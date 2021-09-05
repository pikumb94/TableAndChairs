// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TABLEANDCHAIRS_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void RightMouseButtonPressedHandler();
	void RightMouseButtonDoubleClickedHandler();

	void LeftMouseButtonPressedHandler();
	void LeftMouseButtonReleasedHandler();

	void OnMiddleMousePressed();
	void OnMiddleMouseReleased();

	void OnMouseX(float Val);
	void OnMouseY(float Val);

	void OnPanX(float Val);
	void OnPanY(float Val);

	void ApplyPan();
	void OnYawRotation(float Val);
	void OnPitchRotation(float Val);

	bool bIsMiddleMousePressed;
	bool bIsLeftMousePressed;

	bool bOnPanningX;
	bool bOnPanningY;

	float mAccumulatePanX;
	float mAccumulatePanY;

	const float epsilon_move = 0.05f;
	float PanScaleFactor;
	float BaseTurnRate;
	float BaseLookUpRate;

};
