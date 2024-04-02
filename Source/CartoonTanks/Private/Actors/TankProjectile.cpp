// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TankProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ATankProjectile::ATankProjectile()
{

	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create a scene component for the root
	USceneComponent* RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));

	// Set the root component to the scene component
	RootComponent = RootScene;

	// Set the projectile component
	ProjectileComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	ProjectileComponent->SetupAttachment(RootComponent);

	// Set the projectile movement component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile_Movement"));

	// Create the trail particles
	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle_Trail"));
	TrailParticles->SetupAttachment(RootComponent);

	// Set the max speed
	ProjectileMovementComponent->MaxSpeed = 5000.f;

	// Set the initial speed
	ProjectileMovementComponent->InitialSpeed = 5000.f;

}

// Called when the game starts or when spawned
void ATankProjectile::BeginPlay()
{

	// Call the parent BeginPlay method
	Super::BeginPlay();
	
	// Add the onHit function to the projectile component
	ProjectileComponent->OnComponentHit.AddDynamic(this, &ATankProjectile::onHit);

	// Check if we have sound for the launch
	if(LaunchSound)
	{

		// Play the launch sound
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

// Called every frame
void ATankProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void  ATankProjectile::onHit(UPrimitiveComponent* hitComponent, AActor* actorHit, 
UPrimitiveComponent* otherComponent, FVector impluse, const FHitResult& hit)
{

	// Get the owner that spawned the projectile
	AActor* owner = GetOwner();

	// Return if there is no owner
	if(!owner) return;

	// Hold the controller of the actor
	AController* ownerInstigator = owner->GetInstigatorController();
	
	// Hold the default damage type 
	UClass* damageTypeClass = UDamageType::StaticClass();

	// Check if there is an actor hit, the projectile itself, and it is not the owner
	if(actorHit && actorHit != this && actorHit != owner)
	{

		// Call the apply damage event 
		UGameplayStatics::ApplyDamage(actorHit, damage, ownerInstigator, this, damageTypeClass);

		// Check if there is particles for the hit
		if(HitParticles)
		{
			
			// Spawn the hit particles
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		}

		// Check if there is sound for the hit
		if(HitSound)
		{

			// Play the hit sound
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}

		// Check if we have a camera shake
		if(HitCameraShakeClass)
		{

			// Start the camera shake
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}

	// Destroy the projectile
	Destroy();
}

