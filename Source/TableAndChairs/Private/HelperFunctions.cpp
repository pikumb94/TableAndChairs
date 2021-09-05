// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperFunctions.h"
#include "ProceduralMeshComponent.h"

void UHelperFunctions::CreateCuboid(UProceduralMeshComponent* NewCuboidMesh, float length, float width, float height, const FVector& Offset)
{
	TArray<FVector> vertices;
	float half_length = length / 2;
	float half_width = width / 2;
	float half_height = height / 2;

	//-face along Z
	vertices.Add(FVector(-half_length, -half_width, -half_height) + Offset);//0
	vertices.Add(FVector(half_length, -half_width, -half_height) + Offset);
	vertices.Add(FVector(-half_length, half_width, -half_height) + Offset);
	vertices.Add(FVector(half_length, half_width, -half_height) + Offset);
	//+face along Z
	vertices.Add(FVector(-half_length, -half_width, half_height) + Offset);//4
	vertices.Add(FVector(half_length, -half_width, half_height) + Offset);
	vertices.Add(FVector(-half_length, half_width, half_height) + Offset);
	vertices.Add(FVector(half_length, half_width, half_height) + Offset);

	//-face along Y
	vertices.Add(FVector(-half_length, -half_width, -half_height) + Offset);//8
	vertices.Add(FVector(half_length, -half_width, -half_height) + Offset);
	vertices.Add(FVector(-half_length, -half_width, half_height) + Offset);
	vertices.Add(FVector(half_length, -half_width, half_height) + Offset);
	//+face along Y
	vertices.Add(FVector(-half_length, half_width, -half_height) + Offset);//12
	vertices.Add(FVector(half_length, half_width, -half_height) + Offset);
	vertices.Add(FVector(-half_length, half_width, half_height) + Offset);
	vertices.Add(FVector(half_length, half_width, half_height) + Offset);

	//-face along X
	vertices.Add(FVector(-half_length, -half_width, -half_height) + Offset);//16
	vertices.Add(FVector(-half_length, half_width, -half_height) + Offset);
	vertices.Add(FVector(-half_length, -half_width, half_height) + Offset);
	vertices.Add(FVector(-half_length, half_width, half_height) + Offset);
	//+face along X
	vertices.Add(FVector(half_length, -half_width, -half_height) + Offset);//20
	vertices.Add(FVector(half_length, half_width, -half_height) + Offset);
	vertices.Add(FVector(half_length, -half_width, half_height) + Offset);
	vertices.Add(FVector(half_length, half_width, half_height) + Offset);

	TArray<int32> Triangles;
	//-face along Z
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);
	Triangles.Add(1);
	Triangles.Add(3);
	Triangles.Add(2);
	//+face along Z
	Triangles.Add(6);
	Triangles.Add(7);
	Triangles.Add(5);
	Triangles.Add(4);
	Triangles.Add(6);
	Triangles.Add(5);

	//-face along Y
	Triangles.Add(8);
	Triangles.Add(10);
	Triangles.Add(11);
	Triangles.Add(8);
	Triangles.Add(11);
	Triangles.Add(9);
	//+face along Y
	Triangles.Add(14);
	Triangles.Add(13);
	Triangles.Add(15);
	Triangles.Add(14);
	Triangles.Add(12);
	Triangles.Add(13);

	//-face along X
	Triangles.Add(16);
	Triangles.Add(17);
	Triangles.Add(19);
	Triangles.Add(19);
	Triangles.Add(18);
	Triangles.Add(16);
	//+face along X
	Triangles.Add(21);
	Triangles.Add(22);
	Triangles.Add(23);
	Triangles.Add(21);
	Triangles.Add(20);
	Triangles.Add(22);

	TArray<FVector> normals;
	//-face along Z
	normals.Add(FVector(0, 0, -1));
	normals.Add(FVector(0, 0, -1));
	normals.Add(FVector(0, 0, -1));
	normals.Add(FVector(0, 0, -1));
	//+face along Z
	normals.Add(FVector(0, 0, 1));
	normals.Add(FVector(0, 0, 1));
	normals.Add(FVector(0, 0, 1));
	normals.Add(FVector(0, 0, 1));

	//-face along Y
	normals.Add(FVector(0, -1, 0));
	normals.Add(FVector(0, -1, 0));
	normals.Add(FVector(0, -1, 0));
	normals.Add(FVector(0, -1, 0));
	//+face along Y
	normals.Add(FVector(0, 1, 0));
	normals.Add(FVector(0, 1, 0));
	normals.Add(FVector(0, 1, 0));
	normals.Add(FVector(0, 1, 0));

	//-face along X
	normals.Add(FVector(-1, 0, 0));
	normals.Add(FVector(-1, 0, 0));
	normals.Add(FVector(-1, 0, 0));
	normals.Add(FVector(-1, 0, 0));
	//+face along X
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));

	TArray<FVector2D> UV0;
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(10, 0));
	UV0.Add(FVector2D(0, 10));
	UV0.Add(FVector2D(10, 10));
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(10, 0));
	UV0.Add(FVector2D(0, 10));
	UV0.Add(FVector2D(10, 10));
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(10, 0));
	UV0.Add(FVector2D(0, 10));
	UV0.Add(FVector2D(10, 10));
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(10, 0));
	UV0.Add(FVector2D(0, 10));
	UV0.Add(FVector2D(10, 10));
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(10, 0));
	UV0.Add(FVector2D(0, 10));
	UV0.Add(FVector2D(10, 10));
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(10, 0));
	UV0.Add(FVector2D(0, 10));
	UV0.Add(FVector2D(10, 10));

	TArray<FProcMeshTangent> tangents;
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));
	tangents.Add(FProcMeshTangent(1, 1, 1));

	TArray<FLinearColor> vertexColors;
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));


	NewCuboidMesh->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
}
