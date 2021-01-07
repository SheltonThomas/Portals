// Fill out your copyright notice in the Description page of Project Settings.

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PortalComponent.h"

// Sets default values for this component's properties
UPortalComponent::UPortalComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPortalComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UPortalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPortalComponent::SetPortalLink(AActor* link)
{
	PortalLink = link;
}

