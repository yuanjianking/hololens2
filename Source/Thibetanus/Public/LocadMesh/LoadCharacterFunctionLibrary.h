// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoadCharacterFunctionLibrary.generated.h"



UENUM(BlueprintType)
enum class EPathType : uint8
{
	Absolute,
	Relative
};


USTRUCT(BlueprintType)
struct FMeshInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
	TArray<FVector> Vertices;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
	TArray<int32> Triangles;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
	TArray<FVector> Normals;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
	TArray<FVector2D> UV0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
	TArray<FLinearColor> VertexColors;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
	TArray<FProcMeshTangent> Tangents;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
	FTransform RelativeTransform;
};

USTRUCT(BlueprintType)
struct FReturnedData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
	bool bSuccess;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
	int32 NumMeshes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReturnedData")
	TArray<FMeshInfo> meshInfo;

};


/**
 * 
 */
UCLASS()
class THIBETANUS_API ULoadCharacterFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Loader")
	static FReturnedData LoadMesh(FString filepath, EPathType type = EPathType::Absolute);

	//UFUNCTION(BlueprintCallable, Category = "Loader")
	//static TArray<FString> GetAllFilesInDirectory(const FString directory, const bool fullPath, const bool withoutExtention, const FString onlyFilesStartingWith, const FString onlyFilesWithExtension);
};
