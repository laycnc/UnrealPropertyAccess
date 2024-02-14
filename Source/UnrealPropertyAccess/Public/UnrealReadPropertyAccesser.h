// Fill out your copyright notice in the Description page of Project Settings.

#include <type_traits>
#include "Containers/UnrealString.h"
#include "UObject/Class.h"
#include "UObject/Field.h"
#include "UObject/UnrealType.h"
#include "UObject/NameTypes.h"

namespace UE
{
	namespace ReadPropertyHelper
	{
		template<size_t I, class ... T>
		struct IndexOfTypeImpl;

		template<size_t I, class T, class ... Ty>
		struct IndexOfTypeImpl<I, T, Ty...> : public IndexOfTypeImpl<I - 1, Ty...> {};

		template<>
		struct IndexOfTypeImpl<0> {};

		template<class T, class ... Ty>
		struct IndexOfTypeImpl<0, T, Ty...>
		{
			using Type = T;
		};

		template<size_t I, class ... T>
		using IndexOfType = typename IndexOfTypeImpl<I, T...>::Type;

		template <typename T>
		struct TIsUnrealStructImpl
		{
			template <typename U>
			static std::true_type Test(decltype(&U::StaticStruct));

			template <typename U>
			static std::false_type Test(...);

			static constexpr bool Value = decltype(Test<T>(nullptr))::value;
		};

		template <typename T>
		constexpr bool TIsUnrealStruct = TIsUnrealStructImpl<T>::Value;

		template<class T>
		struct TReadPropertyAccesser;

		template<class Pred, class T>
		struct TDataAccessorInvokeable
		{
			static constexpr bool Value = std::is_invocable_v<Pred, T&>;
		};

		template<class Pred, class KeyType, class ValueType>
		struct TDataAccessorInvokeable<Pred, TMap<KeyType, ValueType>>
		{
			static constexpr bool Value = std::is_invocable_v<Pred, KeyType, ValueType>;
		};


		template<class ErrorPred>
		constexpr bool TIsErrorInvokeable = std::is_invocable_v<ErrorPred, const FString&>;

		template<class T, class ...Tx>
		class TDataAccessorImpl
		{
		public:
			using TargetPropertyType = IndexOfType<sizeof...(Tx), T, Tx...>;

			static constexpr size_t ReadPrpertyNum = sizeof...(Tx) + 1;

		private:
			template<class Pred, class ErrorPred>
			void ExecuteImpl(Pred& InPred, ErrorPred& InError, TObjectPtr<UObject>* InObject)
			{
				// 関数を分割しないと何故かエラーが出る為
				// しょうがなく分離コンパイルエラーになる理由は分からない
				if (InObject)
				{
					using ObjectType = TPointedToType<TargetPropertyType>;
					TObjectPtr<UObject>& Object = *InObject;
					TargetPropertyType Target = Cast<ObjectType>(Object.Get());
					InPred(Target);
					// 戻り値が参照の場合にポインタが書き変わっている可能性がある為
					Object = Target;
				}
			}

			template<size_t I, class Pred, class ErrorPred>
			void ExecuteImpl(Pred& InPred, ErrorPred& InError, void* KeyPtr, UStruct* KeyStruct, void* ValuePtr, UStruct* ValueStruct, std::true_type)
			{
				if constexpr (TIsTMap<TargetPropertyType>::Value)
				{
					// Mapだけ特殊化
					// KeyとValueをコールバックで呼ぶ必要がある
					using KeyType = typename TargetPropertyType::KeyType;
					using ValueType = typename TargetPropertyType::ValueType;

					KeyType* Key = static_cast<KeyType*>(KeyPtr);
					ValueType* Value = static_cast<ValueType*>(ValuePtr);

					InPred(*Key, *Value);
				}
				else if constexpr (TIsPointerOrObjectPtrToBaseOf<TargetPropertyType, UObject>::Value)
				{
					ExecuteImpl(InPred, InError, static_cast<TObjectPtr<UObject>*>(ValuePtr));
				}
				else
				{
					TargetPropertyType* Value = static_cast<TargetPropertyType*>(ValuePtr);
					InPred(*Value);
				}
			}

