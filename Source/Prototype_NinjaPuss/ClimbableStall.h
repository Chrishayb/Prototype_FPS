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

private:

// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
// 	class UStaticMeshComponent* Mesh;
// 
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
// 	class UBoxComponent* TriggerBox;
// 
// 	UPROPERTY(Category = "Interaction", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
// 	TArray<class USceneComponent*> WayPointArray;

public:
	// Sets default values for this actor's properties
	AClimbableStall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called as the player is interacting with this actor
	//UFUNCTION(BlueprintImplementableEvent)
	//virtual void OnInteractionStart() override;

	//UFUNCTION(BlueprintImplementableEvent)
	//virtual void OnInteractionEnd() override;
};
