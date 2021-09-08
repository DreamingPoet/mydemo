// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ESpectBPFLibrary.generated.h"


using std::string;
/**
 *
 */
UCLASS()
class ESPECTSDK_API UESpectBPFLibrary : public UBlueprintFunctionLibrary 
{
	GENERATED_BODY()

public: 

	//打开文件管理器
	UFUNCTION(BlueprintCallable, Category = "FilePicker")
		static FString OpenFileDialog();

	
};

