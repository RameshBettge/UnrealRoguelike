// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "CorridorGenerator.generated.h"

USTRUCT()
struct FCorridorElement
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString ElementName;

	UPROPERTY(EditAnywhere)
		UStaticMesh* Mesh;

	// Z-Scale for Rows.
	UPROPERTY(EditAnywhere)
	float Height;

	// If the side offset should be calculated from the edge instead of from the middle.
	UPROPERTY(EditAnywhere)
	bool bUseAutoEdgeOffset = false;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "!bUseAutoEdgeOffset"))
	bool bEdgeOffset = false;


	UPROPERTY(EditAnywhere, meta = (EditCondition = "!bUseAutoEdgeOffset"))
	float SideOffset = 0.f;

	UPROPERTY(EditAnywhere)
	bool bIsRow = false;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "!bIsRow"))
	float width;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bIsRow"))
	float Spacing;

	//UPROPERTY(EditAnywhere, meta = (EditCondition = "bIsRow"))
	//	float YSize = 0.f;

	USceneComponent* Container = nullptr;

	FCorridorElement(FString Name, UStaticMesh* Mesh, float Height, float Width)
	{
		this->ElementName = Name, this->Mesh = Mesh, this->Height = Height, this->width = Width;
	}
	FCorridorElement() {};
};


UCLASS()
class ROGUELIKE_API ACorridorGenerator : public AActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	ACorridorGenerator();
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "Meshes")
		UStaticMesh* Floor;
	UPROPERTY(EditAnywhere, Category = "Meshes")
		UStaticMesh* Roof;
	//UPROPERTY(EditAnywhere, Category = "Meshes")
	//	UStaticMesh* RoofSupport;


	//UPROPERTY(EditAnywhere, Category = "Size Parameters")
	//	float Width = 2.f;

	UPROPERTY(EditAnywhere, Category = "Size Parameters", meta = (MakeEditWidget))
		FVector Controller = FVector(50.0f, .0f, 0.f);

	//UPROPERTY(EditAnywhere, Category = "Size Parameters|Roof")
	//	float RoofHeight = 200.f;
	//UPROPERTY(EditAnywhere, Category = "Size Parameters|Roof")
	//	float RoofSupportSpacing = 100.f;
	//UPROPERTY(EditAnywhere, Category = "Size Parameters|Roof")
	//	float RoofSupportEdgeOffset = 30.f;

	//UPROPERTY(EditAnywhere, Category = "Debugging")
	//	TArray<UStaticMeshComponent*> Supports;
	//UPROPERTY(EditAnywhere, Category = "Debugging")
	//	bool bGenerateInTick;



private:
	UPROPERTY(meta = (MakeEditWidget))
		FVector Root = FVector::ZeroVector;

	/// UProperties are set so I can move the Containers.
	UPROPERTY(EditAnywhere, Category = "Debugging")
		USceneComponent* ZRotator;
	UPROPERTY(EditAnywhere, Category = "Debugging")
		USceneComponent* FloorScaler;
	UPROPERTY(EditAnywhere, Category = "Debugging")
		USceneComponent* RoofScaler;

private:
	float GetPlanarMagnitude(FVector);

	void CreateSupports();
	void ClearSupports();
	void InstantiateSupportRow(int NumberOfSupports, float YPos, FString SideName);
	UStaticMeshComponent* InstantiateMesh(UStaticMesh* Mesh, USceneComponent* Parent, FName MeshName = TEXT("Mesh"));



	UPROPERTY(EditAnywhere, Category = "Modular")
	float FloorWidth;
	UPROPERTY(EditAnywhere, Category = "Modular")
	float RoofHeight;
	UPROPERTY(EditAnywhere, Category = "Modular")
	float RoofWidth;

	UPROPERTY(EditAnywhere, Category = "Modular")
		float AutoEdgeOffset= 50.f;

	UPROPERTY(EditAnywhere, Category = "Modular")
	TArray<FCorridorElement> Elements;
	FCorridorElement FloorElement;
	FCorridorElement RoofElement;

	TArray<USceneComponent*> Containers;
	USceneComponent* RowsContainer = nullptr;

	void CreateModular();
	void CreateElement(FCorridorElement E);
	void SetContainerPosition(FCorridorElement Element);
	void SetContainerScale(FCorridorElement Element);
	void SetContainerRotation(FCorridorElement Element);

	void CreateModularRow(FCorridorElement Element);
	void InstantiateModularRow(FCorridorElement E, int NumberOfSupports, float YPos, FString SideName);
};
