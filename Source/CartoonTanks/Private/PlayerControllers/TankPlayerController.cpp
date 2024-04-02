// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/TankPlayerController.h"
#include "EnhancedInputSubsystems.h"

ATankPlayerController::ATankPlayerController()
{
}


void ATankPlayerController::BeginPlay()
{

    // Call the parent BeginPlay function
    Super::BeginPlay();

    // Check ifwe have a mapping context
    check(PlayerContext);

    // Hold the enchaned input subsystem for the local player
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

    // Check if we have an enhanced input subsystem
    check(Subsystem);

    // Add the mapping context
    Subsystem->AddMappingContext(PlayerContext, 0);
}

