// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"




void UTankTurret::Rotate(float RelativeSpeed) 
{
	auto RelativeSpeedClamped = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationnChange = RelativeSpeedClamped * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationnChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));
}