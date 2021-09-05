// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HelperFunctions.generated.h"

/**
 * 
 */
UCLASS()
class TABLEANDCHAIRS_API UHelperFunctions : public UObject
{
	GENERATED_BODY()
public:
	static void CreateCuboid(class UProceduralMeshComponent* NewCuboidMesh, float length = 100.f, float width = 100.f, float height = 100.f, const FVector& Offset = FVector::ZeroVector);
};