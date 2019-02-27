// Fill out your copyright notice in the Description page of Project Settings.

#include "ClimbableStall.h"

AClimbableStall::AClimbableStall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AClimbableStall::BeginPlay()
{
	Super::BeginPlay();


}

void AClimbableStall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

//void AClimbableStall::OnInteractionStart()
//{
//	
//}
//
//void AClimbableStall::OnInteractionEnd()
//{
//
//}