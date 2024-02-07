# UnrealPropertyAccess

UnrealEngineで、未改造エンジンを扱う場合にはプロパティ経由で値にアクセスを求められるケースが多いです。  
UObjectのメンバ変数の構造体のetc...と続いていくとプロパティ経由でのアクセスがしんどいです。  
アクセスを簡単にする為の1ヘッダーライブラリを用意しました。

> Source/UnrealPropertyAccess/Public/UnrealReadPropertyAccesser.h

# 使用例

## テストデータ

```cpp

USTRUCT()
struct FMyTestDataInner
{
	GENERATED_BODY()
public:
	UPROPERTY()
	bool BoolValue = 0;
};

USTRUCT()
struct FMyTestData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FMyTestDataInner Inner;
};

UCLASS()
class UMyObject : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FMyTestData TestData;
};

```

## 通常の場合

```cpp

void Test(UMyObject* InObject)
{
	FStructProperty* TestDataProperty = FindFProperty<FStructProperty>(UMyObject::StaticClass(), TEXT("TestData"));

    FStructProperty* InnerProperty = FindFProperty<FStructProperty>(FMyTestData::StaticStruct(), TEXT("Inner"));

    FBoolProperty* BoolValueProperty = FindFProperty<FBoolProperty>(FMyTestDataInner::StaticStruct(), TEXT("BoolValue"));

    if(TestDataProperty == nullptr || InnerProperty == nullptr || BoolValueProperty == nullptr)
    {
        // プロパティが見つからないので失敗
        return;
    }

    // プロパティ経由でのアクセスをする
	FMyTestData* TestData = TestDataProperty->ContainerPtrToValuePtr<FMyTestData>(InObject);
	FMyTestDataInner* Inner = InnerProperty->ContainerPtrToValuePtr<FMyTestDataInner>(TestData);
	bool* BoolValue = BoolValueProperty->ContainerPtrToValuePtr<bool>(BoolValue);
}


```

## UnrealPropertyAccessを使った場合

```cpp

void Test(UMyObject* InObject)
{
    UE::ReadProperty<FMyTestData>(&InObject, TEXT("TestData"))
		.ReadProperty<FMyTestDataInner>(TEXT("Inner"))
		.ReadProperty<bool>(TEXT("BoolValue"))
		.Execute([](bool BoolValue)
		{
            // 正常に動作する場合にはこのコールバック関数が呼ばれます
		});
}


```