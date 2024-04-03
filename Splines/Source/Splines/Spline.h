#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spline.generated.h"

UCLASS()
class SPLINES_API ASpline : public AActor
{
	GENERATED_BODY()

	USceneComponent* SplineHolder;

public:	

	ASpline();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
