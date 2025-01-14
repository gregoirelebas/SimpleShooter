// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include <Kismet/GameplayStatics.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardComponent.h>

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		Blackboard = GetBlackboardComponent();
		if (PlayerPawn && Blackboard != nullptr)
		{
			Blackboard->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		}
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerPawn != nullptr)
	{
		if (LineOfSightTo(PlayerPawn))
		{
			MoveToActor(PlayerPawn, AcceptanceRadius);
			SetFocus(PlayerPawn);
		}
		else
		{
			StopMovement();
			ClearFocus(EAIFocusPriority::Default);
		}
	}
}
