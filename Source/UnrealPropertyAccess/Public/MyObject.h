// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

UENUM()
namespace EEnumTest1
{
	enum Type
	{
		Value1,
		Value2,
		Value3,
	};
}


UENUM()
enum EEnumTest2
{
	EnumTest2_Value1,
	EnumTest2_Value2,
	EnumTest2_Value3,
};

UENUM()
enum struct EEnumTest3 : uint8
{
	Value1,
	Value2,
	Value3,
};


UCLASS()
class UTestObject : public UObject
{
	GENERATED_BODY()
};


UCLASS()
class UTest2Object : public UTestObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool BoolValue = 0;

	UPROPERTY()
	FString StrValue = TEXT("ABCD");
};


USTRUCT()
struct FMyTestDataInner
{
	GENERATED_BODY()
public:

	UPROPERTY()
	bool BoolValue = 0;

	UPROPERTY()
	int8 Int8Value = 0;

	UPROPERTY()
	int16 Int16Value = 0;

	UPROPERTY()
	int32 Int32Value = 0;

	UPROPERTY()
	int64 Int64Value = 0;

	UPROPERTY()
	uint8 Uint8Value = 0;

	UPROPERTY()
	uint16 Uint16Value = 0;

	UPROPERTY()
	uint32 Uint32Value = 0;

	UPROPERTY()
	uint64 Uint64Value = 0;
};



USTRUCT()
struct FMyTestData
{
	GENERATED_BODY()
public:

	UPROPERTY()
	bool BoolValue = 0;

	UPROPERTY()
	int8 Int8Value = 0;

	UPROPERTY()
	int16 Int16Value = 0;

	UPROPERTY()
	int32 Int32Value = 0;

	UPROPERTY()
	int64 Int64Value = 0;

	UPROPERTY()
	uint8 Uint8Value = 0;

	UPROPERTY()
	uint16 Uint16Value = 0;

	UPROPERTY()
	uint32 Uint32Value = 0;

	UPROPERTY()
	uint64 Uint64Value = 0;

	UPROPERTY()
	TEnumAsByte<EEnumTest1::Type> EnumValue1;

	UPROPERTY()
	TEnumAsByte<EEnumTest2> EnumValue2;

	UPROPERTY()
	EEnumTest3 EnumValue3;

	UPROPERTY()
	TObjectPtr<UTestObject> Test1 = nullptr;

	UPROPERTY()
	TObjectPtr<UTest2Object> Test2 = nullptr;

	UPROPERTY()
	TArray<FString> Array1;

	UPROPERTY()
	TArray<FMyTestDataInner> Array2;

	UPROPERTY()
	TMap<int32, int32> Map1;

	UPROPERTY()
	TMap<int32, FMyTestDataInner> Map2;

	UPROPERTY()
	FMyTestDataInner Inner;

};


/**
 *
 */
UCLASS()
class UMyObject : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FMyTestData TestData;

};
