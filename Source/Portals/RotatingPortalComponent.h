// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PortalComponent.h"
#include "RotatingPortalComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Portal), meta = (BlueprintSpawnableComponent))
class PORTALS_API URotatingPortalComponent : public UPortalComponent
{
	GENERATED_BODY()

public:
    
    UPROPERTY(Category = "Portal Info", EditAnywhere)
    FRotator RotationRot;

    UPROPERTY(Category = "Portal Info", EditAnywhere)
    bool PortalLinkOpositeRotation = false;
	
protected:

    virtual void BeginPlay() override;

    virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

    virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

    virtual void AttachCollisionBehaviors() override;

    AActor* LevelActor = nullptr;

    int32 NormalRotation = 1;
};
