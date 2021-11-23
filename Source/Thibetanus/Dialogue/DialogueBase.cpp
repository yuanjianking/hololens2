// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueBase.h"


DialogueBase::DialogueBase()
{
	
}

DialogueBase::~DialogueBase()
{
}

int DialogueBase::GetNextDialogue(USoundBase* inData, USoundBase* outData)
{
	outData = inData;
	return 0;
}

int DialogueBase::GetNextDialogue(int data)
{
	return data;
}

USoundBase* DialogueBase::GetNextDialogue(USoundBase* inData)
{
	

	return inData;
}