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

public:	
	// Sets default values for this actor's properties
	AClimbCloth();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the trigger box has event begin overlap
	UFUNCTION()
	void TriggerBoxBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns Mesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetMesh() { return Mesh; }

};
