#include "UnrealReadPropertyAccesser.h"
#include "MyObject.h"

UE_DISABLE_OPTIMIZATION

namespace
{
	template<class T>
	T RandValue()
	{
		return static_cast<T>(FMath::FRand());
	}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUnrealPropertyAccessStructPrimitiveTest, "PropertyAccess.StructPrimitiveTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FUnrealPropertyAccessStructPrimitiveTest::RunTest(const FString& Parameters)
{
	constexpr uint32 TestNum = 10;
	// Booleanテスト
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const bool TestDataValue = FMath::RandBool();
		bool bFailed = true;
		FMyTestData TestData = {};
		TestData.BoolValue = TestDataValue;
		TestData.Inner.Uint64Value = 123454321;

		UE::ReadProperty<bool>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, BoolValue))
			.Execute([&](bool PropertyValue)
				{
					bFailed = PropertyValue != TestDataValue;
				});

		if (bFailed)
		{
			return false;
		}
	}

	// int8テスト
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const int8 TestDataValue = RandValue<int8>();
		bool bFailed = true;
		FMyTestData TestData = {};
		TestData.Int8Value = TestDataValue;

		UE::ReadProperty<int8>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Int8Value))
			.Execute([&](int8 PropertyValue)
				{
					bFailed = PropertyValue != TestDataValue;
				});

		if (bFailed)
		{
			return false;
		}
	}

	// int16テスト
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const int16 TestDataValue = RandValue<int16>();
		bool bFailed = true;
		FMyTestData TestData = {};
		TestData.Int16Value = TestDataValue;

		UE::ReadProperty<int16>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Int16Value))
			.Execute([&](int16 PropertyValue)
				{
					bFailed = PropertyValue != TestDataValue;
				});

		if (bFailed)
		{
			return false;
		}
	}

	// int32テスト
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const int32 TestDataValue = RandValue<int32>();
		bool bFailed = true;
		FMyTestData TestData = {};
		TestData.Int32Value = TestDataValue;

		UE::ReadProperty<int32>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Int32Value))
			.Execute([&](int32 PropertyValue)
				{
					bFailed = PropertyValue != TestDataValue;
				});

		if (bFailed)
		{
			return false;
		}
	}

	// int64テスト
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const int64 TestDataValue = RandValue<int64>();
		bool bFailed = true;
		FMyTestData TestData = {};
		TestData.Int64Value = TestDataValue;

		UE::ReadProperty<int64>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Int64Value))
			.Execute([&](int64 PropertyValue)
				{
					bFailed = PropertyValue != TestDataValue;
				});

		if (bFailed)
		{
			return false;
		}
	}


	// uint8テスト
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const uint8 TestDataValue = RandValue<uint8>();
		bool bFailed = true;
		FMyTestData TestData = {};
		TestData.Uint8Value = TestDataValue;

		UE::ReadProperty<uint8>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Uint8Value))
			.Execute([&](uint8 PropertyValue)
				{
					bFailed = PropertyValue != TestDataValue;
				});

		if (bFailed)
		{
			return false;
		}
	}

	// uint16テスト
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const uint16 TestDataValue = RandValue<uint16>();
		bool bFailed = true;
		FMyTestData TestData = {};
		TestData.Uint16Value = TestDataValue;

		UE::ReadProperty<uint16>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Uint16Value))
			.Execute([&](uint16 PropertyValue)
				{
					bFailed = PropertyValue != TestDataValue;
				});

		if (bFailed)
		{
			return false;
		}
	}

	// uint32テスト
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const uint32 TestDataValue = RandValue<uint32>();
		bool bFailed = true;
		FMyTestData TestData = {};
		TestData.Uint32Value = TestDataValue;

		UE::ReadProperty<uint32>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Uint32Value))
			.Execute([&](uint32 PropertyValue)
				{
					bFailed = PropertyValue != TestDataValue;
				});

		if (bFailed)
		{
			return false;
		}
	}

	// uint64テスト
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const uint64 TestDataValue = RandValue<uint64>();
		bool bFailed = true;
		FMyTestData TestData = {};
		TestData.Uint64Value = TestDataValue;

		UE::ReadProperty<uint64>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Uint64Value))
			.Execute([&](uint64 PropertyValue)
				{
					bFailed = PropertyValue != TestDataValue;
				});

		if (bFailed)
		{
			return false;
		}
	}

	// 列挙型テスト
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const uint8 TestDataValue = RandValue<uint8>();
		bool bFailed = true;
		FMyTestData TestData = {};
		TestData.EnumValue1 = static_cast<EEnumTest1::Type>(TestDataValue);

		UE::ReadProperty<TEnumAsByte<EEnumTest1::Type>>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, EnumValue1))
			.Execute([&](TEnumAsByte<EEnumTest1::Type> PropertyValue)
				{
					bFailed = PropertyValue != TestDataValue;
				});

		if (bFailed)
		{
			return false;
		}
	}

	// 列挙型テスト
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const EEnumTest2 TestDataValue = RandValue<EEnumTest2>();
		bool bFailed = true;
		FMyTestData TestData = {};
		TestData.EnumValue2 = TestDataValue;

		UE::ReadProperty<EEnumTest2>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, EnumValue2))
			.Execute([&](EEnumTest2 PropertyValue)
				{
					bFailed = PropertyValue != TestDataValue;
				});


		//using EEnumTest1AsByte = TEnumAsByte< EEnumTest1::Type>;
		//using FFF1 = std::conditional_t<TIsTEnumAsByte<EEnumTest1AsByte>::Value, EEnumTest1AsByte::EnumType, EEnumTest1AsByte>;
		//using FFF2 = std::conditional_t<TIsTEnumAsByte<EEnumTest2>::Value, TEnumAsByte<EEnumTest2>::EnumType, EEnumTest2>;
		//using FFF3 = std::conditional_t<TIsTEnumAsByte<EEnumTest3>::Value, TEnumAsByte<EEnumTest3>::EnumType, EEnumTest2>;

		if (bFailed)
		{
			return false;
		}
	}

	// 列挙型テスト
	for (uint32 i = 0; i < TestNum; ++i)
	{
		const EEnumTest3 TestDataValue = RandValue<EEnumTest3>();
		bool bFailed = true;
		FMyTestData TestData = {};
		TestData.EnumValue3 = TestDataValue;

		UE::ReadProperty<EEnumTest3>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, EnumValue3))
			.Execute([&](EEnumTest3 PropertyValue)
				{
					bFailed = PropertyValue != TestDataValue;
				});

		if (bFailed)
		{
			return false;
		}
	}

	// Objectテスト
	{
		bool bFailed = true;
		FMyTestData TestData = {};
		UTestObject* TestObject = NewObject<UTestObject>();
		TestData.Test1 = TestObject;

		// 値が違っているかチェック
		UE::ReadProperty<TObjectPtr<UTestObject>>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Test1))
			.Execute([&](TObjectPtr<UTestObject> PropertyValue)
				{
					bFailed = TestData.Test1 != PropertyValue;
				});

		if (bFailed)
		{
			return false;
		}

		// 値の書き換えをチェック
		UE::ReadProperty<TObjectPtr<UTestObject>>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Test1))
			.Execute([&](TObjectPtr<UTestObject>& PropertyValue)
				{
					PropertyValue = nullptr;
				});

		if (TestData.Test1 != nullptr)
		{
			return false;
		}

		TestData.Test1 = TestObject;

		// 値が違っているかチェック
		UE::ReadProperty<UTestObject*>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Test1))
			.Execute([&](UTestObject* PropertyValue)
				{
					bFailed = TestData.Test1 != PropertyValue;
				});

		if (bFailed)
		{
			return false;
		}

		// 値の書き換えをチェック
		UE::ReadProperty<UTestObject*>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Test1))
			.Execute([&](UTestObject*& PropertyValue)
				{
					PropertyValue = nullptr;
				});

		if (TestData.Test1 != nullptr)
		{
			return false;
		}

		TestObject->MarkAsGarbage();

		if (bFailed)
		{
			return false;
		}
	}

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUnrealPropertyAccessStructHierarchyTest, "PropertyAccess.HierarchyTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FUnrealPropertyAccessStructHierarchyTest::RunTest(const FString& Parameters)
{
	// 階層テスト
	{
		bool bFailed = true;
		UMyObject* TestData = NewObject<UMyObject>();
		const int32 TestDataValue = RandValue<int32>();
		TestData->TestData.Inner.Int32Value = TestDataValue;

		UE::ReadProperty<FMyTestData>(TestData, GET_MEMBER_NAME_CHECKED(UMyObject, TestData))
			.ReadProperty<FMyTestDataInner>(GET_MEMBER_NAME_CHECKED(FMyTestData, Inner))
			.ReadProperty<int32>(GET_MEMBER_NAME_CHECKED(FMyTestDataInner, Int32Value))
			.Execute([&](int32 PropertyValue)
				{
					bFailed = PropertyValue != TestDataValue;
				});

		if (bFailed)
		{
			return false;
		}
	}

	{
		const FString TestDataValue = TEXT("###ABC###");
		bool bFailed = true;
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
					bFailed = PropertyValue != TestDataValue;
				});

		if (bFailed)
		{
			return false;
		}

		UE::ReadProperty<FMyTestData>(TestData, GET_MEMBER_NAME_CHECKED(UMyObject, TestData))
			.ReadProperty<TObjectPtr<UTest2Object>>(GET_MEMBER_NAME_CHECKED(FMyTestData, Test2))
			.ReadProperty<FString>(GET_MEMBER_NAME_CHECKED(UTest2Object, StrValue))
			.Execute([&](FString PropertyValue)
				{
					bFailed = PropertyValue != TestDataValue;
				});

		if (bFailed)
		{
			return false;
		}
	}

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUnrealPropertyAccessStructErrorTest, "PropertyAccess.ErrorCheck", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FUnrealPropertyAccessStructErrorTest::RunTest(const FString& Parameters)
{
	// Struct型テスト
	// 別の型にチェックする
	{
		bool bFailed = true;
		FMyTestData TestData = {};

		UE::ReadProperty<FMyTestData>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Inner))
			.Execute([](const FMyTestData&) {},
				[&](const FString& Error)
				{
					bFailed = false;
				});

		if (bFailed)
		{
			return false;
		}
	}

	// Object型テスト
	// 別の型にチェックする
	{
		bool bFailed = true;
		FMyTestData TestData = {};

		UE::ReadProperty<TObjectPtr<AActor>>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Test1))
			.Execute([](const TObjectPtr<AActor>&) {},
				[&](const FString& Error)
				{
					bFailed = false;
				});

		if (bFailed)
		{
			return false;
		}
	}

	return true;
}

UE_ENABLE_OPTIMIZATION
