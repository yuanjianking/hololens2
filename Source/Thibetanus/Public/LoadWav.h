// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoadWav.generated.h"

/**
 * 
 */
UCLASS()
class THIBETANUS_API ULoadWav : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	static USoundWave* LoadWaveDataFromFile(const FString& FilePath);
};
