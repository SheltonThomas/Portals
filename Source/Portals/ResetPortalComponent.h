// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "ResetPortalComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Portal), meta = (BlueprintSpawnableComponent))
class PORTALS_API UResetPortalComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "Portal Info", EditAnywhere)
	FName LevelToLoad;
	UPROPERTY(Category = "Portal Info", EditAnywhere)
	bool CanShootPortal = false;

	UBoxComponent* BoxComp = nullptr;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
