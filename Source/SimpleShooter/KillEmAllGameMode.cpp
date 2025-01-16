// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include <EngineUtils.h>

void AKillEmAllGameMode::EndGame(bool HasPlayerWon)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool HasWon = Controller->IsPlayerController() == HasPlayerWon;
		Controller->GameHasEnded(Controller->GetPawn(), HasWon);
	}
}

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	bool HasPlayerWon = Cast<APlayerController>(PawnKilled->GetController()) == nullptr;
	EndGame(HasPlayerWon);
}
