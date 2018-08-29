// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerControllerReal.h"
#include "BattleTank.h"


void ATankPlayerControllerReal::BeginPlay()
{
	Super::BeginPlay();
	
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}
	
}


ATank* ATankPlayerControllerReal::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
 }