// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Interfaces/IHttpRequest.h"
#include "JsonFileDownLoad.generated.h"


USTRUCT(BlueprintType)
struct FNewsItem {
	GENERATED_USTRUCT_BODY()

	FNewsItem() {}
	FNewsItem(FString _key, FString _mount, FString _url)
		: key(_key), mount(_mount), url(_url) {}
	UPROPERTY(BlueprintReadOnly)
		FString key;
	UPROPERTY(BlueprintReadOnly)
		FString mount;
	UPROPERTY(BlueprintReadOnly)
		FString url;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRequestCompleteDelegate, const FNewsItem&, Data); 


/**
 * 
 */
UCLASS()
class THIBETANUS_API UJsonFileDownLoad : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
		
private:
	FString _key;

public:
	UJsonFileDownLoad();

public:
	UFUNCTION(BlueprintCallable, Category = "AsyncHttp", meta = (BlueprintInternalUseOnly = "true"))
	static UJsonFileDownLoad* AsyncHttpURLRequest(const FString& url, const FString& key);
	
	void HttpRequestStar(const FString& url, const FString& key);
	void HttpRequest_RecHandle(FHttpRequestPtr request, FHttpResponsePtr response, bool bWasSuccessful);
	
	
	UPROPERTY(BlueprintAssignable)
	FRequestCompleteDelegate OnSucceeded;
	
	
	UPROPERTY(BlueprintAssignable)
	FRequestCompleteDelegate OnFailed;

};
