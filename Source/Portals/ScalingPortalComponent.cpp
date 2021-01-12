// Fill out your copyright notice in the Description page of Project Settings.


#include "ScalingPortalComponent.h"

void UScalingPortalComponent::BeginPlay()
{
	UPortalComponent::BeginPlay();
	UScalingPortalComponent* OtherScalingPortal = Cast<UScalingPortalComponent>(PortalLinkComp);
	if (CopyScalingToLinkedPortal || OtherScalingPortal->CopyScalingToLinkedPortal)
		OtherScalingPortal->ScaleVector = ScaleVector;
}

void UScalingPortalComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlapActors.Contains(OtherActor)) return;
	FVector CurrentScale = OtherActor->GetActorScale();
	FVector NewScale = { CurrentScale.X * ScaleVector.X, CurrentScale.Y * ScaleVector.Y , CurrentScale.Z * ScaleVector.Z };
	OtherActor->SetActorScale3D(NewScale);
	UPortalComponent::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void UScalingPortalComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UPortalComponent::OnEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

void UScalingPortalComponent::AttachCollisionBehaviors()
{
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &UScalingPortalComponent::OnBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &UScalingPortalComponent::OnEndOverlap);
}
