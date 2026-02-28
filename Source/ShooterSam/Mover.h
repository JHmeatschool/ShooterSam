// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERSAM_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:
	UMover();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Mover Setup")
	FVector MoveOffset;

	UPROPERTY(EditAnywhere, Category = "Mover Setup")
	float MoveTime = 4.0f;

	UPROPERTY(VisibleAnywhere, Category = "Mover Setup")
	bool ReachedTarget = false;

	FVector TargetLocation;
	FVector StartLocation;

	bool GetShouldMove();

	UFUNCTION(BlueprintCallable, Category = "Mover Setup")
	void SetShouldMove(bool NewShouldMove);

	UPROPERTY(EditAnywhere, Category = "Mover Setup")
	FRotator RotationOffset;

	FRotator OriginalRotation;

private:
	UPROPERTY(VisibleAnywhere)
	bool ShouldMove = false;
};