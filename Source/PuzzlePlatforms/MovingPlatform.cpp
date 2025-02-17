// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {

	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);

	TargetLocation = FVector(0, 0, 100);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveTriggers <= 0) {
		return;
	}

	if (HasAuthority()) {
		FVector Location = GetActorLocation();

		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float JourneyTravelledLength = (Location - GlobalStartLocation).Size();

		if (JourneyTravelledLength >= JourneyLength) {
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
		}

		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += Speed * DeltaTime * Direction;
		SetActorLocation(Location);
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	if (ActiveTriggers <= 0) {
		ActiveTriggers = 1;
	}
	else {
		ActiveTriggers++;
	}
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0) {
		ActiveTriggers--;
	}
}
