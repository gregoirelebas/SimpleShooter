// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("Killed a pawn!"));
}
