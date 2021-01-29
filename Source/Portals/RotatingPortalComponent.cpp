// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingPortalComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

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

	FRotator TempRotation = RotationRot * NormalRotation;
	FRotator NewRot = OtherActor->GetActorRotation().Add(TempRotation.Pitch, TempRotation.Yaw, TempRotation.Roll);
	OverlapActors.Add(OtherActor);
	PortalLinkComp->OverlapActors.Add(OtherActor);
	FVector PositionOffset = OtherActor->GetActorLocation() - GetOwner()->GetActorLocation();
	FVector PortalLinkPos = PortalLink->GetActorLocation();
	FVector NewPosition = PortalLink->GetActorLocation() + PositionOffset;

	if (OtherActor->GetComponentByClass(UCharacterMovementComponent::StaticClass())) {
		NewRot = LevelActor->GetActorRotation().Add(TempRotation.Pitch, TempRotation.Yaw, TempRotation.Roll);
		LevelActor->SetActorRotation(NewRot);
		NewPosition = PortalLink->GetActorLocation() + PositionOffset;
		OtherActor->SetActorLocation(NewPosition);
	}
	
	else
		OtherActor->SetActorLocationAndRotation(NewPosition, NewRot);
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
