// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoadMaterial.generated.h"

/**
 * 
 */
UCLASS()
class THIBETANUS_API ULoadMaterial : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Texture")
	static UTexture2D* LoadTexture2DFromFile(const FString& FilePath, bool& IsValid, int32& Width, int32& Height);

	UFUNCTION(BlueprintCallable, Category = "Texture")
	static UMaterial* CreateMaterial(const FString& FilePath);

	UFUNCTION(BlueprintCallable, Category = "Texture")
	static bool ExportTextureRenderTarget2D2PNG(UTextureRenderTarget2D* TextureRenderTarget, const FString& FilePath);


};
