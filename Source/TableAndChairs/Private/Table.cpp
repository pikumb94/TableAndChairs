// Fill out your copyright notice in the Description page of Project Settings.


#include "Table.h"
#include "ProceduralMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Chair.h"
#include "UObject/ConstructorHelpers.h"
#include "..\Public\Table.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "HelperFunctions.h"

// Sets default values
ATable::ATable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	TopTable = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("TopTable"));
	TopTable->SetupAttachment(RootComponent);

	Leg1 = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Leg1"));
	Leg2 = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Leg2"));
	Leg3 = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Leg3"));
	Leg4 = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Leg4"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SphereMaterial(TEXT("/Game/HandleMaterial.HandleMaterial"));

	Sphere1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere1"));
	Sphere1->SetupAttachment(TopTable);
	Sphere1->SetStaticMesh(SphereMesh.Object);
	Sphere1->SetMaterial(0, SphereMaterial.Object);
	Sphere1->SetRelativeScale3D(FVector::OneVector * 0.2f);

	Sphere1->OnClicked.AddDynamic(this, &ATable::OnClickedSphereHandle);
	Sphere1->OnReleased.AddDynamic(this, &ATable::OnReleasedSphereHandle);


	Sphere2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere2"));
	Sphere2->SetupAttachment(TopTable);
	Sphere2->SetStaticMesh(SphereMesh.Object);
	Sphere2->SetMaterial(0, SphereMaterial.Object);
	Sphere2->SetRelativeScale3D(FVector::OneVector * 0.2f);

	Sphere2->OnClicked.AddDynamic(this, &ATable::OnClickedSphereHandle);
	Sphere2->OnReleased.AddDynamic(this, &ATable::OnReleasedSphereHandle);
	

	Sphere3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere3"));
	Sphere3->SetupAttachment(TopTable);
	Sphere3->SetStaticMesh(SphereMesh.Object);
	Sphere3->SetMaterial(0, SphereMaterial.Object);
	Sphere3->SetRelativeScale3D(FVector::OneVector * 0.2f);

	Sphere3->OnClicked.AddDynamic(this, &ATable::OnClickedSphereHandle);
	Sphere3->OnReleased.AddDynamic(this, &ATable::OnReleasedSphereHandle);


	Sphere4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere4"));
	Sphere4->SetupAttachment(TopTable);
	Sphere4->SetStaticMesh(SphereMesh.Object);
	Sphere4->SetMaterial(0, SphereMaterial.Object);
	Sphere4->SetRelativeScale3D(FVector::OneVector * 0.2f);

	Sphere4->OnClicked.AddDynamic(this, &ATable::OnClickedSphereHandle);
	Sphere4->OnReleased.AddDynamic(this, &ATable::OnReleasedSphereHandle);

	Leg1->SetupAttachment(Sphere1);
	Leg1->SetWorldScale3D(FVector::OneVector*5.f);
	Leg2->SetupAttachment(Sphere2);
	Leg2->SetWorldScale3D(FVector::OneVector * 5.f);
	Leg3->SetupAttachment(Sphere3);
	Leg3->SetWorldScale3D(FVector::OneVector * 5.f);
	Leg4->SetupAttachment(Sphere4);
	Leg4->SetWorldScale3D(FVector::OneVector * 5.f);

	min_table_length = 50.f;
	min_table_width = 50.f;
	chairs_spacing = 50.f;

	OnEndPlay.AddDynamic(this, &ATable::RemoveAllChairs);
}

