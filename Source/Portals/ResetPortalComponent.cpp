// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetPortalComponent.h"
#include "Kismet/GameplayStatics.h"

void UResetPortalComponent::BeginPlay()
{
	if (LevelToLoad == "")
		LevelToLoad = FName((*GetWorld()->GetName()));

	BoxComp = Cast<UBoxComponent>(GetOwner()->GetComponentByClass(UBoxComponent::StaticClass()));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &UResetPortalComponent::OnBeginOverlap);
}

void UResetPortalComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetComponentByClass(UCharacterMovementComponent::StaticClass()) || CanShootPortal) {
		UGameplayStatics::OpenLevel(this, LevelToLoad);
	}
}
