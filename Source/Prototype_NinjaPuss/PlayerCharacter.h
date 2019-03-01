// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class EDirection : uint8
{
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD
};

UCLASS()
class PROTOTYPE_NINJAPUSS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

#pragma region CameraComponents

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

#pragma endregion CameraComponents

	/** Spawn loaction for the shuriken */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill_Kunai", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* KunaiSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* FollowCameraFocusPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill_Kunai", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* AimDownSightFocusPoint;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

#pragma region CameraStats

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

#pragma endregion CameraStats

#pragma region Kunai

	UPROPERTY(EditAnywhere, Category = "Skill_Kunai")
	TSubclassOf<class APawn> KunaiObject;

	UPROPERTY(EditDefaultsOnly, Category = "Skill_Kunai")
	int KunaiTotalCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill_Kunai")
	int KunaiCurrentCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill_Kunai")
	bool AimDownSightState;

	UPROPERTY(EditDefaultsOnly, Category = "Skill_Kunai")
	float CameraZoomRatio;

#pragma endregion Kunai

#pragma region Interaction

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	class AInteractActor* InteractTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bOpenToInteract;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bInteracting;

#pragma endregion Interaction

#pragma region Birdeye View

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Birdeye Mode")
	

#pragma endregion Birdeye View

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Called for aim down sight for shooting kunai */
	UFUNCTION(BlueprintCallable, Category = "Skill_Kunai")
	void AimDownSight();

	/** Called for exite aim down sight */
	UFUNCTION(BlueprintCallable, Category = "Skill_Kunai")
	void ExitAimDownSight();

	/** Called for shooting shuriken */
	UFUNCTION(BlueprintCallable, Category = "Skill_Kunai")
	void ShootKunai();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void InteractAction();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for set the kunai count to maximum */
	UFUNCTION(BlueprintCallable, Category = "Skill_Kunai")
	void RestoreAllKunais();

	/** Called for restore certain amount of kunai (but not over the max) */
	UFUNCTION(BlueprintCallable, Category = "Skill_Kunai")
	void RestoreKunai(int _count);

	/** Return the current count of kunai player is holding */
	UFUNCTION(BlueprintCallable, Category = "Skill_Kunai")
	int GetKunaiCount() { return KunaiCurrentCount; }

	/** Set the target to interact for the player */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetInteractionTarget(class AInteractActor* _interactTarget);

	/** Try to remove the interaction target if it exists */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void RemoveInteractionTarget(class AInteractActor* _interactTarget);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OpenToInteraction();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void CloseInteraction();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool IsOpenToInteract() { return bOpenToInteract; }

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool IsPlayerInteracting() { return bInteracting; }



};
