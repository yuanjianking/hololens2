// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class THIBETANUS_API DialogueBase
{
public:
	DialogueBase();
	~DialogueBase();


public:
	int GetNextDialogue(int data);
	int GetNextDialogue(USoundBase * inData, USoundBase * outData);
	USoundBase * GetNextDialogue(USoundBase* inData);

};
