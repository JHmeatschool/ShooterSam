// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Kismet/GameplayStatics.h"

#define PI 3.14159f
#define LOG(x) UE_LOG(LogTemp, Display, TEXT(x))
#define LOG_WARNING(x) UE_LOG(LogTemp, Warning, TEXT(x))

class Shape
{
protected:
	int32 Sides;

public:
	virtual void Explain();
};

void Shape::Explain()
{
	LOG("I'm a shape!");
}

class Rectangle : public Shape
{
public:
	void SetSides();

	virtual void Explain() override;
};

void Rectangle::SetSides()
{
	Sides = 4;
}

void Rectangle::Explain()
{
	LOG("I'm a rectangle!");
}

void AGun::BeginPlay()
{
	Super::BeginPlay();

	MuzzleFlashParticleSystem->Deactivate();

	Shape MyShape;
	Rectangle MyRect;

	Shape* ShapePtr1 = &MyShape;
	Shape* ShapePtr2 = &MyRect;

	ShapePtr1->Explain();
	ShapePtr2->Explain();
}

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SceneRoot);

	MuzzleFlashParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Muzzle Flash"));
	MuzzleFlashParticleSystem->SetupAttachment(Mesh);
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	MuzzleFlashParticleSystem->Activate(true);

	if (OwnerController)
	{
		FVector ViewPointLocation;
		FRotator ViewPointRotation;
		OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

		FVector EndLocation = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewPointLocation, EndLocation, ECC_GameTraceChannel2, Params);
		if (IsHit)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactParticleSystem, HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());

			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				UGameplayStatics::ApplyDamage(HitActor, BulletDamage, OwnerController, this, UDamageType::StaticClass());
			}
		}
	}
}