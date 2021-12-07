// Fill out your copyright notice in the Description page of Project Settings.


#include "APKFileDownLoad.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "IPlatformFilePak.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/CoreDelegates.h"
#include <stdio.h>

UAPKFileDownLoad::UAPKFileDownLoad()
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		AddToRoot();
	}
}



UAPKFileDownLoad* UAPKFileDownLoad::AsyncHttpDownload(const FString& url, const FString& mount)
{
	UAPKFileDownLoad* AsyncHttpObject = NewObject<UAPKFileDownLoad>();
	AsyncHttpObject->DownloadRequestStart(url, mount);
	return AsyncHttpObject;
}


void UAPKFileDownLoad::DownloadRequestStart(const FString& url, const FString& mount)
{
	this->_mount = mount;
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> request = FHttpModule::Get().CreateRequest();
	request->SetVerb("GET");
	request->SetURL(url);
	request->OnProcessRequestComplete().BindUObject(this, &UAPKFileDownLoad::DownloadRequestHandle);
	request->OnRequestProgress().BindUObject(this, &UAPKFileDownLoad::DownloadProgress);
	request->ProcessRequest();

	RemoveFromRoot(); 
}


void UAPKFileDownLoad::DownloadRequestHandle(FHttpRequestPtr request, FHttpResponsePtr response, bool bWasSuccessful)
{
	RemoveFromRoot();


	if (bWasSuccessful && response.IsValid() && EHttpResponseCodes::IsOk(response->GetResponseCode()))
	{
		if (response->GetContentLength() > 0) {
			TArray<uint8> EmptyData;
			OnProgressUpdate.Broadcast(response->GetContentLength(), response->GetContentLength(), EmptyData);
		}

		//	FString FileSavePath = FPaths::EngineDir() + "Content/http/MariaMat.uasset";
		FString FileSavePath = FPaths::ProjectDir() + "Content/http/test.apk";
		FString Path, Filename, Extension;
		FPaths::Split(FileSavePath, Path, Filename, Extension);
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();


		if (!PlatformFile.DirectoryExists(*Path))
		{
			if (!PlatformFile.CreateDirectoryTree(*Path))
			{
				UE_LOG(LogTemp, Error, TEXT("Create Directory Failed!"));
				OnFailed.Broadcast();
				return;
			}
		}

		IFileHandle* FileHandle = PlatformFile.OpenWrite(*FileSavePath);
		if (FileHandle)
		{
			FileHandle->Write(response->GetContent().GetData(), response->GetContentLength());
			delete FileHandle;


		//	FString mountPath = FPaths::ProjectContentDir() + "maria/";

			FString mountPath = FPaths::ProjectContentDir() + this->_mount + "/";
			TCHAR Character[256];
			swprintf(Character, TEXT("Blueprint'/Game/%ls/B.B_C'"), *(this->_mount));

			FPakPlatformFile* pakFile = (FPakPlatformFile*)(FPlatformFileManager::Get().FindPlatformFile(FPakPlatformFile::GetTypeName()));
			if (pakFile != nullptr)
			{
				if (pakFile->Mount(*FileSavePath, 4, *mountPath))
				{

					UClass* Test = LoadClass<AActor>(NULL, Character);

					if (Test != nullptr)
					{
						UE_LOG(LogTemp, Warning, TEXT("AActor\n"));
						UWorld* MyWorld = GEngine->GetWorldContexts()[0].World();

						if (MyWorld)
						{
							MyWorld->SpawnActor<AActor>(Test, FVector(410.0f, 300.0f, -4.0f), FRotator(0.f));
							UE_LOG(LogTemp, Warning, TEXT("UWorld\n"));
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT("no UWorld\n"));
						}

					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("no AActor\n"));
					}

				}
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("no FPakPlatformFile\n"));


			/*if (FCoreDelegates::MountPak.IsBound())
			{
				UE_LOG(LogTemp, Warning, TEXT("LoadPakDelegate(): OnMountPak.IsBound()"));
				IPakFile* pakFile = FCoreDelegates::MountPak.Execute(FileSavePath, 4);
				if (pakFile)
				{
					const auto& mountPoint = pakFile->PakGetMountPoint();
					UE_LOG(LogTemp, Warning, TEXT("LoadPakDelegate(): MountPoint %s"), *mountPoint);
					FString pakContentPath = mountPoint + "MyProject1/Content/";
					FPackageName::RegisterMountPoint("/Game/", pakContentPath);

					UClass* Test = LoadClass<AActor>(NULL, TEXT("Blueprint'/Game/test/B.B_C'"));

					if (Test != nullptr)
						GetWorld()->SpawnActor(Test);
					else
						UE_LOG(LogTemp, Warning, TEXT("no AActor\n"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("LoadPakDelegate(): OnMountPak.IsBound() Falied"));
			}*/

			OnSucceeded.Broadcast();
			return;
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Save File Failed!"));
			OnFailed.Broadcast();
			return;
		}

	}
	UE_LOG(LogTemp, Error, TEXT("download File Failed!"));
	OnFailed.Broadcast();
	return;
}


void UAPKFileDownLoad::DownloadProgress(FHttpRequestPtr request, int32 bytesSent, int32 bytesReceived)
{
	if (request->GetResponse()->GetContentLength() > 0)
	{
		TArray<uint8> EmptyData;
		OnProgressUpdate.Broadcast(bytesReceived, request->GetResponse()->GetContentLength(), EmptyData);
	}
}