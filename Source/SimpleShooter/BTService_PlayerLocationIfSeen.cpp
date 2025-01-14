// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"

#include <BehaviorTree/BlackboardComponent.h>
#include <Kismet/GameplayStatics.h>

#include "ShooterAIController.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = "Update player location if seen";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard)
	{
		return;
	}

	AShooterAIController* Controller = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	if (!Controller)
	{
		return;
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn)
	{
		return;
	}

	if (Controller->LineOfSightTo(PlayerPawn))
	{
		Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
	}
	else
	{
		Blackboard->ClearValue(GetSelectedBlackboardKey());
	}
}
