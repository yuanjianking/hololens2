// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/DialogueBaseFunctionLibrary.h"



//static ConstructorHelpers::FObjectFinder<USoundWave> SWBattleBGM(TEXT("SoundWave'/Game/wavs/xiongxiong.xiongxiong'"));
//
//base = SWBattleBGM.Object;
//if (base)
//{
//	UGameplayStatics::PlaySound2D(GetWorld(), base);
//
//}
//USoundWave* sw = LoadWaveDataFromFile(TEXT("C:\\Users\\MI\\Downloads\\xiongxiong.wav"));
//if (sw->IsPlayable())
//{
//	return sw;
//}
//



USoundWave* UDialogueBaseFunctionLibrary::LoadWaveDataFromFile(const FString& FilePath)
{
	USoundWave* sw = NewObject<USoundWave>(USoundWave::StaticClass());

	if (!sw)
		return nullptr;


	TArray < uint8 > rawFile;

	FFileHelper::LoadFileToArray(rawFile, FilePath.GetCharArray().GetData());
	FWaveModInfo WaveInfo;

	if (WaveInfo.ReadWaveInfo(rawFile.GetData(), rawFile.Num()))
	{
		sw->RawData.Lock(LOCK_READ_WRITE);
		void* LockedData = sw->RawData.Realloc(rawFile.Num());
		FMemory::Memcpy(LockedData, rawFile.GetData(), rawFile.Num());
		sw->RawData.Unlock();

		int32 DurationDiv = *WaveInfo.pChannels * *WaveInfo.pBitsPerSample * *WaveInfo.pSamplesPerSec;
		if (DurationDiv)
		{
			sw->Duration = *WaveInfo.pWaveDataSize * 8.0f / DurationDiv;
		}
		else
		{
			sw->Duration = 0.0f;
		}

		sw->SetSampleRate(*WaveInfo.pSamplesPerSec);
		sw->NumChannels = *WaveInfo.pChannels;
		sw->RawPCMDataSize = WaveInfo.SampleDataSize;
		sw->SoundGroup = ESoundGroup::SOUNDGROUP_Default;


		UE_LOG(LogTemp, Log, TEXT("SW NumChannels-> %i"), sw->NumChannels);
		UE_LOG(LogTemp, Log, TEXT("SW Duration-> %f"), sw->Duration);
		UE_LOG(LogTemp, Log, TEXT("SW RawPCMDataSize-> %i"), sw->RawPCMDataSize);
		UE_LOG(LogTemp, Log, TEXT("SW SampleRate-> %u"), sw->__PPO__SampleRate);

		//	UGameplayStatics::PlaySound2D(GetWorld(), sw);
	}
	else {
		return nullptr;
	}

	return sw;
}
