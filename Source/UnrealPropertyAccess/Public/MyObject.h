// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"


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
