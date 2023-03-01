// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"	
#include "Camera/CameraComponent.h"	
#include "Math/UnrealMathUtility.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(StaticMesh);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetWorldRotation(FRotator(-15.0f, 0, 0));
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawnedB
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	CenterLocation = GetActorLocation();
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveAngle = FMath::Fmod(MoveAngle + MoveSpeed, 360.0f);
	float Rad = FMath::DegreesToRadians(MoveAngle);
	float X = FMath::Sin(Rad) * MoveRadius;
	float Y = FMath::Cos(Rad) * MoveRadius;

	SetActorLocation(CenterLocation + FVector(X, Y, 0.0f));
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// BindAxis for all MyPawn instances, but only possesed pawn receives events
	PlayerInputComponent->BindAxis("LookPitch", this, &AMyPawn::LookPitch);
	PlayerInputComponent->BindAxis("LookHeading", this, &AMyPawn::LookHeading);
	PlayerInputComponent->BindAxis("LookZoom", this, &AMyPawn::LookZoom);
}

void AMyPawn::LookPitch(float Value)
{
	// Check receiving event input 
	UE_LOG(LogTemp, Log, TEXT("LookPitch %s"), *GetName());

	FRotator Rotation = SpringArm->GetComponentRotation();
	Rotation.Pitch += RotationSpeed * Value;
	SpringArm->SetWorldRotation(Rotation);
}

void AMyPawn::LookHeading(float Value)
{
	FRotator Rotation = SpringArm->GetComponentRotation();
	Rotation.Yaw += RotationSpeed * Value;
	SpringArm->SetWorldRotation(Rotation);
}

void AMyPawn::LookZoom(float Value)
{
	SpringArm->TargetArmLength -= ZoomSpeed * Value;
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, 100.0f, 1000.0f);
}