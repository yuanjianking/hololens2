// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Interfaces/IHttpRequest.h"
#include "APKFileDownLoad.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDownloadProgressDelegate,
const int32&, ReceivedDataInBytes,
const int32&, TotalDataInBytes,
const TArray<uint8>&, BinaryData
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDownloadDelegate);


/**
 * 
 */
UCLASS()
class THIBETANUS_API UAPKFileDownLoad : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

private:
	FString _mount;

public:
	UAPKFileDownLoad();


public:
	UFUNCTION(BlueprintCallable, Category = "AsyncHttp", meta = (BlueprintInternalUseOnly = "true"))
		static UAPKFileDownLoad* AsyncHttpDownload(const FString& url, const FString& mount);

	void DownloadRequestStart(const FString& url, const FString& mount);
	void DownloadRequestHandle(FHttpRequestPtr request, FHttpResponsePtr response, bool bWasSuccessful);
	void DownloadProgress(FHttpRequestPtr request, int32 bytesSent, int32 bytesReceived);


	UPROPERTY(BlueprintAssignable)
		FDownloadProgressDelegate OnProgressUpdate; 


	UPROPERTY(BlueprintAssignable)
		FDownloadDelegate OnSucceeded;


	UPROPERTY(BlueprintAssignable)
		FDownloadDelegate OnFailed;
};
