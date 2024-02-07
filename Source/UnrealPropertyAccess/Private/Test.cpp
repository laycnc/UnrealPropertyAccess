#include "ReadPropertyAccesser.h"
#include "MyObject.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUnrealPropertyAccessStructBooleanTest, "PropertyAccess.StructBooleanTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FUnrealPropertyAccessStructBooleanTest::RunTest(const FString& Parameters)
{
	bool bFailed = false;
	FMyTestData TestData = {};

	// テストデータ
	const bool TestDataValues[] = { false, true, false };

	for (bool TestDataValue : TestDataValues)
	{
		TestData.BoolValue = TestDataValue;

		UE::ReadProperty<bool>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, BoolValue))
			.Execute([&](bool PropertyValue)
				{
					if (PropertyValue != TestDataValue)
					{
						bFailed = true;
					}
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
	bool bFailed = false;
	FMyTestData TestData = {};

	// テストデータ
	const int8 TestDataValues[] = { 124, 21, 11, 23 };

	for (int8 TestDataValue : TestDataValues)
	{
		TestData.Int8Value = TestDataValue;

		UE::ReadProperty<int8>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Int8Value))
			.Execute([&](int8 PropertyValue)
				{
					if (PropertyValue != TestDataValue)
					{
						bFailed = true;
					}
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
	bool bFailed = false;
	FMyTestData TestData = {};

	// テストデータ
	const int16 TestDataValues[] = { 124, 21, 11, 23 };

	for (int16 TestDataValue : TestDataValues)
	{
		TestData.Int16Value = TestDataValue;

		UE::ReadProperty<int16>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Int16Value))
			.Execute([&](int16 PropertyValue)
				{
					if (PropertyValue != TestDataValue)
					{
						bFailed = true;
					}
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
	bool bFailed = false;
	FMyTestData TestData = {};

	// テストデータ
	const int32 TestDataValues[] = { 3221, 5322, 2315, 797 };

	for (int32 TestDataValue : TestDataValues)
	{
		TestData.Int32Value = TestDataValue;

		UE::ReadProperty<int32>(&TestData, GET_MEMBER_NAME_CHECKED(FMyTestData, Int32Value))
			.Execute([&](int32 PropertyValue)
				{
					if (PropertyValue != TestDataValue)
					{
						bFailed = true;
					}
				});

		if (bFailed)
		{
			return false;
		}
	}

	return true;
}
