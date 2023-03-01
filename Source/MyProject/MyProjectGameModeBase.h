// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMyProjectGameModeBase();


	virtual void BeginPlay() override;

	void SwitchPrevTarget();
	void SwitchNextTarget();
	void ClearFollowTarget();

	void SetFollowTarget(bool Prev);
};
