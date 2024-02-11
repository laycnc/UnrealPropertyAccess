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


	return true;
}

UE_ENABLE_OPTIMIZATION