// Called when the game starts or when spawned
void ATable::BeginPlay()
{
	Super::BeginPlay();
	CreateTable();

	TopTable->RegisterComponent();
	Sphere1->RegisterComponent();
	Sphere2->RegisterComponent();
	Sphere3->RegisterComponent();
	Sphere4->RegisterComponent();

	Leg1->RegisterComponent();
	Leg2->RegisterComponent();
	Leg3->RegisterComponent();
	Leg4->RegisterComponent();

	NorthChairs.AddTail(GetWorld()->SpawnActor <AChair>(GetActorLocation() +  FVector(0, 50, 0), FRotator(0,-90,0)));

	EastChairs.AddTail(GetWorld()->SpawnActor <AChair>(GetActorLocation() + FVector(50, 0, 0), FRotator(0,180,0)));

	SouthChairs.AddTail(GetWorld()->SpawnActor <AChair>(GetActorLocation() + FVector(0, -50, 0), FRotator(0,90,0)));

	WestChairs.AddTail(GetWorld()->SpawnActor <AChair>(GetActorLocation() + FVector(-50, 0, 0), FRotator(0,0,0)));
}

void ATable::CreateTable()
{
	UHelperFunctions::CreateCuboid(TopTable, min_table_length, min_table_width, 5);

	UHelperFunctions::CreateCuboid(Leg1, 5, 5, 50, FVector(0, 0, -25));
	UHelperFunctions::CreateCuboid(Leg2, 5, 5, 50, FVector(0, 0, -25));
	UHelperFunctions::CreateCuboid(Leg3, 5, 5, 50, FVector(0, 0, -25));
	UHelperFunctions::CreateCuboid(Leg4, 5, 5, 50, FVector(0, 0, -25));

	TopTable->AddRelativeLocation(FVector(0, 0, 25));
	//Leg1->AddRelativeLocation(FVector(0, 0, -50));
	//Leg2->AddRelativeLocation(FVector(0, 0, -100));
	//Leg3->AddRelativeLocation(FVector(0, 0, -200));
	//Leg4->AddRelativeLocation(FVector(0, 0, 500));

	Sphere1->AddRelativeLocation(FVector(-min_table_length/2, -min_table_width/2, 2.5f));
	//Spheres.Add(Sphere1);
	Sphere2->AddRelativeLocation(FVector(min_table_length/2, -min_table_width/2, 2.5f));
	//Spheres.Add(Sphere2);
	Sphere3->AddRelativeLocation(FVector(-min_table_length/2, min_table_width/2, 2.5f));
	//Spheres.Add(Sphere3);
	Sphere4->AddRelativeLocation(FVector(min_table_length/2, min_table_width/2, 2.5f));
	//Spheres.Add(Sphere4);
}

// Called every frame
void ATable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSphereClicked && ClickedComponent)
	{
		float Free1South = -(Sphere1->GetComponentLocation().X - SouthChairs.GetHead()->GetValue()->GetActorLocation().X) - (chairs_spacing / 2);
		float Free1West = -(Sphere1->GetComponentLocation().Y - WestChairs.GetTail()->GetValue()->GetActorLocation().Y) - (chairs_spacing / 2);
		float Free2South = Sphere2->GetComponentLocation().X - SouthChairs.GetTail()->GetValue()->GetActorLocation().X - (chairs_spacing / 2);
		float Free3West = Sphere3->GetComponentLocation().Y - WestChairs.GetHead()->GetValue()->GetActorLocation().Y - (chairs_spacing / 2);

		float mouseX;
		float mouseY;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);

		//UE_LOG(LogTemp, Warning, TEXT("Mouse Location: %f, %f"), mouseX, mouseY);

		FVector PlaneNormal(0, 0, 1);
		FVector PlanePoint = ClickedComponent->GetComponentLocation();

		FVector WorldLocation;
		FVector WorldDirection;
		GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

		if (WorldDirection.Z < 0) {
			//FVector NewPosition = FMath::LinePlaneIntersection(WorldLocation, WorldLocation + WorldDirection * 10000, FPlane(PlanePoint, PlaneNormal));
			FPlane TablePlane(PlanePoint, PlaneNormal);
			FVector NewPosition = FMath::RayPlaneIntersection(WorldLocation, WorldDirection, TablePlane);

			FVector2D DeltaXY(NewPosition - ClickedComponent->GetComponentLocation());

			FVector DeltaVector(DeltaXY, 0);
			MoveVerticesAndActors(DeltaVector, ClickedComponent, Free1South, Free1West, Free2South, Free3West);

		}
		
		UpdateChairsNorth(Free2South, Free1South);
		UpdateChairsSouth(Free1South, Free2South);
		UpdateChairsEast(Free1West, Free3West);
		UpdateChairsWest(Free3West, Free1West);
	}

}

