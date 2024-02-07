// Fill out your copyright notice in the Description page of Project Settings.

#include <type_traits>
#include "Containers/UnrealString.h"
#include "UObject/Class.h"
#include "UObject/Field.h"
#include "UObject/UnrealType.h"
#include "UObject/NameTypes.h"

namespace UE
{

	template<class ... Args>
	struct TLastType;

	template<class T>
	struct TLastType<T>
	{
		using Type = T;
	};

	template<class T, class Ty, class ... Tz>
	struct TLastType<T, Ty, Tz...>
		: public TLastType<Ty, Tz...>
	{
	};

	template<class T>
	struct TReadUnrealPropertyAccesser;

	template<class Pred, class T>
	struct TDataAccessorInvokeable
	{
		static constexpr bool Value = std::is_invocable_v<Pred, T>;
	};

	template<class Pred, class KeyType, class ValueType>
	struct TDataAccessorInvokeable<Pred, TMap<KeyType, ValueType>>
	{
		static constexpr bool Value = std::is_invocable_v<Pred, KeyType, ValueType>;
	};


	template<class ErrorPred>
	constexpr bool TDataAccessorErrorInvokeable = std::is_invocable_v<ErrorPred, const FString&>;

	template<class T, class ...Tx>
	class TDataAccessorImpl
	{
	private:

		using TargetPropertyType = typename TLastType<T, Tx...>::Type;

		static constexpr size_t ReadPrpertyNum = sizeof...(Tx) + 1;

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
			else
			{
				TargetPropertyType* Value = static_cast<TargetPropertyType*>(ValuePtr);
				InPred(*Value);
			}
		}


		template<size_t I, class Pred, class ErrorPred>
		void ExecuteImpl(Pred InPred, ErrorPred InErrorPred, void* KeyPtr, UStruct* KeyStruct, void* ValuePtr, UStruct* ValueStruct, std::false_type)
		{
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
				if constexpr (TDataAccessorErrorInvokeable<ErrorPred>)
				{
					InErrorPred(FString::Printf(TEXT("Struct(%s) Property(%s)が見つかりませんでした。"), *GetNameSafe(ValueStruct), *PropertyName.ToString()));
				}

				return;
			}
			if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
			{
				void* NewValue = Property->ContainerPtrToValuePtr<void>(ValuePtr);
				ExecuteImpl<I + 1>(InPred, InErrorPred, nullptr, nullptr, NewValue, ObjectProperty->PropertyClass, NextConditionType());
			}
			else if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
			{
				void* NewValue = Property->ContainerPtrToValuePtr<void>(ValuePtr);
				ExecuteImpl<I + 1>(InPred, InErrorPred, nullptr, nullptr, NewValue, StructProperty->Struct, NextConditionType());
			}
			else if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
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
					void* KeyPtr = MapHelper.GetKeyPtr(Index);
					void* ValuePtr = MapHelper.GetValuePtr(Index);
					ExecuteImpl<I + 1>(InPred, InErrorPred, KeyPtr, MapKeyStruct, ValuePtr, MapValueStruct, NextConditionType());
				}
			}
			else
			{
				void* NewValue = Property->ContainerPtrToValuePtr<void>(ValuePtr);
				ExecuteImpl<I + 1>(InPred, InErrorPred, nullptr, nullptr, NewValue, nullptr, NextConditionType());
			}
		}
	public:

		TDataAccessorImpl(TReadUnrealPropertyAccesser<T>* InTopParam)
			: TopParam(InTopParam)
		{
		}

#ifdef __cpp_concepts

		template<class ExecPred> requires (TDataAccessorInvokeable<ExecPred, TargetPropertyType >::Value)
			void Execute(ExecPred InExec)
		{
			ExecuteImpl<0>(InExec, nullptr, nullptr, nullptr, TopParam->DataPtr, TopParam->TopDataClass, std::false_type());
		}

		template<class ExecPred, class ErrorPred> requires (TDataAccessorInvokeable<ExecPred, TargetPropertyType >::Value&& std::is_invocable_v<ErrorPred, const FString&>)
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
		TReadUnrealPropertyAccesser<T>* TopParam = nullptr;
	};

	template<class T>
	struct TReadUnrealPropertyAccesser
		: public TDataAccessorImpl<T>
	{
		TReadUnrealPropertyAccesser(void* InValuePtr, UStruct* InValueClass, FName InPropertyName)
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

	template<class Ty, class ValueType>
	TReadUnrealPropertyAccesser<Ty> ReadProperty(ValueType* InValuePtr, FName InPropertyName)
	{
		UStruct* ValueStruct = nullptr;
		if constexpr (std::is_base_of_v<UObject, ValueType>)
		{
			ValueStruct = ValueType::StaticClass();
		}
		else
		{
			ValueStruct = ValueType::StaticStruct();
		}
		auto Accesser = TReadUnrealPropertyAccesser<Ty>(InValuePtr, ValueStruct, InPropertyName);
		return Accesser;
	}
}
