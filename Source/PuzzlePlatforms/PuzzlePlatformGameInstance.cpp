// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Game instance init"));
}

void UPuzzlePlatformGameInstance::Init()
{
}

void UPuzzlePlatformGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	
	if (Engine == nullptr) {
		return;
	}

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();

	if (World == nullptr) {
		return;
	}
	
	FString URL = World->GetAddressURL();
	UE_LOG(LogTemp, Warning, TEXT("URL: %s"), *URL)

	World->ServerTravel("/Game/PuzzlePlatform/Maps/PuzzleMap?listen");
}

void UPuzzlePlatformGameInstance::Join(FString & Address)
{
	UEngine* Engine = GetEngine();

	if (Engine == nullptr) {
		return;
	}

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if (PlayerController == nullptr) {
		return;
	}

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
