// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <Kismet/GameplayStatics.h>

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = TEXT("Update player location");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard)
	{
		return;
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn)
	{
		return;
	}

	Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
}
