// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractActor.h"
#include "Kismet/GameplayStatics.h"

#include "PlayerCharacter.h"

// Sets default values
AInteractActor::AInteractActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AInteractActor::OnTriggerEnter()
{
	if (PlayerReference)
	{
		PlayerReference->SetInteractionTarget(this);
	}
}

void AInteractActor::OnTriggerExit()
{
	if (PlayerReference)
	{
		PlayerReference->RemoveInteractionTarget(this);
	}
}

// Called when the game starts or when spawned
void AInteractActor::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerReference = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

}

// Called every frame
void AInteractActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

