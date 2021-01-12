// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingPortalComponent.h"
#include "EngineUtils.h"

void URotatingPortalComponent::BeginPlay()
{
	UPortalComponent::BeginPlay();
	URotatingPortalComponent* OtherPortal = Cast<URotatingPortalComponent>(PortalLinkComp);
	OtherPortal->RotationRot = RotationRot;

	for (TActorIterator<AActor> ActorIter(GetWorld()); ActorIter; ++ActorIter) {
		AActor* CurrentActor = *ActorIter;
		if (CurrentActor->GetName() == "Level") {
			LevelActor = CurrentActor;
			break;
		}
	}

	if (!PortalLinkOpositeRotation || !NormalRotation) return;
	
	OtherPortal->NormalRotation = -1;
}

void URotatingPortalComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlapActors.Contains(OtherActor)) return;

	FRotator CurrentRot = OtherActor->GetActorRotation();
	FRotator NewRot = OtherActor->GetActorRotation().Add(RotationRot.Pitch, RotationRot.Yaw, RotationRot.Roll);
	OverlapActors.Add(OtherActor);
	PortalLinkComp->OverlapActors.Add(OtherActor);
	FVector PositionOffset = OtherActor->GetActorLocation() - GetOwner()->GetActorLocation();
	FVector PortalLinkPos = PortalLink->GetActorLocation();
	FVector NewPosition = PortalLink->GetActorLocation() + PositionOffset;

	if (OtherActor->GetName().Compare("FirstPersonCharacter_C")) {
		NewRot = LevelActor->GetActorRotation().Add(RotationRot.Pitch, RotationRot.Yaw, RotationRot.Roll);
		LevelActor->SetActorRotation(NewRot * NormalRotation);
		NewPosition = PortalLink->GetActorLocation() + PositionOffset;
		OtherActor->SetActorLocation(NewPosition);
	}
	
	else {
		OtherActor->SetActorLocationAndRotation(NewPosition, NewRot * NormalRotation);
	}
}

void URotatingPortalComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UPortalComponent::OnEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

void URotatingPortalComponent::AttachCollisionBehaviors()
{
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &URotatingPortalComponent::OnBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &URotatingPortalComponent::OnEndOverlap);
}
