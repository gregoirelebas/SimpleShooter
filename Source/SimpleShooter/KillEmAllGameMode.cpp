// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include <EngineUtils.h>
#include "ShooterAIController.h"

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

	bool IsPlayerDead = Cast<APlayerController>(PawnKilled->GetController()) != nullptr;
	if (IsPlayerDead)
	{
		EndGame(false);
	}
	else
	{
		bool AreAllDead = true;
		for (AShooterAIController* ShooterAIController : TActorRange<AShooterAIController>(GetWorld()))
		{
			if (!ShooterAIController->IsDead()) //One of them is still alive
			{
				AreAllDead = false;
				break;
			}
		}

		if (AreAllDead)
		{
			EndGame(true);
		}
	}
}
