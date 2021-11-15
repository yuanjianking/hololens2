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
//
////加载ImageWrapper模块，同时创建一个针对格式操作的辅助对象
//static TSharedPtr<IImageWrapper> GetImageWrapperByExtention(const FString InImagePath)
//{
//	IImageWrapperModule& ImageWrapperModule = FModuleManager::GetModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
//
//
//
//	if (InImagePath.EndsWith(".png"))
//	{
//		return ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
//	}
//	else if (InImagePath.EndsWith(".jpg") || InImagePath.EndsWith(".jpeg"))
//	{
//		return ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
//	}
//	else if (InImagePath.EndsWith(".bmp"))
//	{
//		return ImageWrapperModule.CreateImageWrapper(EImageFormat::BMP);
//	}
//	else if (InImagePath.EndsWith(".ico"))
//	{
//		return ImageWrapperModule.CreateImageWrapper(EImageFormat::ICO);
//	}
//	else if (InImagePath.EndsWith(".exr"))
//	{
//		return ImageWrapperModule.CreateImageWrapper(EImageFormat::EXR);
//	}
//	else if (InImagePath.EndsWith(".icns"))
//	{
//		return ImageWrapperModule.CreateImageWrapper(EImageFormat::ICNS);
//	}
//	return nullptr;
//}
//
//UTexture2D* DialogueBase::LoadTexture2DFromFile(const FString& FilePath, bool& IsValid, int32& Width, int32& Height)
//{
//
//	IsValid = false;
//	UTexture2D* LoadedT2D = NULL;
//
//
//	TSharedPtr<IImageWrapper> ImageWrapper = GetImageWrapperByExtention(FilePath);
//	//得到解压后的源数据
//	TArray<uint8> RawFileData;
//	if (!FFileHelper::LoadFileToArray(RawFileData, *FilePath, 0)) return NULL;
//
//	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
//	{
//		TArray<uint8> UncompressedBGRA;
//		//设置格式并获取未压缩的数据
//		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
//		{
//			//创建UTexture2D*
//			LoadedT2D = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);
//
//			if (!LoadedT2D) return NULL;
//			//得到高度和宽度
//			Width = ImageWrapper->GetWidth();
//			Height = ImageWrapper->GetHeight();
//			// 锁住他的数据  
//			void* TextureData = LoadedT2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
//			//获取纹理数据
//			FMemory::Memcpy(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
//			//解锁
//			LoadedT2D->PlatformData->Mips[0].BulkData.Unlock();
//
//			LoadedT2D->UpdateResource();
//		}
//	}
//
//	IsValid = true;
//	return LoadedT2D;
//}
//
//bool DialogueBase::ExportTextureRenderTarget2D2PNG(UTextureRenderTarget2D* TextureRenderTarget, const FString& FilePath)
//{
//
//	FTextureRenderTargetResource* rtResource = TextureRenderTarget->GameThread_GetRenderTargetResource();
//	FReadSurfaceDataFlags readPixelFlags(RCM_UNorm);
//
//	TArray<FColor> outBMP;
//
//	for (FColor& color : outBMP)
//	{
//		color.A = 255;
//	}
//	outBMP.AddUninitialized(TextureRenderTarget->GetSurfaceWidth() * TextureRenderTarget->GetSurfaceHeight());
//	rtResource->ReadPixels(outBMP, readPixelFlags);
//
//	FIntPoint destSize(TextureRenderTarget->GetSurfaceWidth(), TextureRenderTarget->GetSurfaceHeight());
//	TArray<uint8> CompressedBitmap;
//	FImageUtils::CompressImageArray(destSize.X, destSize.Y, outBMP, CompressedBitmap);
//	bool imageSavedOk = FFileHelper::SaveArrayToFile(CompressedBitmap, *FilePath);
//
//	return imageSavedOk;
//}