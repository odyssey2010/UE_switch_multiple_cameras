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

#include "MyProjectGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MyPawn.h"
#include "Camera/CameraComponent.h"	

AMyProjectGameMode::AMyProjectGameMode()
{
}

void AMyProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	PlayerController->InputComponent->BindAction("SwitchPrevTarget", IE_Pressed, this, &AMyProjectGameMode::SwitchPrevTarget);
	PlayerController->InputComponent->BindAction("SwitchNextTarget", IE_Pressed, this, &AMyProjectGameMode::SwitchNextTarget);
	PlayerController->InputComponent->BindAction("ClearFollowTarget", IE_Pressed, this, &AMyProjectGameMode::ClearFollowTarget);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("M - Reset to Default Pawn"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("> - Switch to Previous Pawn"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("< - Switch to Previous Pawn"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Keys"));
	}
}

void AMyProjectGameMode::SetFollowTarget(bool PrevTarget)
{	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPawn::StaticClass(), Actors);
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AMyPawn* CurrentActor = Cast<AMyPawn>(GetWorld()->GetFirstPlayerController()->GetViewTarget());

	int CurrentIndex = Actors.Find(CurrentActor);
	int TargetIndex = -1;

	if (PrevTarget)
	{
		TargetIndex = CurrentIndex > 0 ? (CurrentIndex - 1) % Actors.Num() : Actors.Num() - 1;
	}
	else
	{
		TargetIndex = CurrentIndex < 0 ? 0 : (CurrentIndex + 1) % Actors.Num();
	}

	AMyPawn* TargetActor = Cast<AMyPawn>(Actors[TargetIndex]);
	if (TargetActor)
	{
		PlayerController->Possess(TargetActor);
	}

	UE_LOG(LogTemp, Log, TEXT("SetFollowTarget %s"), *TargetActor->GetName());
}

void AMyProjectGameMode::SwitchPrevTarget()
{
	SetFollowTarget(true);
}

void AMyProjectGameMode::SwitchNextTarget()
{
	SetFollowTarget(false);
}

void AMyProjectGameMode::ClearFollowTarget()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	
	// Set to default pawn
	APawn* DefaultPawn = Cast<APawn>(UGameplayStatics::GetActorOfClass(GetWorld(), DefaultPawnClass));
	PlayerController->Possess(DefaultPawn);
}