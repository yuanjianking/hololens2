// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueBase.h"
#include "GameFramework/Actor.h"
#include "DialogueActor.generated.h"



UCLASS()
class THIBETANUS_API ADialogueActor : public AActor, public DialogueBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogueActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	USoundBase* base;
public:
	UFUNCTION(BlueprintCallable)
	int test();


	UFUNCTION(BlueprintCallable)
	int test1(USoundBase* inData, USoundBase* outData);

	UFUNCTION(BlueprintCallable)
	USoundBase* test2(USoundBase* inData);

	UFUNCTION(BlueprintCallable)
		USoundWave* LoadWaveDataFromFile(const FString& FilePath);
};
