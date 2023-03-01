// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MyPawn.h"
#include "Camera/CameraComponent.h"	

AMyProjectGameModeBase::AMyProjectGameModeBase()
{
}

void AMyProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	PlayerController->InputComponent->BindAction("SwitchPrevTarget", IE_Pressed, this, &AMyProjectGameModeBase::SwitchPrevTarget);
	PlayerController->InputComponent->BindAction("SwitchNextTarget", IE_Pressed, this, &AMyProjectGameModeBase::SwitchNextTarget);
	PlayerController->InputComponent->BindAction("ClearFollowTarget", IE_Pressed, this, &AMyProjectGameModeBase::ClearFollowTarget);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("M - Reset to Default Pawn"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("> - Switch to Previous Pawn"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("< - Switch to Previous Pawn"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Keys"));
	}
}

void AMyProjectGameModeBase::SetFollowTarget(bool PrevTarget)
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
		TargetIndex = CurrentIndex < 0 ? 0 : (CurrentIndex + 1) % Actors.Num();

	UE_LOG(LogTemp, Log, TEXT("SetFollowTarget %s"), *TargetActor->GetName());
}

void AMyProjectGameModeBase::SwitchPrevTarget()
{
	SetFollowTarget(true);
}

void AMyProjectGameModeBase::SwitchNextTarget()
{
	SetFollowTarget(false);
}

void AMyProjectGameModeBase::ClearFollowTarget()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	
	// Set to default pawn
	APawn* DefaultPawn = Cast<APawn>(UGameplayStatics::GetActorOfClass(GetWorld(), DefaultPawnClass));
	PlayerController->Possess(DefaultPawn);
}