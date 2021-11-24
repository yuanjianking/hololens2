// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DialogueBaseFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class THIBETANUS_API UDialogueBaseFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	USoundBase* base;

public:
	UFUNCTION(BlueprintCallable,Category="Dialogue")
	static USoundWave* LoadWaveDataFromFile(const FString& FilePath);
	
};
