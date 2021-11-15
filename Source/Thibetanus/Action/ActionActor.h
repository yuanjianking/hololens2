// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionBase.h"
#include "GameFramework/Actor.h"
#include "ActionActor.generated.h"

UCLASS()
class THIBETANUS_API AActionActor : public AActor, public ActionBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
