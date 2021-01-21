// Fill out your copyright notice in the Description page of Project Settings.

#include "PortalComponent.h"
#include "EngineUtils.h"


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
	PortalInit();
	AttachCollisionBehaviors();
	// ...
}

void UPortalComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlapActors.Contains(OtherActor)) return;
	OverlapActors.Add(OtherActor);
	PortalLinkComp->OverlapActors.Add(OtherActor);
	FVector PositionOffset = OtherActor->GetActorLocation() - GetOwner()->GetActorLocation();
	FVector PortalLinkPos = PortalLink->GetActorLocation();
	FVector NewPosition = PortalLink->GetActorLocation() + PositionOffset;
	OtherActor->SetActorLocationAndRotation(NewPosition, OtherActor->GetActorRotation());
}

void UPortalComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlapActors.Remove(OtherActor);
}

// Called every frame
void UPortalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	PortalView->TextureTarget = RenderTarget;
	PortalView->CaptureScene();
	// ...
}

void UPortalComponent::PortalInit()
{
	for (TActorIterator<AActor> ActorIter(GetWorld()); ActorIter; ++ActorIter) {
		AActor* CurrentActor = *ActorIter;
		if (CurrentActor == GetOwner()) continue;
		if (!(CurrentActor->GetComponentByClass(UPortalComponent::StaticClass()))) continue;
		UPortalComponent* PortalComponent = Cast<UPortalComponent>(CurrentActor->GetComponentByClass(UPortalComponent::StaticClass()));
		if (PortalComponent->PortalNumber == PortalNumber) {
			PortalLink = CurrentActor;
			PortalLinkComp = PortalComponent;
			BoxComp = Cast<UBoxComponent>(GetOwner()->GetComponentByClass(UBoxComponent::StaticClass()));
			PortalMesh = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));
			PortalMat = Cast<UMaterial>(PortalMesh->GetMaterial(0));
			PortalView = Cast<USceneCaptureComponent2D>(GetOwner()->GetComponentByClass(USceneCaptureComponent2D::StaticClass()));
			PortalView->TextureTarget = RenderTarget;

			PortalMat->SetShadingModel(MSM_Unlit);
		}
	}
}

void UPortalComponent::AttachCollisionBehaviors()
{
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &UPortalComponent::OnBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &UPortalComponent::OnEndOverlap);
}

