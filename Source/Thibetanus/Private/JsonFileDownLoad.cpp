// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonFileDownLoad.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "IPlatformFilePak.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/CoreDelegates.h"

UJsonFileDownLoad::UJsonFileDownLoad()
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		AddToRoot();
	}
}


UJsonFileDownLoad* UJsonFileDownLoad::AsyncHttpURLRequest(const FString& url, const FString& key) {	
	UJsonFileDownLoad* AsyncHttpObject = NewObject<UJsonFileDownLoad>();
	AsyncHttpObject->HttpRequestStar(url, key);
	return AsyncHttpObject;
}


void UJsonFileDownLoad::HttpRequestStar(const FString& url, const FString& key)
{
	this->_key = key;
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> request = FHttpModule::Get().CreateRequest();
	request->SetVerb("GET");
	request->SetURL(url);
	//request->SetHeader(TEXT("Content-Type"), TEXT("application/json;charset=utf-8"));
	//request->SetTimeout(200);
	//request->SetContentAsString(requestJsonStr); POST时候用
	//request->OnRequestProgress().BindUObject() 绑定进度
	request->OnProcessRequestComplete().BindUObject(this, &UJsonFileDownLoad::HttpRequest_RecHandle); //请求回调
	request->ProcessRequest();
}

void UJsonFileDownLoad::HttpRequest_RecHandle(FHttpRequestPtr request, FHttpResponsePtr response, bool bWasSuccessful) {


	if (bWasSuccessful && response.IsValid() && EHttpResponseCodes::IsOk(response->GetResponseCode())) {
		TSharedPtr<FJsonObject> jsonObj;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(response->GetContentAsString());

		if (FJsonSerializer::Deserialize(JsonReader, jsonObj)) {
			const TArray< TSharedPtr<FJsonValue> >* dataList;
			if (jsonObj->TryGetArrayField(TEXT("list"), dataList)) 
			{
			//	TArray<FNewsItem> newsList;
				for (TSharedPtr<FJsonValue> item : *dataList)
				{
					TSharedPtr<FJsonObject>itemObjet = item->AsObject();

					if (itemObjet->GetStringField(TEXT("key")).Equals(this->_key))
					{					
						OnSucceeded.Broadcast(FNewsItem(
							itemObjet->GetStringField(TEXT("key")),
							itemObjet->GetStringField(TEXT("mount")),
							itemObjet->GetStringField(TEXT("url"))
						));
						break;
					}
				}
				
				RemoveFromRoot();
				return;
			}
		}
	}
	OnFailed.Broadcast({}); 
	RemoveFromRoot();
}

