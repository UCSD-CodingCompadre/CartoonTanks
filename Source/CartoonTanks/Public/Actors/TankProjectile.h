// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TankProjectile.generated.h"

UCLASS()
class CARTOONTANKS_API ATankProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ATankProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Hold the pointer to the projectile mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess= "true"))
	UStaticMeshComponent* ProjectileComponent;
	
	// Hold the pointer to the projectile movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess= "true"))
	UProjectileMovementComponent* ProjectileMovementComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


	// Hold the damage of the projectile
	UPROPERTY(EditAnywhere)
	float damage = 50.f;

	// Hold the particle system for the projectile
	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* HitParticles;

	// Hold the particle system component for the projectile trail
	UPROPERTY(VisibleAnywhere, Category = "Effects")
	class UParticleSystemComponent* TrailParticles;

	// Hold the sound for the projectile
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* LaunchSound;

	// Hold the sound for the hit
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* HitSound;

	// Hold the camera shake
	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

	/*
	Callback function that handles the projectile hitting an actor
	@param UPrimitiveComponent* hitComponent the component that caused the hit
	AActor* actorHit the actor hit by the hitComponent
	UPrimitiveComponent* otherComponent the component of the actor hit
	FVector impulse the impulse of the hit event
	FHitResult hit the hit event of caused by the projectile
	@return void
	*/
	UFUNCTION()
	void onHit(UPrimitiveComponent* hitComponent, AActor* actorHit, 
	UPrimitiveComponent* otherComponent, FVector impluse, const FHitResult& hit);


};
