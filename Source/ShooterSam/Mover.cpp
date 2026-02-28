#include "Mover.h"
#include "Math/UnrealMathUtility.h"

UMover::UMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMover::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();
	OriginalRotation = GetOwner()->GetActorRotation();

	SetShouldMove(false);
}

void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector CurrentLocation = GetOwner()->GetActorLocation();

	ReachedTarget = CurrentLocation.Equals(TargetLocation);

	if (!ReachedTarget)
	{
		float Speed = MoveOffset.Length() / MoveTime;
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(NewLocation);
	}

	FRotator TargetRotation = OriginalRotation;

	if (ShouldMove)
	{
		TargetRotation = OriginalRotation + RotationOffset;
	}

	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	float RotateSpeed = RotationOffset.Euler().Size() / MoveTime;
	FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, RotateSpeed);

	GetOwner()->SetActorRotation(NewRotation);
}

bool UMover::GetShouldMove()
{
	return ShouldMove;
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;

	if (ShouldMove)
	{
		TargetLocation = StartLocation + MoveOffset;
	}
	else
	{
		TargetLocation = StartLocation;
	}
}