// MIT License
// Copyright (c) 2023 devx.3dcodekits.com
// All rights reserved.
// 
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this softwareand associated documentation
// files(the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions :
//
// The above copyright noticeand this permission notice shall be
// included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

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
