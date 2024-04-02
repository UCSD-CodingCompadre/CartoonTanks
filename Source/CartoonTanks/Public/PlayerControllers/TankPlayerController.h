// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class CARTOONTANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	// Default constructor
	ATankPlayerController();

protected:

	/*
	Handles setting up the enchaned input subsystem and input mode data
	@param none
	@return void
	*/
	virtual void BeginPlay() override;

private:

	// Hold the mapping context
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerContext;
};
