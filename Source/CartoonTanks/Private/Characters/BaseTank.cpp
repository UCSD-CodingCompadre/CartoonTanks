// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseTank::ABaseTank()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the spring arm component
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring_Arm"));
    
    // Attach the spring arm component to the root component
    SpringArmComponent->SetupAttachment(RootComponent);

    // Set the camera component 
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    
    // Attach the camera component to the spring arm component
    CameraComponent->SetupAttachment(SpringArmComponent);

	// Set the projectile spawn component
	ProjectileSpawnComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile_Spawn"));

	// Check if there is a skeletal mesh
	if(GetMesh() != nullptr)
	{

		// Get the skeletal mesh
		USkeletalMeshComponent* SkeletalMesh = GetMesh();
	
		// Attach the projectile spawn component to the tank turret
		ProjectileSpawnComponent->SetupAttachment(SkeletalMesh);
	}
}

void ABaseTank::HandlePawnDestruction()
{

	// Check if we have death particles
	if(DeathParticles)
	{

		// Spawn the death particles
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}

	// Check if we have a sound for the pawn death
	if(DeathSound)
	{

		// Play the death sound
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	// Check if we have a camera shake
	if(CameraShakeClass)
	{

		// Start the camera shake
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShakeClass);
	}
}

// Called when the game starts or when spawned
void ABaseTank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

