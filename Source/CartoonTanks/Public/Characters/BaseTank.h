// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseTank.generated.h"

UCLASS()
class CARTOONTANKS_API ABaseTank : public ACharacter
{
	GENERATED_BODY()

public:
	
	// Sets default values for this character's properties
	ABaseTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Hold the tank name
	UPROPERTY(EditDefaultsOnly, Category = "Specs")
	FString TankName;

	// Hold the move speed of the tank
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Specs")
	float MoveSpeed = 0.0f;
	
	// Hold the turn speed of the tank
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Specs")
	float TurnSpeed = 0.0f;

	// Hold the projectile template
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Specs", meta = (AllowPrivateAccess= "true"))
	TSubclassOf<class ATankProjectile> ProjectileClass;

	// Hold the delta location
	UPROPERTY(BlueprintReadWrite, Category = "Input")
	FVector DeltaLocation = FVector(0.f);
	
	// Hold the delta rotation
	UPROPERTY(BlueprintReadWrite, Category = "Input")
	FRotator DeltaRotation = FRotator(0.f);

	// Hold the pointer to the tank's projectile spawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess= "true"))
	USceneComponent* ProjectileSpawnComponent;

	// Hold if the tank is alive
	UPROPERTY(BlueprintReadWrite, Category = "CharacterState")
	bool IsTankAlive = true;

	/*
	Handle the destructionof the pawn
	@param none
	@return void
	*/
	UFUNCTION(BlueprintCallable, Category = "CharacterState")
	void HandlePawnDestruction();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Hold the pointer to the spring arm component
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArmComponent;

	// Hold the pointer to the camera component
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* CameraComponent;

	// Hold the death particles for the tank
	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* DeathParticles;

	// Hold the sound for the tank death
	UPROPERTY(EditAnywhere, Category = "Effects")
	class USoundBase* DeathSound;

	// Hold the camera shake
	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<class UCameraShakeBase> CameraShakeClass;
};
