// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TableAndChairsGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TABLEANDCHAIRS_API ATableAndChairsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void BeginPlay() override;

};