void ATable::OnClickedSphereHandle(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	bSphereClicked = true;
	ClickedComponent = TouchedComponent;
}

void ATable::OnReleasedSphereHandle(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased)
{
	bSphereClicked = false;
	ClickedComponent = nullptr;
}

void ATable::MoveVerticesAndActors(FVector& DeltaPosition, UPrimitiveComponent* ClickedComp, float Free1South, float Free1West, float Free2South, float Free3West)
{
	TArray<FVector> MovedVertices;

	if (ClickedComp->GetUniqueID() == Sphere1->GetUniqueID()){
		FVector ConstrainVector((ClickedComponent->GetComponentLocation() + DeltaPosition - Sphere2->GetComponentLocation()).X, (ClickedComponent->GetComponentLocation() + DeltaPosition - Sphere3->GetComponentLocation()).Y, 0);
		if (ConstrainVector.X > -min_table_length)
			DeltaPosition.X = 0;
		if(ConstrainVector.Y>-min_table_width)
			DeltaPosition.Y = 0;

		ClickedComponent->SetWorldLocation(ClickedComponent->GetComponentLocation() + DeltaPosition);
		MoveSphere1Vertices(DeltaPosition, MovedVertices);

		Sphere2->AddLocalOffset(FVector(0, DeltaPosition.Y, 0));
		Sphere3->AddLocalOffset(FVector(DeltaPosition.X, 0, 0));
		for (auto c : SouthChairs) {
			c->AddActorWorldOffset(FVector(0, DeltaPosition.Y, 0));//N/S => MOVE-Y		E/W => MOVE-X
		}
		for (auto c : WestChairs) {
			c->AddActorWorldOffset(FVector(DeltaPosition.X, 0, 0));
		}

		if (SouthChairs.Num() == 1 && (Free1South < 0) && DeltaPosition.X>0) {
			for (auto c : NorthChairs) {
				c->AddActorWorldOffset(FVector(DeltaPosition.X, 0, 0));
			}
			for (auto c : SouthChairs) {
				c->AddActorWorldOffset(FVector(DeltaPosition.X, 0, 0));
			}
		}

		if (WestChairs.Num() == 1 && (Free1West < 0) && DeltaPosition.Y > 0) {
			for (auto c : EastChairs) {
				c->AddActorWorldOffset(FVector(0, DeltaPosition.Y, 0));
			}
			for (auto c : WestChairs) {
				c->AddActorWorldOffset(FVector(0, DeltaPosition.Y, 0));
			}
		}

	}


	else if (ClickedComp->GetUniqueID() == Sphere2->GetUniqueID()) {
		FVector ConstrainVector((ClickedComponent->GetComponentLocation() + DeltaPosition - Sphere1->GetComponentLocation()).X, (ClickedComponent->GetComponentLocation() + DeltaPosition - Sphere4->GetComponentLocation()).Y, 0);
		if (ConstrainVector.X < min_table_length)
			DeltaPosition.X = 0;
		if(ConstrainVector.Y > -min_table_width)
			DeltaPosition.Y = 0;

		ClickedComponent->SetWorldLocation(ClickedComponent->GetComponentLocation() + DeltaPosition);
		MoveSphere2Vertices(DeltaPosition, MovedVertices);

		Sphere1->AddLocalOffset(FVector(0, DeltaPosition.Y, 0));
		for (auto c : SouthChairs) {
			c->AddActorWorldOffset(FVector(0, DeltaPosition.Y, 0));
		}

		Sphere4->AddLocalOffset(FVector(DeltaPosition.X, 0, 0));
		for (auto c : EastChairs) {
			c->AddActorWorldOffset(FVector(DeltaPosition.X, 0, 0));
		}


		if (SouthChairs.Num() == 1 && (Free2South < 0) && DeltaPosition.X < 0) {
			for (auto c : NorthChairs) {
				c->AddActorWorldOffset(FVector(DeltaPosition.X, 0, 0));
			}
			for (auto c : SouthChairs) {
				c->AddActorWorldOffset(FVector(DeltaPosition.X, 0, 0));
			}
		}

		if (WestChairs.Num() == 1 && (Free1West < 0) && DeltaPosition.Y > 0) {
			for (auto c : EastChairs) {
				c->AddActorWorldOffset(FVector(0, DeltaPosition.Y, 0));
			}
			for (auto c : WestChairs) {
				c->AddActorWorldOffset(FVector(0, DeltaPosition.Y, 0));
			}
		}

	}
	else if (ClickedComp->GetUniqueID() == Sphere3->GetUniqueID()) {
		FVector ConstrainVector((ClickedComponent->GetComponentLocation() + DeltaPosition - Sphere4->GetComponentLocation()).X, (ClickedComponent->GetComponentLocation() + DeltaPosition - Sphere1->GetComponentLocation()).Y, 0);
		if (ConstrainVector.X > -min_table_length)
			DeltaPosition.X = 0;
		if(ConstrainVector.Y < min_table_width)
			DeltaPosition.Y = 0;

		ClickedComponent->SetWorldLocation(ClickedComponent->GetComponentLocation() + DeltaPosition);
		MoveSphere3Vertices(DeltaPosition, MovedVertices);

		Sphere4->AddLocalOffset(FVector(0, DeltaPosition.Y, 0));
		for (auto c : NorthChairs) {
			c->AddActorWorldOffset(FVector(0, DeltaPosition.Y, 0));
		}

		Sphere1->AddLocalOffset(FVector(DeltaPosition.X, 0, 0));
		for (auto c : WestChairs) {
			c->AddActorWorldOffset(FVector(DeltaPosition.X, 0, 0));
		}

		if (SouthChairs.Num() == 1 && (Free1South < 0) && DeltaPosition.X > 0) {
			for (auto c : NorthChairs) {
				c->AddActorWorldOffset(FVector(DeltaPosition.X, 0, 0));
			}
			for (auto c : SouthChairs) {
				c->AddActorWorldOffset(FVector(DeltaPosition.X, 0, 0));
			}
		}

		if (WestChairs.Num() == 1 && (Free3West < 0) && DeltaPosition.Y < 0) {
			for (auto c : EastChairs) {
				c->AddActorWorldOffset(FVector(0, DeltaPosition.Y, 0));
			}
			for (auto c : WestChairs) {
				c->AddActorWorldOffset(FVector(0, DeltaPosition.Y, 0));
			}
		}

	}
	else if (ClickedComp->GetUniqueID() == Sphere4->GetUniqueID()) {
		FVector ConstrainVector((ClickedComponent->GetComponentLocation() + DeltaPosition - Sphere3->GetComponentLocation()).X, (ClickedComponent->GetComponentLocation() + DeltaPosition - Sphere2->GetComponentLocation()).Y, 0);
		if (ConstrainVector.X < min_table_length)
			DeltaPosition.X = 0;

		if(ConstrainVector.Y < min_table_width)
			DeltaPosition.Y = 0;


		ClickedComponent->SetWorldLocation(ClickedComponent->GetComponentLocation() + DeltaPosition);
		MoveSphere4Vertices(DeltaPosition, MovedVertices);

		Sphere3->AddLocalOffset(FVector(0, DeltaPosition.Y, 0));
		for (auto c : NorthChairs) {
			c->AddActorWorldOffset(FVector(0, DeltaPosition.Y, 0));
		}

		Sphere2->AddLocalOffset(FVector(DeltaPosition.X, 0, 0));
		for (auto c : EastChairs) {
			c->AddActorWorldOffset(FVector(DeltaPosition.X, 0, 0));
		}


		if (SouthChairs.Num() == 1 && (Free2South < 0) && DeltaPosition.X < 0) {
			for (auto c : NorthChairs) {
				c->AddActorWorldOffset(FVector(DeltaPosition.X, 0, 0));
			}
			for (auto c : SouthChairs) {
				c->AddActorWorldOffset(FVector(DeltaPosition.X, 0, 0));
			}
		}

		if (WestChairs.Num() == 1 && (Free3West < 0) && DeltaPosition.Y < 0) {
			for (auto c : EastChairs) {
				c->AddActorWorldOffset(FVector(0, DeltaPosition.Y, 0));
			}
			for (auto c : WestChairs) {
				c->AddActorWorldOffset(FVector(0, DeltaPosition.Y, 0));
			}
		}

	}
	else {

	}

	TopTable->UpdateMeshSection(0, MovedVertices, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>());

}

