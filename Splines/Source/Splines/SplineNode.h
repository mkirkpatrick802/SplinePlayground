#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineNode.generated.h"

UCLASS()
class SPLINES_API ASplineNode : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spline, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* KnotMesh;

	UPROPERTY(EditAnywhere, Category = Spline)
	USceneComponent* Handles;

	USceneComponent* InHandle;

	USceneComponent* OutHandle;

public:	

	ASplineNode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	FVector CalculatePValue(const FVector& StartLocation, const FVector& EndLocation, const float Time, 
		const bool DrawLines = false, const FColor DebugColor = FColor::Red, const float DebugThickness = 2) const;

	UFUNCTION(BlueprintCallable, Category = Spline)
	float GetTimeFromDistance(const float Distance) const;

	UFUNCTION(BlueprintCallable, Category = Spline)
	FVector GetPointAtTime(const float Time) const;

private:

	// Debugging
	UPROPERTY(EditAnywhere, Category = Spline)
	bool DrawDebugLines = false;

	// Primary Locations
	FVector KnotLocation;
	FVector InHandleLocation;
	FVector OutHandleLocation;

	// Final Point
	FVector PStartLocation;

	// Utilities
	ASplineNode* ConnectedNode;

	float T;
	float SplineLength = 0;

public:

	UFUNCTION(BlueprintCallable, Category = Spline)
	FORCEINLINE void SetConnectedNode( ASplineNode* Knot) { ConnectedNode = Knot; }

	FORCEINLINE FVector GetKnotLocation() const { return KnotLocation; }
	FORCEINLINE FVector GetInHandleLocation() const { return InHandleLocation; }
};
