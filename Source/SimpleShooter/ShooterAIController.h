// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* AIBehavior;

public:
	void BeginPlay() override;

	bool IsDead() const;
};
