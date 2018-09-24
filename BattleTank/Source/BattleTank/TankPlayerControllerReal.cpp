// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerControllerReal.h"
#include "Tank.h"
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

void ATankPlayerControllerReal::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerControllerReal::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
 }

void ATankPlayerControllerReal::AimTowardsCrosshair() {
	if (!GetControlledTank()){return; }

	FVector HitLocation; //Out Paramater
	if (GetSightRayHitLocation(HitLocation)) {//Has a "side-effect", is going to line trace
		
		GetControlledTank()->AimAt(HitLocation);
	}
	

}

//Get World location of linetrace through crosshair, true if hits landscape
bool ATankPlayerControllerReal::GetSightRayHitLocation(FVector& OutHitLocation) const{
	
	//Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	FVector LookDirection;
	//"De-project" the screen position of the crosshair to a world direction
	if (GetLookDirection(ScreenLocation, LookDirection)) {

		//Line-trace along that LookDirection, and see what we hit (up to max range
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return true;
}

bool ATankPlayerControllerReal::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		//Set hit location
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

bool ATankPlayerControllerReal::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const{
	FVector CameraWorldLocation;// To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