void ATable::RemoveAllChairs(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	for (auto c : NorthChairs) {
		c->Destroy();
	}
	for (auto c : SouthChairs) {
		c->Destroy();
	}
	for (auto c : EastChairs) {
		c->Destroy();
	}
	for (auto c : WestChairs) {
		c->Destroy();
	}

}

void ATable::MoveSphere1Vertices(const FVector& DeltaPosition, TArray<FVector>& ToMoveVertices)
{
	FProcMeshSection* TableMeshSection = TopTable->GetProcMeshSection(0);

	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[0].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[1].Position + FVector(0, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[2].Position + FVector(DeltaPosition.X, 0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[3].Position);
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[4].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[5].Position + FVector(0, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[6].Position + FVector(DeltaPosition.X, 0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[7].Position);
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[8].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[9].Position + FVector(0, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[10].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[11].Position + FVector(0, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[12].Position + FVector(DeltaPosition.X, 0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[13].Position);
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[14].Position + FVector(DeltaPosition.X, 0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[15].Position);
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[16].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[17].Position + FVector(DeltaPosition.X, 0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[18].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[19].Position + FVector(DeltaPosition.X, 0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[20].Position + FVector(0, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[21].Position);
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[22].Position + FVector(0, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[23].Position);

	/*
	ToMoveVertices[0] = TableMeshSection->ProcVertexBuffer[0].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	ToMoveVertices[8] = TableMeshSection->ProcVertexBuffer[8].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	ToMoveVertices[16] = TableMeshSection->ProcVertexBuffer[16].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	ToMoveVertices[4] = TableMeshSection->ProcVertexBuffer[4].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[10].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[18].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);

	TableMeshSection->ProcVertexBuffer[2].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[12].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[17].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[14].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[19].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[6].Position += FVector(DeltaPosition.X, 0, 0);

	TableMeshSection->ProcVertexBuffer[1].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[9].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[20].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[22].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[11].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[5].Position += FVector(0, DeltaPosition.Y, 0);
	
	int32 vertexNum = TableMeshSection->ProcVertexBuffer.Num();
	TArray<FVector> MovedVertices;
	MovedVertices.SetNum(vertexNum);
	for (int32 index = 0; index < vertexNum; index++)
	{
		MovedVertices[index] = TableMeshSection->ProcVertexBuffer[index].Position;
	}
	TopTable->UpdateMeshSection(0, MovedVertices, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>());*/
}

void ATable::MoveSphere2Vertices(const FVector& DeltaPosition, TArray<FVector>& ToMoveVertices)
{
	FProcMeshSection* TableMeshSection = TopTable->GetProcMeshSection(0);

	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[0].Position + FVector(0, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[1].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[2].Position);
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[3].Position + FVector(DeltaPosition.X, 0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[4].Position + FVector(0, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[5].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[6].Position);
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[7].Position + FVector(DeltaPosition.X, 0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[8].Position + FVector(0, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[9].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[10].Position + FVector(0, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[11].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[12].Position);
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[13].Position + FVector(DeltaPosition.X, 0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[14].Position);
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[15].Position + FVector(DeltaPosition.X, 0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[16].Position + FVector(0, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[17].Position );
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[18].Position + FVector(0, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[19].Position);
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[20].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[21].Position + FVector(DeltaPosition.X, 0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[22].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[23].Position + FVector(DeltaPosition.X, 0, 0));
	/*
	TableMeshSection->ProcVertexBuffer[1].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[9].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[20].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[22].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[11].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[5].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);

	TableMeshSection->ProcVertexBuffer[3].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[7].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[13].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[15].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[21].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[23].Position += FVector(DeltaPosition.X, 0, 0);

	TableMeshSection->ProcVertexBuffer[0].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[8].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[16].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[4].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[10].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[18].Position += FVector(0, DeltaPosition.Y, 0);

	int32 vertexNum = TableMeshSection->ProcVertexBuffer.Num();
	TArray<FVector> MovedVertices;
	MovedVertices.SetNum(vertexNum);
	for (int32 index = 0; index < vertexNum; index++)
	{
		MovedVertices[index] = TableMeshSection->ProcVertexBuffer[index].Position;
	}
	TopTable->UpdateMeshSection(0, MovedVertices, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>());*/
}

void ATable::MoveSphere3Vertices(const FVector& DeltaPosition, TArray<FVector>& ToMoveVertices)
{
	FProcMeshSection* TableMeshSection = TopTable->GetProcMeshSection(0);

	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[0].Position + FVector(DeltaPosition.X,0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[1].Position );
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[2].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[3].Position + FVector(0, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[4].Position + FVector(DeltaPosition.X,0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[5].Position );
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[6].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[7].Position + FVector(0,DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[8].Position + FVector(DeltaPosition.X,0 ,0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[9].Position );
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[10].Position + FVector(DeltaPosition.X,0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[11].Position );
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[12].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[13].Position + FVector(0,DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[14].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[15].Position + FVector(0, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[16].Position + FVector(DeltaPosition.X,0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[17].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[18].Position + FVector(DeltaPosition.X,0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[19].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[20].Position );
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[21].Position + FVector(0,DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[22].Position );
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[23].Position + FVector(0,DeltaPosition.Y, 0));
	/*
	TableMeshSection->ProcVertexBuffer[2].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[12].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[17].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[14].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[19].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[6].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);

	TableMeshSection->ProcVertexBuffer[0].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[8].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[16].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[4].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[10].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[18].Position += FVector(DeltaPosition.X, 0, 0);

	TableMeshSection->ProcVertexBuffer[3].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[7].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[13].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[15].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[21].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[23].Position += FVector(0, DeltaPosition.Y, 0);

	int32 vertexNum = TableMeshSection->ProcVertexBuffer.Num();
	TArray<FVector> MovedVertices;
	MovedVertices.SetNum(vertexNum);
	for (int32 index = 0; index < vertexNum; index++)
	{
		MovedVertices[index] = TableMeshSection->ProcVertexBuffer[index].Position;
	}
	TopTable->UpdateMeshSection(0, MovedVertices, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>());*/
}

void ATable::MoveSphere4Vertices(const FVector& DeltaPosition, TArray<FVector>& ToMoveVertices)
{
	FProcMeshSection* TableMeshSection = TopTable->GetProcMeshSection(0);

	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[0].Position );
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[1].Position + FVector(DeltaPosition.X, 0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[2].Position + FVector(0, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[3].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[4].Position );
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[5].Position + FVector(DeltaPosition.X, 0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[6].Position + FVector(0,DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[7].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[8].Position );
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[9].Position + FVector(DeltaPosition.X,0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[10].Position);
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[11].Position + FVector(DeltaPosition.X,0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[12].Position + FVector(0,DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[13].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[14].Position + FVector(0,DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[15].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[16].Position );
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[17].Position + FVector(0,DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[18].Position );
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[19].Position + FVector(0,DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[20].Position + FVector(DeltaPosition.X,0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[21].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[22].Position + FVector( DeltaPosition.X,0, 0));
	ToMoveVertices.Add(TableMeshSection->ProcVertexBuffer[23].Position + FVector(DeltaPosition.X, DeltaPosition.Y, 0));
	/*
	TableMeshSection->ProcVertexBuffer[3].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[7].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[13].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[15].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[21].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[23].Position += FVector(DeltaPosition.X, DeltaPosition.Y, 0);

	TableMeshSection->ProcVertexBuffer[1].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[9].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[20].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[22].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[11].Position += FVector(DeltaPosition.X, 0, 0);
	TableMeshSection->ProcVertexBuffer[5].Position += FVector(DeltaPosition.X, 0, 0);

	TableMeshSection->ProcVertexBuffer[2].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[12].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[17].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[14].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[19].Position += FVector(0, DeltaPosition.Y, 0);
	TableMeshSection->ProcVertexBuffer[6].Position += FVector(0, DeltaPosition.Y, 0);

	int32 vertexNum = TableMeshSection->ProcVertexBuffer.Num();
	TArray<FVector> MovedVertices;
	MovedVertices.SetNum(vertexNum);
	for (int32 index = 0; index < vertexNum; index++)
	{
		MovedVertices[index] = TableMeshSection->ProcVertexBuffer[index].Position;
	}
	TopTable->UpdateMeshSection(0, MovedVertices, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>());*/
}

void ATable::UpdateChairsNorth(float FreeSpaceHead, float FreeSpaceTail)
{
	int head_chairs = FMath::Abs(FreeSpaceHead / chairs_spacing);
	int tail_chairs = FMath::Abs(FreeSpaceTail / chairs_spacing);

	if (FreeSpaceHead < 0) {
		head_chairs++;
		while (head_chairs > 0) {
			if (NorthChairs.Num() <= 1)
				break;
			auto ChairToRemove = NorthChairs.GetHead();
			ChairToRemove->GetValue()->Destroy();
			NorthChairs.RemoveNode(ChairToRemove);
			head_chairs--;
		}
	}
	else if(FreeSpaceHead > 0 && FreeSpaceHead > chairs_spacing){
		while (head_chairs > 0) {
			NorthChairs.AddHead(GetWorld()->SpawnActor <AChair>(NorthChairs.GetHead()->GetValue()->GetActorLocation() + FVector(50, 0, 0), FRotator(0, -90, 0)));
			head_chairs--;
		}
	}

	if (FreeSpaceTail < 0) {
		tail_chairs++;
		while (tail_chairs > 0) {
			if (NorthChairs.Num() <= 1)
				break;
			auto ChairToRemove = NorthChairs.GetTail();
			ChairToRemove->GetValue()->Destroy();
			NorthChairs.RemoveNode(ChairToRemove);
			tail_chairs--;
		}
	}
	else if (FreeSpaceTail > 0 && FreeSpaceTail > chairs_spacing) {
		while (tail_chairs > 0) {
			NorthChairs.AddTail(GetWorld()->SpawnActor <AChair>(NorthChairs.GetTail()->GetValue()->GetActorLocation() + FVector(-50, 0, 0), FRotator(0, -90, 0)));
			tail_chairs--;
		}
	}

}

void ATable::UpdateChairsEast(float FreeSpaceHead, float FreeSpaceTail)
{

	int head_chairs = FMath::Abs(FreeSpaceHead / chairs_spacing);
	int tail_chairs = FMath::Abs(FreeSpaceTail / chairs_spacing);

	if (FreeSpaceHead < 0) {
		head_chairs++;
		while (head_chairs > 0) {
			if (EastChairs.Num() <= 1)
				break;
			auto ChairToRemove = EastChairs.GetHead();
			ChairToRemove->GetValue()->Destroy();
			EastChairs.RemoveNode(ChairToRemove);
			head_chairs--;
		}
	}
	else if (FreeSpaceHead > 0 && FreeSpaceHead > chairs_spacing) {
		while (head_chairs > 0) {
			EastChairs.AddHead(GetWorld()->SpawnActor <AChair>(EastChairs.GetHead()->GetValue()->GetActorLocation() + FVector(0, -50, 0), FRotator(0, 180, 0)));
			head_chairs--;
		}
	}

	if (FreeSpaceTail < 0) {
		tail_chairs++;
		while (tail_chairs > 0) {
			if (EastChairs.Num() <= 1)
				break;
			auto ChairToRemove = EastChairs.GetTail();
			ChairToRemove->GetValue()->Destroy();
			EastChairs.RemoveNode(ChairToRemove);
			tail_chairs--;
		}
	}
	else if (FreeSpaceTail > 0 && FreeSpaceTail > chairs_spacing) {
		while (tail_chairs > 0) {
			EastChairs.AddTail(GetWorld()->SpawnActor <AChair>(EastChairs.GetTail()->GetValue()->GetActorLocation() + FVector(0, 50, 0), FRotator(0, 180, 0)));
			tail_chairs--;
		}
	}

}

void ATable::UpdateChairsSouth(float FreeSpaceHead, float FreeSpaceTail)
{
	int head_chairs = FMath::Abs(FreeSpaceHead / chairs_spacing);
	int tail_chairs = FMath::Abs(FreeSpaceTail / chairs_spacing);

	if (FreeSpaceHead < 0) {
		head_chairs++;
		while (head_chairs > 0) {
			if (SouthChairs.Num() <= 1)
				break;
			auto ChairToRemove = SouthChairs.GetHead();
			ChairToRemove->GetValue()->Destroy();
			SouthChairs.RemoveNode(ChairToRemove);
			head_chairs--;
		}

	}
	else if (FreeSpaceHead > 0 && FreeSpaceHead > chairs_spacing) {
		while (head_chairs > 0) {
			SouthChairs.AddHead(GetWorld()->SpawnActor <AChair>(SouthChairs.GetHead()->GetValue()->GetActorLocation() + FVector(-50, 0, 0), FRotator(0, 90, 0)));
			head_chairs--;
		}
	}

	if (FreeSpaceTail < 0) {
		tail_chairs++;
		while (tail_chairs > 0) {
			if (SouthChairs.Num() <= 1)
				break;
			auto ChairToRemove = SouthChairs.GetTail();
			ChairToRemove->GetValue()->Destroy();
			SouthChairs.RemoveNode(ChairToRemove);
			tail_chairs--;
		}
	}
	else if (FreeSpaceTail > 0 && FreeSpaceTail > chairs_spacing) {
		while (tail_chairs > 0) {
			SouthChairs.AddTail(GetWorld()->SpawnActor <AChair>(SouthChairs.GetTail()->GetValue()->GetActorLocation() + FVector(50, 0, 0), FRotator(0, 90, 0)));
			tail_chairs--;
		}
	}

}

void ATable::UpdateChairsWest(float FreeSpaceHead, float FreeSpaceTail)
{

	int head_chairs = FMath::Abs(FreeSpaceHead / chairs_spacing);
	int tail_chairs = FMath::Abs(FreeSpaceTail / chairs_spacing);

	if (FreeSpaceHead < 0) {
		head_chairs++;
		while (head_chairs > 0) {
			if (WestChairs.Num() <= 1)
				break;
			auto ChairToRemove = WestChairs.GetHead();
			ChairToRemove->GetValue()->Destroy();
			WestChairs.RemoveNode(ChairToRemove);
			head_chairs--;
		}
	}
	else if (FreeSpaceHead > 0 && FreeSpaceHead > chairs_spacing) {
		while (head_chairs > 0) {
			WestChairs.AddHead(GetWorld()->SpawnActor <AChair>(WestChairs.GetHead()->GetValue()->GetActorLocation() + FVector(0, 50, 0), FRotator(0, 0, 0)));
			head_chairs--;
		}
	}

	if (FreeSpaceTail < 0) {
		tail_chairs++;
		while (tail_chairs > 0) {
			if (WestChairs.Num() <= 1)
				break;
			auto ChairToRemove = WestChairs.GetTail();
			ChairToRemove->GetValue()->Destroy();
			WestChairs.RemoveNode(ChairToRemove);
			tail_chairs--;
		}
	}
	else if (FreeSpaceTail > 0 && FreeSpaceTail > chairs_spacing) {
		while (tail_chairs > 0) {
			WestChairs.AddTail(GetWorld()->SpawnActor <AChair>(WestChairs.GetTail()->GetValue()->GetActorLocation() + FVector(0, -50, 0), FRotator(0, 0, 0)));
			tail_chairs--;
		}
	}

}
