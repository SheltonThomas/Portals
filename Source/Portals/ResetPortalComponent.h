// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PortalComponent.h"
#include "ResetPortalComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Portal), meta = (BlueprintSpawnableComponent))
class PORTALS_API UResetPortalComponent : public UPortalComponent
{
	GENERATED_BODY()

protected:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void AttachCollisionBehaviors() override;
	
};
