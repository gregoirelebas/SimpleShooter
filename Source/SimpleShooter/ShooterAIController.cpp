// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include <Kismet/GameplayStatics.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardComponent.h>

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);

		Blackboard = GetBlackboardComponent();
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		if (Blackboard)
		{
			Blackboard->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		}
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Blackboard && PlayerPawn)
	{
		if (LineOfSightTo(PlayerPawn))
		{
			Blackboard->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
			Blackboard->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
		}
		else
		{
			Blackboard->ClearValue(TEXT("PlayerLocation"));
		}
	}
}
