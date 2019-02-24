// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	FollowCameraFocusPoint = CreateDefaultSubobject<USceneComponent>(TEXT("FollowCameraFocusPoint"));
	FollowCameraFocusPoint->SetupAttachment(GetMesh());

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	KunaiSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ShurikenSpawnPoint"));
	KunaiSpawnPoint->SetupAttachment(GetMesh());

	AimDownSightFocusPoint = CreateDefaultSubobject<USceneComponent>(TEXT("AimDownSightFocusPoint"));
	AimDownSightFocusPoint->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Attach the camera to the focus point
	CameraBoom->AttachToComponent(FollowCameraFocusPoint, FAttachmentTransformRules::KeepRelativeTransform);

	// Shuriken current count set to total cout
	RestoreAllKunais();

	// Default Interaction state
	bOpenToInteract = false;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	/// To use the tick function, go to the constructor 
	/// and uncomment the " PrimaryActorTick.bCanEverTick = true; "
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::AimDownSight()
{
	// Change the ADS state to true
	AimDownSightState = true;

	// Let the character follow camera rotation
	bUseControllerRotationYaw = true;

	CameraBoom->AttachToComponent(AimDownSightFocusPoint, FAttachmentTransformRules::KeepRelativeTransform);
	CameraBoom->TargetArmLength *= CameraZoomRatio;
}

void APlayerCharacter::ExitAimDownSight()
{
	// Change the ADS state to false
	AimDownSightState = false;

	// Let the character not follow camera rotation
	bUseControllerRotationYaw = false;

	CameraBoom->AttachToComponent(FollowCameraFocusPoint, FAttachmentTransformRules::KeepRelativeTransform);
	CameraBoom->TargetArmLength /= CameraZoomRatio;
}

void APlayerCharacter::ShootKunai()
{
	// Validate the obejct pointer
	// Check if the player is ADSing
	// Check if there is enough kunai to shoot
	if (KunaiObject 
		&& AimDownSightState == true
		&& KunaiCurrentCount > 0)
	{
		// Set the parameter for spawning the shuriken
		FVector kunaiSpawnLocation;
		FRotator kunaiSpawnRotation;
		FActorSpawnParameters kunaiSpawnInfo;
		kunaiSpawnInfo.Owner = this;
		kunaiSpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		kunaiSpawnLocation = KunaiSpawnPoint->GetComponentLocation();
		kunaiSpawnRotation = FollowCamera->GetComponentRotation();

		// Spawn the kunai
		APawn* SpawnedKunai;
		SpawnedKunai = GetWorld()->SpawnActor<APawn>(KunaiObject, kunaiSpawnLocation, kunaiSpawnRotation, kunaiSpawnInfo);

		// Lower the ammo
		KunaiCurrentCount--;
	}
}

void APlayerCharacter::Interact()
{
	if (bOpenToInteract)
	{
		bInteracting = true;
	}
}

void APlayerCharacter::RestoreAllKunais()
{
	KunaiCurrentCount = KunaiTotalCount;
}

void APlayerCharacter::RestoreKunai(int _count)
{
	KunaiCurrentCount = FMath::Max(KunaiTotalCount, KunaiCurrentCount + _count);
}

void APlayerCharacter::OpenToInteraction()
{
	bOpenToInteract = true;
}

void APlayerCharacter::EndInteraction()
{
	bOpenToInteract = false;
	bInteracting = false;
}

