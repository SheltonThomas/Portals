// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PortalComponent.h"
#include "ScalingPortalComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Portal), meta = (BlueprintSpawnableComponent) )
class PORTALS_API UScalingPortalComponent : public UPortalComponent
{
	GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite, Category = "Portal Info", EditAnywhere)
    FVector ScaleVector;

    UPROPERTY(Category = "Portal Info", EditAnywhere)
    bool CopyScalingToLinkedPortal = true;
    
protected:

    virtual void BeginPlay() override;

    virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

    virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

    virtual void AttachCollisionBehaviors() override;
};
