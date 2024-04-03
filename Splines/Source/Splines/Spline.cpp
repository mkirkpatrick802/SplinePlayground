#include "Spline.h"


ASpline::ASpline()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineHolder = CreateDefaultSubobject<USceneComponent>(FName("Spline Holder"));
	SplineHolder->SetupAttachment(RootComponent);
	SetRootComponent(SplineHolder);
}

void ASpline::BeginPlay()
{
	Super::BeginPlay();
}

void ASpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}