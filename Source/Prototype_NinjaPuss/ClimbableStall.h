// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActor.h"
#include "ClimbableStall.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_NINJAPUSS_API AClimbableStall : public AInteractActor
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* TriggerBox;

	UPROPERTY(Category = "Interaction", VisibleAnywhere, BlueprintReadOnly)
	TArray<class USceneComponent*> WayPointArray;

public:
	// Sets default values for this actor's properties
	AClimbableStall();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	float TotalTransferTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	float TotalDistanceTravel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bHasUsed;

	/** Determent if the player has interact with this or not  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bInUse;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bInWayPointTransit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	FVector CurrentWayPointLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	FVector DestinationLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	int WayPointCount;

	UPROPERTY()
	bool bHasSetPath;

	UPROPERTY()
	float CurrentPathLength;

	UPROPERTY()
	float LerpDelta;

	UPROPERTY()
	float TimeForCurrentPath;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Finds out the total distance needs to travel as soon as the player interact */
	UFUNCTION()
	float FindTotalDistance();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called as the player is interacting with this actor (C++)
	virtual void OnInteractionStart() override;

	// Called as the player is interacting with this actor (C++)
	virtual void OnInteractionEnd() override;


};
