// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadMaterial.h"
#include "UObject/UObjectGlobals.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "ImageUtils.h"
#include "Engine/TextureRenderTarget2D.h"
//#include "Factories/MaterialFactoryNew.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/FileHelper.h"

//加载ImageWrapper模块，同时创建一个针对格式操作的辅助对象
TSharedPtr<IImageWrapper> GetImageWrapperByExtention(const FString InImagePath)
{
	IImageWrapperModule& ImageWrapperModule = FModuleManager::GetModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));



	if (InImagePath.EndsWith(".png"))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
	}
	else if (InImagePath.EndsWith(".jpg") || InImagePath.EndsWith(".jpeg"))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
	}
	else if (InImagePath.EndsWith(".bmp"))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::BMP);
	}
	else if (InImagePath.EndsWith(".ico"))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::ICO);
	}
	else if (InImagePath.EndsWith(".exr"))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::EXR);
	}
	else if (InImagePath.EndsWith(".icns"))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::ICNS);
	}
	return nullptr;
}

UTexture2D* ULoadMaterial::LoadTexture2DFromFile(const FString& FilePath, bool& IsValid, int32& Width, int32& Height)
{

	IsValid = false;
	UTexture2D* LoadedT2D = NULL;


	TSharedPtr<IImageWrapper> ImageWrapper = GetImageWrapperByExtention(FilePath);
	//得到解压后的源数据
	TArray<uint8> RawFileData;
	if (!FFileHelper::LoadFileToArray(RawFileData, *FilePath, 0)) return NULL;

	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
	{
		TArray<uint8> UncompressedBGRA;
		//设置格式并获取未压缩的数据
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			//创建UTexture2D*
			LoadedT2D = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

			if (!LoadedT2D) return NULL;
			//得到高度和宽度
			Width = ImageWrapper->GetWidth();
			Height = ImageWrapper->GetHeight();
			// 锁住他的数据  
			void* TextureData = LoadedT2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			//获取纹理数据
			FMemory::Memcpy(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
			//解锁
			LoadedT2D->PlatformData->Mips[0].BulkData.Unlock();

			LoadedT2D->UpdateResource();
		}
	}

	IsValid = true;
	return LoadedT2D;


}
UMaterial* ULoadMaterial::CreateMaterial(const FString& FilePath)
{
	/*FString MaterialBaseName = "Plane";
	FString PackageName = "/Game/materials/";
	PackageName += MaterialBaseName;
	UPackage* Package = CreatePackage(*PackageName);*/

	// Create an unreal material asset
	//UMaterialFactoryNew * MaterialFactory = NewObject<UMaterialFactoryNew>();
//	UMaterial* UnrealMaterial = (UMaterial*)MaterialFactory->FactoryCreateNew(UMaterial::StaticClass(), Package, TEXT("test"), RF_Standalone | RF_Public, NULL, GWarn);

	UMaterial* UnrealMaterial = UMaterial::GetDefaultMaterial(MD_Surface);
	FAssetRegistryModule::AssetCreated(UnrealMaterial);
	//Package->FullyLoad();
	//Package->SetDirtyFlag(true);

	////UE_LOG(LogTemp, Warning, Package->yo);
	bool IsValid;
	int32 Width;
	int32 Height;
	UTexture2D* diffuse = LoadTexture2DFromFile(FilePath + "/diffuse.png", IsValid, Width, Height);
	UTexture2D* normal = LoadTexture2DFromFile(FilePath + "/normal.png", IsValid, Width, Height);
	UTexture2D* specular = LoadTexture2DFromFile(FilePath + "/specular.png", IsValid, Width, Height);

	UMaterialExpressionTextureSample* TextureExpressionDiffuse = NewObject<UMaterialExpressionTextureSample>(UnrealMaterial);
	TextureExpressionDiffuse->Texture = diffuse;
	TextureExpressionDiffuse->SamplerType = SAMPLERTYPE_Color;


	UMaterialExpressionTextureSample* TextureExpressionNormal = NewObject<UMaterialExpressionTextureSample>(UnrealMaterial);
	TextureExpressionNormal->Texture = normal;
	TextureExpressionNormal->SamplerType = SAMPLERTYPE_Color;


	UMaterialExpressionTextureSample* TextureExpressionSpecular = NewObject<UMaterialExpressionTextureSample>(UnrealMaterial);
	TextureExpressionSpecular->Texture = specular;
	TextureExpressionSpecular->SamplerType = SAMPLERTYPE_Color;

	UnrealMaterial->Expressions.Add(TextureExpressionDiffuse);
	UnrealMaterial->Expressions.Add(TextureExpressionNormal);
	UnrealMaterial->Expressions.Add(TextureExpressionSpecular);
	UnrealMaterial->BaseColor.Expression = TextureExpressionDiffuse;
	UnrealMaterial->Normal.Expression = TextureExpressionNormal;
	UnrealMaterial->Specular.Expression = TextureExpressionSpecular;



	//// Tiling system
	//UMaterialExpressionMultiply* Multiply = NewObject<UMaterialExpressionMultiply>(UnrealMaterial);
	//UnrealMaterial->Expressions.Add(Multiply);

	//// Diffuse
	//FStringAssetReference DiffuseAssetPath("/Game/T_Texture");
	//UTexture* DiffuseTexture = Cast<UTexture>(DiffuseAssetPath.TryLoad());
	//if (DiffuseTexture)
	//{
	//	// make texture sampler
	//	UMaterialExpressionTextureSample* TextureExpression = NewObject<UMaterialExpressionTextureSample>(UnrealMaterial);
	//	TextureExpression->Texture = DiffuseTexture;
	//	TextureExpression->SamplerType = SAMPLERTYPE_Color;
	//	UnrealMaterial->Expressions.Add(TextureExpression);
	//	UnrealMaterial->BaseColor.Expression = TextureExpression;

	//	// Tiling
	//	TextureExpression->Coordinates.Expression = Multiply;
	//}


	//// Tiling
	//UMaterialExpressionAppendVector* Append = NewObject<UMaterialExpressionAppendVector>(UnrealMaterial);
	//UnrealMaterial->Expressions.Add(Append);
	//Multiply->B.Expression = Append;
	//UMaterialExpressionTextureCoordinate* TexCoords = NewObject<UMaterialExpressionTextureCoordinate>(UnrealMaterial);
	//UnrealMaterial->Expressions.Add(TexCoords);
	//Multiply->A.Expression = TexCoords;
	//UMaterialExpressionScalarParameter* XParam = NewObject<UMaterialExpressionScalarParameter>(UnrealMaterial);
	//UMaterialExpressionScalarParameter* YParam = NewObject<UMaterialExpressionScalarParameter>(UnrealMaterial);
	//UnrealMaterial->Expressions.Add(XParam);
	//UnrealMaterial->Expressions.Add(YParam);
	//XParam->ParameterName = "TextureRepeatX";
	//XParam->DefaultValue = 1;
	//YParam->ParameterName = "TextureRepeatY";
	//YParam->DefaultValue = 1;
	//Append->A.Expression = XParam;
	//Append->B.Expression = YParam;



	UnrealMaterial->PreEditChange(NULL);
	UnrealMaterial->PostEditChange();
//	FGlobalComponentReregisterContext RecreateComponents;
	return UnrealMaterial;
}
//RenderTarget2D导出成本地图片
bool ULoadMaterial::ExportTextureRenderTarget2D2PNG(UTextureRenderTarget2D* TextureRenderTarget, const FString& FilePath)
{

	FTextureRenderTargetResource* rtResource = TextureRenderTarget->GameThread_GetRenderTargetResource();
	FReadSurfaceDataFlags readPixelFlags(RCM_UNorm);

	TArray<FColor> outBMP;

	for (FColor& color : outBMP)
	{
		color.A = 255;
	}
	outBMP.AddUninitialized(TextureRenderTarget->GetSurfaceWidth() * TextureRenderTarget->GetSurfaceHeight());
	rtResource->ReadPixels(outBMP, readPixelFlags);

	FIntPoint destSize(TextureRenderTarget->GetSurfaceWidth(), TextureRenderTarget->GetSurfaceHeight());
	TArray<uint8> CompressedBitmap;
	FImageUtils::CompressImageArray(destSize.X, destSize.Y, outBMP, CompressedBitmap);
	bool imageSavedOk = FFileHelper::SaveArrayToFile(CompressedBitmap, *FilePath);

	return imageSavedOk;
}