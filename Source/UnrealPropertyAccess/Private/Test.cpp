//#include "UnrealReadPropertyAccesser.h"
#include "UElReadPropertyAccesser.h"
#include "MyObject.h"

UE_DISABLE_OPTIMIZATION

namespace
{
	template<class T>
	T RandValue()
	{
		if constexpr (std::is_integral_v<T>)
		{
			return static_cast<T>(FMath::Rand());
		}
		return static_cast<T>(FMath::FRand());
	}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUnrealPropertyAccessStructPrimitiveTest, "PropertyAccess.StructPrimitiveTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FUnrealPropertyAccessStructPrimitiveTest::RunTest(const FString& Parameters)
{
	UE_LOG(LogTemp, Display, TEXT("========================"));
	UE_LOG(LogTemp, Display, TEXT("StructPrimitiveTest Test"));
	UE_LOG(LogTemp, Display, TEXT("========================"));

	const auto OnPropertyErrorHandle = [this](const FString& InError)
		{
			AddError(InError);
		};

	constexpr uint32 TestNum = 10;

	// Booleanテスト
	UE_LOG(LogTemp, Display, TEXT("Boolean Test"));
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const bool TestDataValue = FMath::RandBool();
		FMyTestData TestData = {};
		TestData.BoolValue = TestDataValue;
		TestData.Inner.Uint64Value = 123454321;

		UE::ReadProperty<bool>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, BoolValue))
			.Execute([&](bool PropertyValue)
				{
					TestEqual(TEXT("Boolean Test Error"), TestDataValue, PropertyValue);
				}, OnPropertyErrorHandle);

	}

	// int8テスト
	UE_LOG(LogTemp, Display, TEXT("int8 Test"));
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const int8 TestDataValue = RandValue<int8>();
		FMyTestData TestData = {};
		TestData.Int8Value = TestDataValue;

		UE::ReadProperty<int8>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Int8Value))
			.Execute([&](int8 PropertyValue)
				{
					TestEqual(TEXT("int8 Test Error"), TestDataValue, PropertyValue);
				}, OnPropertyErrorHandle);
	}

	// int16テスト
	UE_LOG(LogTemp, Display, TEXT("int16 Test"));
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const int16 TestDataValue = RandValue<int16>();
		FMyTestData TestData = {};
		TestData.Int16Value = TestDataValue;

		UE::ReadProperty<int16>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Int16Value))
			.Execute([&](int16 PropertyValue)
				{
					TestEqual(TEXT("int16 Test Error"), TestDataValue, PropertyValue);
				}, OnPropertyErrorHandle);
	}

	// int32テスト
	UE_LOG(LogTemp, Display, TEXT("int32 Test"));
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const int32 TestDataValue = RandValue<int32>();
		FMyTestData TestData = {};
		TestData.Int32Value = TestDataValue;

		UE::ReadProperty<int32>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Int32Value))
			.Execute([&](int32 PropertyValue)
				{
					TestEqual(TEXT("int32 Test Error"), TestDataValue, PropertyValue);
				}, OnPropertyErrorHandle);
	}

	// int64テスト
	UE_LOG(LogTemp, Display, TEXT("int64 Test"));
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const int64 TestDataValue = RandValue<int64>();
		FMyTestData TestData = {};
		TestData.Int64Value = TestDataValue;

		UE::ReadProperty<int64>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Int64Value))
			.Execute([&](int64 PropertyValue)
				{
					TestEqual(TEXT("int64 Test Error"), TestDataValue, PropertyValue);
				}, OnPropertyErrorHandle);
	}


	// uint8テスト
	UE_LOG(LogTemp, Display, TEXT("uint8 Test"));
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const uint8 TestDataValue = RandValue<uint8>();
		FMyTestData TestData = {};
		TestData.Uint8Value = TestDataValue;

		UE::ReadProperty<uint8>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Uint8Value))
			.Execute([&](uint8 PropertyValue)
				{
					TestEqual(TEXT("uint8 Test Error"), TestDataValue, PropertyValue);
				}, OnPropertyErrorHandle);
	}

	// uint16テスト
	UE_LOG(LogTemp, Display, TEXT("uint16 Test"));
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const uint16 TestDataValue = RandValue<uint16>();
		FMyTestData TestData = {};
		TestData.Uint16Value = TestDataValue;

		UE::ReadProperty<uint16>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Uint16Value))
			.Execute([&](uint16 PropertyValue)
				{
					TestEqual(TEXT("uint16 Test Error"), TestDataValue, PropertyValue);
				}, OnPropertyErrorHandle);
	}

	// uint32テスト
	UE_LOG(LogTemp, Display, TEXT("uint32 Test"));
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const uint32 TestDataValue = RandValue<uint32>();
		FMyTestData TestData = {};
		TestData.Uint32Value = TestDataValue;

		UE::ReadProperty<uint32>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Uint32Value))
			.Execute([&](uint32 PropertyValue)
				{
					TestEqual(TEXT("uint32 Test Error"), TestDataValue, PropertyValue);
				}, OnPropertyErrorHandle);
	}

	// uint64テスト
	UE_LOG(LogTemp, Display, TEXT("uint64 Test"));
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const uint64 TestDataValue = RandValue<uint64>();
		FMyTestData TestData = {};
		TestData.Uint64Value = TestDataValue;

		UE::ReadProperty<uint64>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Uint64Value))
			.Execute([&](uint64 PropertyValue)
				{
					TestEqual(TEXT("uint64 Test Error"), TestDataValue, PropertyValue);
				}, OnPropertyErrorHandle);
	}

	// 列挙型テスト
	UE_LOG(LogTemp, Display, TEXT("TEnumAsByte<EEnumTest1::Type> Test"));
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const uint8 TestDataValue = RandValue<uint8>();
		FMyTestData TestData = {};
		TestData.EnumValue1 = static_cast<EEnumTest1::Type>(TestDataValue);

		UE::ReadProperty<TEnumAsByte<EEnumTest1::Type>>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, EnumValue1))
			.Execute([&](TEnumAsByte<EEnumTest1::Type> PropertyValue)
				{
					TestEqual(TEXT("TEnumAsByte<EEnumTest1::Type> Test Error"), TestDataValue, PropertyValue);
				}, OnPropertyErrorHandle);
	}

	// 列挙型テスト
	UE_LOG(LogTemp, Display, TEXT("EEnumTest2 Test"));
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const EEnumTest2 TestDataValue = RandValue<EEnumTest2>();
		FMyTestData TestData = {};
		TestData.EnumValue2 = TestDataValue;

		UE::ReadProperty<EEnumTest2>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, EnumValue2))
			.Execute([&](EEnumTest2 PropertyValue)
				{
					TestEqual(TEXT("EEnumTest2 Test Error"), TestDataValue, PropertyValue);
				}, OnPropertyErrorHandle);
	}

	// 列挙型テスト
	UE_LOG(LogTemp, Display, TEXT("EEnumTest3 Test"));
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const EEnumTest3 TestDataValue = RandValue<EEnumTest3>();
		FMyTestData TestData = {};
		TestData.EnumValue3 = TestDataValue;

		UE::ReadProperty<EEnumTest3>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, EnumValue3))
			.Execute([&](EEnumTest3 PropertyValue)
				{
					TestEqual(TEXT("EEnumTest3 Test Error"), TestDataValue, PropertyValue);
				}, OnPropertyErrorHandle);
	}

	// Objectテスト
	UE_LOG(LogTemp, Display, TEXT("Object Test"));
	{
		FMyTestData TestData = {};
		UTestObject* TestObject = NewObject<UTestObject>();
		TestData.Test1 = TestObject;

		// 値が違っているかチェック
		UE::ReadProperty<TObjectPtr<UTestObject>>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Test1))
			.Execute([&](TObjectPtr<UTestObject> PropertyValue)
				{
					TestEqual<TObjectPtr<UObject>>(TEXT("UObject Set Value Test Error"), TestData.Test1, PropertyValue);
				}, OnPropertyErrorHandle);

		// 値の書き換えをチェック
		UE::ReadProperty<TObjectPtr<UTestObject>>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Test1))
			.Execute([&](TObjectPtr<UTestObject>& PropertyValue)
				{
					PropertyValue = nullptr;
				}, OnPropertyErrorHandle);

		TestEqual<TObjectPtr<UObject>>(TEXT("UObject Set Value Test Error"), TestData.Test1, nullptr);

		// 値を更新
		TestData.Test1 = TestObject;
		UE::ReadProperty<UTestObject*>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Test1))
			.Execute([&](UTestObject* PropertyValue)
				{
					// 値を更新したので一致しているはず
					TestEqual<TObjectPtr<UObject>>(TEXT("UObject Property Read Comparison Test Error"), TestData.Test1, PropertyValue);
				}, OnPropertyErrorHandle);

		// 値の書き換えをチェック
		UE::ReadProperty<UTestObject*>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Test1))
			.Execute([&](UTestObject*& PropertyValue)
				{
					PropertyValue = nullptr;
				}, OnPropertyErrorHandle);

		TestEqual<TObjectPtr<UObject>>(TEXT("UObject Set Value Test Error"), TestData.Test1, nullptr);

		TestObject->MarkAsGarbage();
	}

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUnrealPropertyAccessStructHierarchyTest, "PropertyAccess.HierarchyTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FUnrealPropertyAccessStructHierarchyTest::RunTest(const FString& Parameters)
{
	UE_LOG(LogTemp, Display, TEXT("========================"));
	UE_LOG(LogTemp, Display, TEXT("Hierarchy Test"));
	UE_LOG(LogTemp, Display, TEXT("========================"));

	const auto OnPropertyErrorHandle = [this](const FString& InError)
		{
			AddError(InError);
		};

	// 階層テスト
	UE_LOG(LogTemp, Display, TEXT("UMyObject::TestData.Inner.Int32Value Test"));
	{
		UMyObject* TestData = NewObject<UMyObject>();
		const int32 TestDataValue = RandValue<int32>();
		TestData->TestData.Inner.Int32Value = TestDataValue;

		UE::ReadProperty<FMyTestData>(TestData, GET_MEMBER_NAME_CHECKED(UMyObject, TestData))
			.ReadProperty<FMyTestDataInner>(GET_MEMBER_NAME_CHECKED(FMyTestData, Inner))
			.ReadProperty<int32>(GET_MEMBER_NAME_CHECKED(FMyTestDataInner, Int32Value))
			.Execute([&](int32 PropertyValue)
				{
					TestEqual(TEXT("UMyObject::TestData.Inner.Int32Value Test Error"), TestDataValue, PropertyValue);
				}, OnPropertyErrorHandle);
	}

	UE_LOG(LogTemp, Display, TEXT("UMyObject::TestData.Test1.StrValue Test"));
	{
		const FString TestDataValue = TEXT("###ABC###");
		UMyObject* TestData = NewObject<UMyObject>();
		UTest2Object* Test2Data = NewObject<UTest2Object>();
		TestData->TestData.Test1 = Test2Data;
		TestData->TestData.Test2 = Test2Data;
		Test2Data->StrValue = TEXT("###ABC###");

		// TObjectPtr<UTest1Object>だがUTest2Objectが入っている想定のプロパティ
		UE::ReadProperty<FMyTestData>(TestData, GET_MEMBER_NAME_CHECKED(UMyObject, TestData))
			.ReadProperty<TObjectPtr<UTest2Object>>(GET_MEMBER_NAME_CHECKED(FMyTestData, Test1))
			.ReadProperty<FString>(GET_MEMBER_NAME_CHECKED(UTest2Object, StrValue))
			.Execute([&](FString PropertyValue)
				{
					TestEqual(TEXT("UMyObject::TestData.Test1.StrValue Test Error"), TestDataValue, PropertyValue);
				}, OnPropertyErrorHandle);

		UE::ReadProperty<FMyTestData>(TestData, GET_MEMBER_NAME_CHECKED(UMyObject, TestData))
			.ReadProperty<TObjectPtr<UTest2Object>>(GET_MEMBER_NAME_CHECKED(FMyTestData, Test2))
			.ReadProperty<FString>(GET_MEMBER_NAME_CHECKED(UTest2Object, StrValue))
			.Execute([&](FString PropertyValue)
				{
					TestEqual(TEXT("UMyObject::TestData.Test2.StrValue Test Error"), TestDataValue, PropertyValue);
				}, OnPropertyErrorHandle);

	}

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUnrealPropertyAccessStructErrorTest, "PropertyAccess.ErrorCheck", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FUnrealPropertyAccessStructErrorTest::RunTest(const FString& Parameters)
{
	const auto UnreachablePropertyError = [this]<class T>(const T&)
	{
		AddError(TEXT("Access to unreachable property was made"));
	};


	// Struct型テスト
	// 別の型にチェックする
	{
		bool bFailed = true;
		FMyTestData TestData = {};

		UE::ReadProperty<FMyTestData>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Inner))
			.Execute(UnreachablePropertyError,
				[&](const FString& Error)
				{
					bFailed = false;
				});

		TestFalse(TEXT("Property Access Failed"), bFailed);
	}

	// Object型テスト
	// 別の型にチェックする
	{
		bool bFailed = true;
		FMyTestData TestData = {};

		UE::ReadProperty<TObjectPtr<AActor>>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Test1))
			.Execute(UnreachablePropertyError,
				[&](const FString& Error)
				{
					bFailed = false;
				});

		TestFalse(TEXT("Property Access Failed"), bFailed);
	}

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUnrealPropertyAccessContainerErrorTest, "PropertyAccess.ContainerTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FUnrealPropertyAccessContainerErrorTest::RunTest(const FString& Parameters)
{
	const auto OnPropertyErrorHandle = [this](const FString& InError)
		{
			AddError(InError);
		};

	// Arrayテスト
	UE_LOG(LogTemp, Display, TEXT("Array Value Test"));
	{
		FMyTestData TestData = {};
		TestData.Array1.Add(TEXT("ABC"));
		TestData.Array1.Add(TEXT("def"));
		TestData.Array1.Add(TEXT("GHI"));

		TArray<FString> TestArray;

		//using Type = UE::ReadPropertyDetails::TReadPropertyInfo<TArray<FString>>;

		UE::ReadProperty<TArray<FString>>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Array1))
			.Execute([&](const FString& PropertyValue)
				{
					TestArray.Add(PropertyValue);
				}, OnPropertyErrorHandle);

		if (!TestEqual(TEXT("ArrayNum Cheak"), TestArray.Num(), TestData.Array1.Num()))
		{
			return false;
		}

		for (int32 index = 0; index < TestArray.Num(); ++index)
		{
			TestEqual(TEXT("Array Value Cheak"), TestArray[index], TestData.Array1[index]);
		}
	}

	// Arrayテスト
	UE_LOG(LogTemp, Display, TEXT("Array Hierarchy Value Test"));
	{
		FMyTestData TestData = {};
		FMyTestDataInner Inner = {};
		Inner.Int32Value = 1234;
		TestData.Array2.Add(Inner);
		Inner.Int32Value = 5678;
		TestData.Array2.Add(Inner);
		Inner.Int32Value = 9012;
		TestData.Array2.Add(Inner);

		TArray<int32> TestArray;

		UE::ReadProperty<TArray<FMyTestDataInner>>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Array2))
			.ReadProperty<int32>(GET_MEMBER_NAME_CHECKED(FMyTestDataInner, Int32Value))
			.Execute([&](const int32& PropertyValue)
				{
					TestArray.Add(PropertyValue);
				}, OnPropertyErrorHandle);

		if (!TestEqual(TEXT("ArrayNum Cheak"), TestArray.Num(), TestData.Array2.Num()))
		{
			return false;
		}

		for (int32 index = 0; index < TestArray.Num(); ++index)
		{
			const FMyTestDataInner& Temp = TestData.Array2[index];
			TestEqual(TEXT("Array Value Cheak"), TestArray[index], Temp.Int32Value);
		}
	}

	// Mapテスト
	UE_LOG(LogTemp, Display, TEXT("Map Value Test"));
	{
		FMyTestData TestData = {};

		for (int32 i = 0; i < 20; ++i)
		{
			const int32 Value = RandValue<int32>();
			TestData.Map1.Add(i, Value);
		}

		TMap<int32, int32> TestMap;

		UE::ReadProperty<TMap<int32, int32>>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Map1))
			.Execute([&](int32 Key, int32 Value)
				{
					TestMap.Add(Key, Value);
				}, OnPropertyErrorHandle);

		if (!TestEqual(TEXT("MapNum Cheak"), TestMap.Num(), TestData.Map1.Num()))
		{
			return false;
		}

		for (auto& [Key, Value] : TestData.Map1)
		{
			if (!TestTrue(TEXT("Map Key Cheak"), TestMap.Contains(Key)))
			{
				return false;
			}

			const int32 TestMapValue = TestMap[Key];
			TestEqual(TEXT("Map Value Cheak"), Value, TestMapValue);
		}
	}


	// Map階層テスト
	UE_LOG(LogTemp, Display, TEXT("Map Hierarchy Value Test"));
	{
		FMyTestData TestData = {};

		for (int32 i = 0; i < 20; ++i)
		{
			FMyTestDataInner Inner = {};
			Inner.Int32Value = RandValue<int32>();
			TestData.Map2.Add(i, Inner);
		}

		TArray<int32> TestArray;

		UE::ReadProperty<TMap<int32, FMyTestDataInner>>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Map2))
			.ReadProperty<int32>(GET_MEMBER_NAME_CHECKED(FMyTestDataInner, Int32Value))
			.Execute([&](int32 PropertyValue)
				{
					TestArray.Add(PropertyValue);
				}, OnPropertyErrorHandle);

		if (!TestEqual(TEXT("MapNum Cheak"), TestArray.Num(), TestData.Map2.Num()))
		{
			return false;
		}

		for (auto& [Key, Value] : TestData.Map2)
		{
			const int32 TestValue = TestArray[Key];
			TestEqual(TEXT("Map Value Cheak"), TestValue, Value.Int32Value);
		}
	}

	return true;
}


UE_ENABLE_OPTIMIZATION
