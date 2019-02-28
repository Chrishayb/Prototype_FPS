// Fill out your copyright notice in the Description page of Project Settings.

#include "TomatoBox.h"
#include "Components/StaticMeshComponent.h"

#include "PlayerCharacter.h"

ATomatoBox::ATomatoBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

void ATomatoBox::BeginPlay()
{
	Super::BeginPlay();

}

void ATomatoBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATomatoBox::OnInteractionStart()
{
	Super::OnInteractionStart();

}

void ATomatoBox::OnInteractionEnd()
{
	Super::OnInteractionEnd();

}
