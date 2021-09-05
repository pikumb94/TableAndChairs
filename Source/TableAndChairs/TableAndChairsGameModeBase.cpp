// Copyright Epic Games, Inc. All Rights Reserved.


#include "TableAndChairsGameModeBase.h"
#include "CustomPlayerController.h"

void ATableAndChairsGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
    PlayerControllerClass = ACustomPlayerController::StaticClass();

    /*
    APlayerController* MyController = GetWorld()->GetFirstPlayerController();
    MyController = CreateDefaultSubobject<APlayerController>(TEXT("MyController"));
    */
}

void ATableAndChairsGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    /*
    APlayerController* MyController = GetWorld()->GetFirstPlayerController();
    
    MyController->bShowMouseCursor = true;
    MyController->bEnableClickEvents = true;
    MyController->bEnableMouseOverEvents = true;*/
}
