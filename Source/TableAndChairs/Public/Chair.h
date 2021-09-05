// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chair.generated.h"

UCLASS()
class TABLEANDCHAIRS_API AChair : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AChair();

	// Create Chair Mesh
	void CreateChair();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Procedural Mesh Compoentn for the Chair Actor
	class UProceduralMeshComponent* Leg1;
	UProceduralMeshComponent* Leg2;
	UProceduralMeshComponent* Leg3;
	UProceduralMeshComponent* Leg4;

	UProceduralMeshComponent* Seat;
	UProceduralMeshComponent* Back;
};
