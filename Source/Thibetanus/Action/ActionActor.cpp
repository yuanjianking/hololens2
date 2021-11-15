// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionActor.h"

// Sets default values
AActionActor::AActionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

