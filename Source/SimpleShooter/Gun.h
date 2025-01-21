// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ImpactShotEffect;

	UPROPERTY(EditAnywhere)
	float ShootRange = 1000.0f;

	UPROPERTY(EditAnywhere)
	float Damage = 10.0f;

private:
	AController* GetOwnerController() const;

	bool TryGunTrace(FHitResult& HitResult, FVector& ShootDirection);

public:	
	void Shoot();
};
