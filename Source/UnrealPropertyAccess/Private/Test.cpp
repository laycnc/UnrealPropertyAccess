#include "UnrealReadPropertyAccesser.h"
#include "MyObject.h"

UE_DISABLE_OPTIMIZATION

namespace
{
	template<class T>
	T RandRange()
	{
		return (T)FMath::RandRange(TNumericLimits<T>::Min(), TNumericLimits<T>::Max());
	}

}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUnrealPropertyAccessStructBooleanTest, "PropertyAccess.StructBooleanTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FUnrealPropertyAccessStructBooleanTest::RunTest(const FString& Parameters)
{
	for (uint32 i = 0; i < 10; ++i)
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

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUnrealPropertyAccessStructInt8Test, "PropertyAccess.StructInt8Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FUnrealPropertyAccessStructInt8Test::RunTest(const FString& Parameters)
{
	for (uint32 i = 0; i < 10; ++i)
	{
		const int8 TestDataValue = RandRange<int8>();
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

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUnrealPropertyAccessStructInt16Test, "PropertyAccess.StructInt16Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FUnrealPropertyAccessStructInt16Test::RunTest(const FString& Parameters)
{
	for (uint32 i = 0; i < 10; ++i)
	{
		const int16 TestDataValue = RandRange<int16>();
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

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUnrealPropertyAccessStructInt32Test, "PropertyAccess.StructInt32Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FUnrealPropertyAccessStructInt32Test::RunTest(const FString& Parameters)
{
	for (uint32 i = 0; i < 10; ++i)
	{
		const int32 TestDataValue = RandRange<int32>();
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

	return true;
}

UE_ENABLE_OPTIMIZATION
