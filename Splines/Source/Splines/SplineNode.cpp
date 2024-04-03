
#include "SplineNode.h"

ASplineNode::ASplineNode()
{
	PrimaryActorTick.bCanEverTick = true;

	KnotMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Knot Mesh"));
	KnotMesh->SetupAttachment(RootComponent);
	SetRootComponent(KnotMesh);

	Handles = CreateDefaultSubobject<USceneComponent>(FName("Handle Holder"));
	Handles->SetupAttachment(RootComponent);

	InHandle = CreateDefaultSubobject<USceneComponent>(FName("In Handle"));
	InHandle->SetupAttachment(Handles);

	OutHandle = CreateDefaultSubobject<USceneComponent>(FName("Out Handle"));
	OutHandle->SetupAttachment(Handles);
}

void ASplineNode::BeginPlay()
{
	Super::BeginPlay();

	InHandle->AddRelativeLocation(FVector(250, 0, 0));
	OutHandle->AddRelativeLocation(FVector(-250, 0, 0));
}

void ASplineNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	KnotLocation = KnotMesh->GetComponentLocation();
	InHandleLocation = InHandle->GetComponentLocation();
	OutHandleLocation = OutHandle->GetComponentLocation();

	DrawDebugSphere(GetWorld(), InHandleLocation, 35, 16, FColor::Emerald);
	DrawDebugSphere(GetWorld(), OutHandleLocation, 35, 16, FColor::Red);

	SplineLength = 0;
	PStartLocation = KnotLocation;
	T = 0;
	while(T <= 1)
	{
		T += .05f;
		if (!ConnectedNode) continue;

		FVector P = GetPointAtTime(T);
		DrawDebugLine(GetWorld(), PStartLocation, P, FColor::Magenta, false, -1, 0, 5);

		SplineLength += (PStartLocation - P).Length();
		PStartLocation = P;
	}
}

FVector ASplineNode::CalculatePValue(const FVector& StartLocation, const FVector& EndLocation, const float Time,
	const bool DrawLines, const FColor DebugColor, const float DebugThickness) const
{
	const FVector PValue = FMath::Lerp(StartLocation, EndLocation, Time);

	if(DrawDebugLines)
	{
		DrawDebugLine(GetWorld(), StartLocation, PValue, DebugColor, false, -1, 0, DebugThickness);
	}

	return PValue;
}

float ASplineNode::GetTimeFromDistance(const float Distance) const
{
	return Distance / SplineLength;
}

FVector ASplineNode::GetPointAtTime(const float Time) const
{
	if (!ConnectedNode) return FVector::Zero();

	const FVector a = CalculatePValue(KnotLocation, OutHandleLocation, Time, DrawDebugLines);
	const FVector b = CalculatePValue(OutHandleLocation, ConnectedNode->GetInHandleLocation(), Time, DrawDebugLines);
	const FVector c = CalculatePValue(ConnectedNode->GetInHandleLocation(), ConnectedNode->GetKnotLocation(), Time, DrawDebugLines);

	const FVector d = CalculatePValue(a, b, Time, DrawDebugLines);
	const FVector e = CalculatePValue(d, c, Time, DrawDebugLines);

	return CalculatePValue(d, e, Time, DrawDebugLines);
}
