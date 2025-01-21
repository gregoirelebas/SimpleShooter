// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return nullptr;

	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr)
		return nullptr;

	return OwnerController;
}

bool AGun::TryGunTrace(FHitResult& HitResult, FVector& ShotDirection)
{
	FVector Location;
	FRotator Rotation;
	GetOwnerController()->GetPlayerViewPoint(Location, Rotation);

	ShotDirection = Location + Rotation.Vector() * ShootRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(HitResult, Location, ShotDirection, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

void AGun::Shoot()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult HitResult;
	FVector ShotDirection;

	bool HasShotHit = TryGunTrace(HitResult, ShotDirection);
	if (HasShotHit)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactShotEffect, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitResult.ImpactPoint);

		AActor* HitActor = HitResult.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent = FPointDamageEvent(Damage, HitResult, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), Owner);
		}
	}
}
