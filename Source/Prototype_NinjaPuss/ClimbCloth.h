// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClimbCloth.generated.h"

UCLASS()
class PROTOTYPE_NINJAPUSS_API AClimbCloth : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* TriggerBox;
	
	UPROPERTY(Category = "Interaction", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<class USceneComponent*> WayPointArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class APlayerCharacter* PlayerReference;

public:	
	// Sets default values for this actor's properties
	AClimbCloth();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	float TotalTransferTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	float TimeForEachWayPointLerp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	float TotalDistanceTravel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bHasUsed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bInUse;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bCanUse;

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

	// Called when the trigger box has event begin overlap
	UFUNCTION()
	void TriggerBoxBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Called when the trigger box has event end overlap
	UFUNCTION()
	void TriggerBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void OnPlayerInteraction();

	UFUNCTION(BlueprintCallable)
	void OnEndInteraction();

	/** Finds out the total distance needs to travel as soon as the player interact */
	UFUNCTION()
	float FindTotalDistance();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns Mesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetMesh() { return Mesh; }

	/** Returns PlayerCharacter reference */
	FORCEINLINE class APlayerCharacter* GetPlayerRef() { return PlayerReference; }
};
