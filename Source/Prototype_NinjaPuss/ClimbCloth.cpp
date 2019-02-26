// Fill out your copyright notice in the Description page of Project Settings.

#include "ClimbCloth.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AClimbCloth::AClimbCloth()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetGenerateOverlapEvents(false);
	RootComponent = Mesh;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetGenerateOverlapEvents(true);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AClimbCloth::TriggerBoxBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AClimbCloth::TriggerBoxEndOverlap);
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetupAttachment(RootComponent);

	// Set the default state
	bHasUsed = false;
	bInUse = false;
	bCanUse = true;
}

// Called when the game starts or when spawned
void AClimbCloth::BeginPlay()
{
	Super::BeginPlay();
	
}

void AClimbCloth::TriggerBoxBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (playerCharacter)
	{
		PlayerReference = playerCharacter;
		PlayerReference->OpenToInteraction();
	}
}

void AClimbCloth::TriggerBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (playerCharacter)
	{
		PlayerReference->CloseInteraction();
	}
}

void AClimbCloth::OnPlayerInteraction()
{
	// Set the first way point for the action
	WayPointCount = 0;
	CurrentWayPointLoc = PlayerReference->GetActorLocation();
	DestinationLoc = WayPointArray[0]->GetComponentLocation();
	TimeForEachWayPointLerp = TotalTransferTime / WayPointArray.Num();
	TotalDistanceTravel = FindTotalDistance();
	CurrentPathLength = FVector::Distance(CurrentWayPointLoc, DestinationLoc);
	TimeForCurrentPath = (CurrentPathLength / TotalDistanceTravel) * TotalTransferTime;

	// Initiate the interaction
	bHasSetPath = true;
	bInUse = true;
	LerpDelta = 0.0f;
	
	// Disable the player action
	PlayerReference->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerReference->CloseInteraction();
}

void AClimbCloth::OnEndInteraction()
{
	// Re-Enable the player action
	PlayerReference->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	bHasUsed = true;
	bInUse = false;
	bCanUse = false;
}

float AClimbCloth::FindTotalDistance()
{
	float totalDistanceResult = 0.0f;

	for (int i = 0; i < WayPointArray.Num(); ++i)
	{
		if (i == 0)
		{
			totalDistanceResult += 
				FVector::Distance(PlayerReference->GetActorLocation(), WayPointArray[0]->GetComponentLocation());
			continue;
		}

		totalDistanceResult += 
			FVector::Distance(WayPointArray[i-1]->GetComponentLocation(), WayPointArray[i]->GetComponentLocation());
	}

	return totalDistanceResult;
}

// Called every frame
void AClimbCloth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bInUse && PlayerReference)
	{
		if (PlayerReference->IsPlayerInteracting())
		{
			OnPlayerInteraction();
		}
	}

	// Run the check for the interaction
	if (bHasSetPath && bInUse && !bHasUsed)
	{
		// Increament the time the move
		LerpDelta += DeltaTime;

		bool reachedDestination = false;
		float leakTime;
		if (LerpDelta > 1.0f)
		{
			reachedDestination = true;
			leakTime = LerpDelta - 1.0f;
			LerpDelta = 1.0f;
		}

		// Move the actor
		FVector resultLocation;
		float alpha = LerpDelta / TimeForCurrentPath;
		resultLocation = FMath::Lerp(CurrentWayPointLoc, DestinationLoc, LerpDelta);
		PlayerReference->SetActorLocation(resultLocation);

		// Check if the player has reach the current destination
		if (reachedDestination)
		{
			WayPointCount++;
			if (WayPointCount >= WayPointArray.Num())
			{
				// End the interaction and unlock player movement
				OnEndInteraction();
			}
			else
			{
				LerpDelta = leakTime; // Reset the lerp delta time and add the leak time onto it
				CurrentWayPointLoc = DestinationLoc;
				DestinationLoc = WayPointArray[WayPointCount]->GetComponentLocation();
				CurrentPathLength = FVector::Distance(CurrentWayPointLoc, DestinationLoc);
				TimeForCurrentPath = (CurrentPathLength / TotalDistanceTravel) * TotalTransferTime;
			}

		}

	}
	

	

}

