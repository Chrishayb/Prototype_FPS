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

	/** Spawn loaction for the shuriken */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ShurikenSpawnPoint;


#pragma endregion CameraComponents
	
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

#pragma region CombatStats

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	float DodgeCooldown;

#pragma endregion CombatStats

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

	/** Called for shooting shuriken */
	UFUNCTION(BlueprintCallable, Category = "Skill")
	void ShootShuriken();

	/** Called for character dash/dodge ability */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Dash(EDirection _direction);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
