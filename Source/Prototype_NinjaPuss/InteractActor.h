// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractActor.generated.h"

/**
 * Interact Actor are actors that have a mesh, a trigger box, also have implementable function for player to interact with.
 * They are responsible for open up the interact ability to the player as the player triggers within certain range.
 */
UCLASS()
class PROTOTYPE_NINJAPUSS_API AInteractActor : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	class APlayerCharacter* PlayerReference;

public:	
	// Sets default values for this actor's properties
	AInteractActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called as the player triggers and able to use the interaction ability(s)
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnTriggerEnter();

	// Called as the player leave the trigger and no longer able to use the interaction ability(s)
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnTriggerExit();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called as the player is interacting with this actor
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnInteractStart"))
	void OnInteractionStart();

	virtual void InteractionStart();

	// Called as the player is interacting with this actor
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnInteractEnd"))
	void OnInteractionEnd();

	UFUNCTION(BlueprintCallable)
	class APlayerCharacter* GetPlayerRef() { return PlayerReference; }
};
