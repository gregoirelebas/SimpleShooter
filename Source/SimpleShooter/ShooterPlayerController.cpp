// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include <Blueprint/UserWidget.h>

void AShooterPlayerController::DisplayEndScreen(TSubclassOf<UUserWidget> EndScreenClass)
{
	if (EndScreenClass)
	{
		UUserWidget* EndScreen = CreateWidget(this, EndScreenClass, TEXT("End screen"));
		if (EndScreen)
		{
			EndScreen->AddToViewport();
		}
	}
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (HUDScreenClass)
	{
		HUDScreen = CreateWidget(this, HUDScreenClass, TEXT("HUD"));
		if (HUDScreen)
		{
			HUDScreen->AddToViewport();
		}
	}
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Game as ended"));

	FTimerHandle RestartTimer;
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

	if (HUDScreen)
	{
		HUDScreen->RemoveFromViewport();
	}

	if (bIsWinner)
	{
		DisplayEndScreen(WinScreenClass);
	}
	else
	{
		DisplayEndScreen(LooseScreenClass);
	}
}
