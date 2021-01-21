// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "Materials/Material.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PortalComponent.generated.h"


UCLASS( ClassGroup=(Portal), meta=(BlueprintSpawnableComponent) )
class PORTALS_API UPortalComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPortalComponent();

	UPROPERTY(Category = "Portal Info", EditAnywhere)	
	int64 PortalNumber = 0;

	UPROPERTY(Category = "Portal Info", EditAnywhere)
	UBoxComponent* BoxComp = nullptr;

	UPROPERTY(Category = "Portal Info", EditAnywhere)
	USceneCaptureComponent2D* PortalView = nullptr;

	UPROPERTY(Category = "Portal Info", EditAnywhere)
	UStaticMeshComponent* PortalMesh = nullptr;

	UPROPERTY(Category = "Portal Info", EditAnywhere)
	UMaterial* PortalMat;

	UPROPERTY(Category = "Portal Info", EditAnywhere)
	UCanvasRenderTarget2D* RenderTarget;

	UPortalComponent* PortalLinkComp;
	TArray<AActor*> OverlapActors;
	AActor* PortalLink = nullptr;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void PortalInit();

	UFUNCTION()
	virtual void AttachCollisionBehaviors();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
