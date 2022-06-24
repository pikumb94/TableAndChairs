// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Table.h"

void ACustomPlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;

    InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &ACustomPlayerController::RightMouseButtonPressedHandler);
	InputComponent->BindAction("RightMouseClick", IE_DoubleClick, this, &ACustomPlayerController::RightMouseButtonDoubleClickedHandler);

	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &ACustomPlayerController::LeftMouseButtonPressedHandler);
	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &ACustomPlayerController::LeftMouseButtonReleasedHandler);

	InputComponent->BindAxis("MouseX", this, &ACustomPlayerController::OnMouseX);
	InputComponent->BindAxis("MouseY", this, &ACustomPlayerController::OnMouseY);

	InputComponent->BindAction("MiddleMouseClick", IE_Pressed, this, &ACustomPlayerController::OnMiddleMousePressed);
	InputComponent->BindAction("MiddleMouseClick", IE_Released, this, &ACustomPlayerController::OnMiddleMouseReleased);

	bIsMiddleMousePressed = false;
	bIsLeftMousePressed = false;
	bOnPanningX = false;
	bOnPanningY = false;
	mAccumulatePanX = 0.f;
	mAccumulatePanY = 0.f;
	PanScaleFactor = 0.03f;
	BaseTurnRate = 1.f;
	BaseLookUpRate = 1.f;
}

void ACustomPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMiddleMousePressed)
	{
		ApplyPan();
	}

}

void ACustomPlayerController::RightMouseButtonPressedHandler()
{
	FVector WorldLocation;
	FVector WorldDirection;
	GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	if (WorldDirection.Z < 0) {
		FVector PlaneNormal(0, 0, 1);
		FVector PlanePoint = WorldDirection;
		//FVector NewPosition = FMath::LinePlaneIntersection(WorldLocation, WorldLocation + WorldDirection * 10000, FPlane(PlanePoint, PlaneNormal));
		FPlane Plane(PlanePoint, PlaneNormal);
		FVector NewPosition = FMath::RayPlaneIntersection(WorldLocation, WorldDirection, Plane);

		FHitResult HitResult;
		if (GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
		{
			if (!Cast<ATable>(HitResult.GetActor()))
				GetWorld()->SpawnActor<ATable>(NewPosition, FRotator(0, 0, 0));
		}

	}

}

void ACustomPlayerController::RightMouseButtonDoubleClickedHandler()
{
	FHitResult HitResult;
	if(GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
	{
		if(Cast<ATable>(HitResult.GetActor()))
			HitResult.GetActor()->Destroy();
	}
}

void ACustomPlayerController::OnMiddleMousePressed()
{
	bIsMiddleMousePressed = true;
}

void ACustomPlayerController::LeftMouseButtonPressedHandler()
{
	bIsLeftMousePressed = true;
}

void ACustomPlayerController::LeftMouseButtonReleasedHandler()
{
	bIsLeftMousePressed = false;
}

void ACustomPlayerController::OnMiddleMouseReleased()
{
	bIsMiddleMousePressed = false;

	bOnPanningX = false;
	bOnPanningY = false;

	mAccumulatePanX = 0.f;
	mAccumulatePanY = 0.f;
}


void ACustomPlayerController::OnPanX(float Val)
{
	float Delta = Val * PanScaleFactor;
	mAccumulatePanX += Delta;

}

void ACustomPlayerController::OnPanY(float Val)
{
	float Delta = Val * PanScaleFactor;
	mAccumulatePanY += Delta;
}

void ACustomPlayerController::OnYawRotation(float Val)
{
	auto ControlledPawn = GetPawn();
	if (ControlledPawn)
		ControlledPawn->AddControllerYawInput(Val * BaseTurnRate);
}

void ACustomPlayerController::OnPitchRotation(float Val)
{
	auto ControlledPawn = GetPawn();
	if (ControlledPawn)
		ControlledPawn->AddControllerPitchInput(-Val * BaseLookUpRate);
}

void ACustomPlayerController::OnMouseX(float Val)
{
	if (FMath::Abs(Val) > epsilon_move)
	{
		if (bIsLeftMousePressed)
		{
			OnYawRotation(Val);

		}
		if (bIsMiddleMousePressed)
		{
			OnPanX(Val);
		}
	}
}

void ACustomPlayerController::OnMouseY(float Val)
{
	if (FMath::Abs(Val) > epsilon_move)
	{
		if (bIsLeftMousePressed)
		{
			OnPitchRotation(Val);

		}
		if (bIsMiddleMousePressed)
		{
			OnPanY(Val);
		}

	}
}

void ACustomPlayerController::ApplyPan()
{
	if (!bOnPanningY && !bOnPanningX) {
		float AbsPanX = FMath::Abs(mAccumulatePanX);
		float AbsPanY = FMath::Abs(mAccumulatePanY);
		//if (AbsPanX != 0 && AbsPanY != 0)
			if (AbsPanX > AbsPanY)
				bOnPanningX = true;
			else
				bOnPanningY = true;
	}

	auto ControlledPawn = GetPawn();
	if (ControlledPawn) {

		if (bOnPanningY)
		{
			ControlledPawn->AddMovementInput(FVector::UpVector, mAccumulatePanY);
		}

		if (bOnPanningX)
		{
			FRotator const ControlSpaceRot = GetControlRotation();
			ControlledPawn->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), mAccumulatePanX);
		}
	}

}