			template<size_t I, class Pred, class ErrorPred, class ValueType>
			void ExecuteImpl(Pred InPred, ErrorPred InErrorPred, void* KeyPtr, UStruct* KeyStruct, ValueType* InValuePtr, UStruct* ValueStruct, std::false_type)
			{
				using Type = IndexOfType<I, T, Tx...>;

				void* ValuePtr = InValuePtr;
				if constexpr (std::is_same_v<ValueType, TObjectPtr<UObject>>)
				{
					// UObjectの場合には生ポインタまで取得する必要があるので特殊化が必要
					// TObjectPtrのままだと値を取得する事が出来ない
					if (!IsValid(*InValuePtr))
					{
						// 未設定の場合には早期終了
						return;
					}

					UObject* ObjectPtr = InValuePtr->Get();

					if (!ObjectPtr->GetClass()->IsChildOf(ValueStruct))
					{
						// 念の為取得したObjectのタイプチェックもする
						return;
					}

					// 本当はTypeを参照してUClassを上書きする必要がある
					// todo
					ValueStruct = ObjectPtr->GetClass();

					ValuePtr = ObjectPtr;
				}

				const FName& PropertyName = TopParam->PropertyNames[I];
				FProperty* Property = FindFProperty<FProperty>(ValueStruct, PropertyName);

				using NextConditionType = std::bool_constant<ReadPrpertyNum == I + 1>;

				const auto GetPropertyClass = [](const FProperty* InProperty) -> UStruct*
					{
						if (const FObjectProperty* SetInnerObjProperty = CastField<FObjectProperty>(InProperty))
						{
							return SetInnerObjProperty->PropertyClass;
						}
						else if (const FStructProperty* SetInnerStructProperty = CastField<FStructProperty>(InProperty))
						{
							return SetInnerStructProperty->Struct;
						}
						return nullptr;
					};

				if (Property == nullptr)
				{
					// Propertyが見つからないのでエラー
					if constexpr (TIsErrorInvokeable<ErrorPred>)
					{
						InErrorPred(FString::Printf(TEXT("Struct(%s) Property(%s)が見つかりませんでした。"), *GetNameSafe(ValueStruct), *PropertyName.ToString()));
					}

					return;
				}
				if constexpr (TIsPointerOrObjectPtrToBaseOf<Type, UObject>::Value)
				{
					if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
					{
						UClass* TargetClass = TPointedToType<Type>::StaticClass();
						if (!TargetClass->IsChildOf(ObjectProperty->PropertyClass))
						{
							if constexpr (TIsErrorInvokeable<ErrorPred>)
							{
								// エラーハンドリング関数が指定されている場合にはコールバックを出す
								InErrorPred(FString::Printf(TEXT("指定されている[%d]型(%s) != %s"), I, *ObjectProperty->PropertyClass->GetName(), *TargetClass->GetName()));
							}
							return;
						}
						TObjectPtr<UObject>* NewValue = ObjectProperty->ContainerPtrToValuePtr<TObjectPtr<UObject>>(ValuePtr);
						ExecuteImpl<I + 1>(InPred, InErrorPred, nullptr, nullptr, NewValue, ObjectProperty->PropertyClass, NextConditionType());
						return;
					}
					// Propertyが見つからないのでエラー
					if constexpr (TIsErrorInvokeable<ErrorPred>)
					{
						InErrorPred(FString::Printf(TEXT("指定されている[%d]型がUObject派生のクラスではありません"), I));
					}
				}
				if constexpr (TIsUnrealStruct<Type>)
				{
					if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
					{
						UStruct* TargetStruct = Type::StaticStruct();
						if (TargetStruct != StructProperty->Struct)
						{
							if constexpr (TIsErrorInvokeable<ErrorPred>)
							{
								// エラーハンドリング関数が指定されている場合にはコールバックを出す
								InErrorPred(FString::Printf(TEXT("指定されている[%d]型(%s) != %s"), I, *StructProperty->Struct->GetName(), *TargetStruct->GetName()));
							}
							return;
						}
						void* NewValue = Property->ContainerPtrToValuePtr<void>(ValuePtr);
						ExecuteImpl<I + 1>(InPred, InErrorPred, nullptr, nullptr, NewValue, StructProperty->Struct, NextConditionType());
					}
					// Propertyが見つからないのでエラー
					if constexpr (TIsErrorInvokeable<ErrorPred>)
					{
						InErrorPred(FString::Printf(TEXT("指定されている[%d]型がUObject派生のクラスではありません"), I));
					}
				}
				if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
				{
					UStruct* ArrayValueStruct = GetPropertyClass(ArrayProperty->Inner);
					void* NewValue = ArrayProperty->ContainerPtrToValuePtr<void>(ValuePtr);

					FScriptArrayHelper ArrayHelper(ArrayProperty, NewValue);

					for (int32 Index = 0; Index < ArrayHelper.Num(); ++Index)
					{
						void* ArrayValuePtr = ArrayHelper.GetRawPtr(Index);
						ExecuteImpl<I + 1>(InPred, InErrorPred, nullptr, nullptr, ArrayValuePtr, ArrayValueStruct, NextConditionType());
					}
				}
				else if (FSetProperty* SetProperty = CastField<FSetProperty>(Property))
				{
					UStruct* SetValueStruct = GetPropertyClass(SetProperty->ElementProp);
					void* NewValue = SetProperty->ContainerPtrToValuePtr<void>(ValuePtr);

					FScriptSetHelper SetHelper(SetProperty, NewValue);

					for (int32 Index = 0; Index < SetHelper.Num(); ++Index)
					{
						void* ArrayValuePtr = SetHelper.GetElementPtr(Index);
						ExecuteImpl<I + 1>(InPred, InErrorPred, nullptr, nullptr, ArrayValuePtr, SetValueStruct, NextConditionType());
					}
				}
				else if (FMapProperty* MapProperty = CastField<FMapProperty>(Property))
				{
					UStruct* MapKeyStruct = GetPropertyClass(MapProperty->KeyProp);
					UStruct* MapValueStruct = GetPropertyClass(MapProperty->ValueProp);

					void* NewValue = MapProperty->ContainerPtrToValuePtr<void>(ValuePtr);

					FScriptMapHelper MapHelper(MapProperty, NewValue);

					for (int32 Index = 0; Index < MapHelper.Num(); ++Index)
					{
						void* MapKeyPtr = MapHelper.GetKeyPtr(Index);
						void* MapValuePtr = MapHelper.GetValuePtr(Index);
						ExecuteImpl<I + 1>(InPred, InErrorPred, MapKeyPtr, MapKeyStruct, MapValuePtr, MapValueStruct, NextConditionType());
					}
				}
				else
				{
					void* NewValue = Property->ContainerPtrToValuePtr<void>(ValuePtr);
					ExecuteImpl<I + 1>(InPred, InErrorPred, nullptr, nullptr, NewValue, nullptr, NextConditionType());
				}
			}
		public:

