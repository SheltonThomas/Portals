// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetPortalComponent.h"
#include "Kismet/GameplayStatics.h"

void UResetPortalComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()));
}

void UResetPortalComponent::AttachCollisionBehaviors()
{
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &UResetPortalComponent::OnBeginOverlap);
}
