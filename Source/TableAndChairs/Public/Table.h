// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Table.generated.h"

UCLASS()
class TABLEANDCHAIRS_API ATable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATable();

	// Create Table Mesh
	void CreateTable();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//Procedural Mesh Compoentn for the Table Actor
	class UProceduralMeshComponent* Leg1;
	UProceduralMeshComponent* Leg2;
	UProceduralMeshComponent* Leg3;
	UProceduralMeshComponent* Leg4;
	UProceduralMeshComponent* TopTable;
	
	class UStaticMeshComponent* Sphere1;
	UStaticMeshComponent* Sphere2;
	UStaticMeshComponent* Sphere3;
	UStaticMeshComponent* Sphere4;

	UFUNCTION()
	void OnClickedSphereHandle(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	UFUNCTION()
	void OnReleasedSphereHandle(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased);
	UFUNCTION()
	void RemoveAllChairs(AActor* Actor, EEndPlayReason::Type EndPlayReason);

	bool bSphereClicked=false;

	void MoveSphere1Vertices(const FVector& DeltaPosition, TArray<FVector>& ToMoveVertices);
	void MoveSphere2Vertices(const FVector& DeltaPosition, TArray<FVector>& ToMoveVertices);
	void MoveSphere3Vertices(const FVector& DeltaPosition, TArray<FVector>& ToMoveVertices);
	void MoveSphere4Vertices(const FVector& DeltaPosition, TArray<FVector>& ToMoveVertices);

	void UpdateChairsNorth(float FreeSpaceHead, float FreeSpaceTail);
	void UpdateChairsEast(float FreeSpaceHead, float FreeSpaceTail);
	void UpdateChairsSouth(float FreeSpaceHead, float FreeSpaceTail);
	void UpdateChairsWest(float FreeSpaceHead, float FreeSpaceTail);

	void MoveVerticesAndActors(FVector& DeltaPosition, UPrimitiveComponent* ClickedComp, float Free1South, float Free1West, float Free2South, float Free3West);

	UPrimitiveComponent* ClickedComponent;

	float min_table_length;
	float min_table_width;

	float chairs_spacing;

	TDoubleLinkedList<AActor*> NorthChairs;
	TDoubleLinkedList<AActor*> EastChairs;
	TDoubleLinkedList<AActor*> SouthChairs;
	TDoubleLinkedList<AActor*> WestChairs;

};