			TDataAccessorImpl(TReadPropertyAccesser<T>* InTopParam)
				: TopParam(InTopParam)
			{
			}

#ifdef __cpp_concepts

			template<class ExecPred> requires (TDataAccessorInvokeable<ExecPred, TargetPropertyType >::Value)
				void Execute(ExecPred InExec)
			{
				ExecuteImpl<0>(InExec, nullptr, nullptr, nullptr, TopParam->DataPtr, TopParam->TopDataClass, std::false_type());
			}

			template<class ExecPred, class ErrorPred> requires (TDataAccessorInvokeable<ExecPred, TargetPropertyType >::Value&& TIsErrorInvokeable<ErrorPred>)
				void Execute(ExecPred InExec, ErrorPred InError)
			{
				ExecuteImpl<0>(InExec, InError, nullptr, nullptr, TopParam->DataPtr, TopParam->TopDataClass, std::false_type());
			}


#else

			template<class Pred>
			void Execute(Pred InPred)
			{
				ExecuteImpl<0>(InPred, TopParam->DataPtr, TopParam->TopDataClass, std::false_type());
			}

			template<class Pred, class ErrorPred>
			void Execute(ExecPred InExec, ErrorPred InError)
			{
				ExecuteImpl<0>(InExec, InError, nullptr, nullptr, TopParam->DataPtr, TopParam->TopDataClass, std::false_type());
			}

#endif

			template<class Ty>
			TDataAccessorImpl<T, Tx..., Ty> ReadProperty(FName InPropertyName)
			{
				auto Accesser = TDataAccessorImpl<T, Tx..., Ty>(TopParam);
				TopParam->PropertyNames.Add(InPropertyName);
				return Accesser;
			}

		protected:
			TReadPropertyAccesser<T>* TopParam = nullptr;
		};

		template<class T>
		struct TReadPropertyAccesser
			: public TDataAccessorImpl<T>
		{
			TReadPropertyAccesser(void* InValuePtr, UStruct* InValueClass, FName InPropertyName)
				: TDataAccessorImpl<T>(this)
				, DataPtr(InValuePtr)
				, TopDataClass(InValueClass)
				, PropertyNames()
			{
				PropertyNames.Add(InPropertyName);
			}

			void* DataPtr = nullptr;
			UStruct* TopDataClass = nullptr;
			TArray<FName> PropertyNames;
		};

	}

	template<class Ty, class ValueType>
	ReadPropertyHelper::TReadPropertyAccesser<Ty> ReadProperty(ValueType* InValuePtr, FName InPropertyName)
	{
		UStruct* ValueStruct = nullptr;
		if constexpr (TIsPointerOrObjectPtrToBaseOf<ValueType*, UObject>::Value)
		{
			ValueStruct = ValueType::StaticClass();
		}
		else
		{
			ValueStruct = ValueType::StaticStruct();
		}
		auto Accesser = ReadPropertyHelper::TReadPropertyAccesser<Ty>(InValuePtr, ValueStruct, InPropertyName);
		return Accesser;
	}
}

