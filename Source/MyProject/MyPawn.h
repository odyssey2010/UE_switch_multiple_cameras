// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPawn.generated.h"

UCLASS()
class MYPROJECT_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LookPitch(float Value);
	void LookHeading(float Value);
	void LookZoom(float Value);
	
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMesh{ nullptr };
	
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm{ nullptr };
	
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera{ nullptr };

	FVector CenterLocation;
	float MoveRadius{ 100.0f };
	float MoveAngle{ 0.0f };
	float MoveSpeed{ 0.5f };
	float RotationSpeed{ 2.0f };
	float ZoomSpeed{ 5.0f };
};
