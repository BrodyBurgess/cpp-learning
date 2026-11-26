#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DirectionalTracePractice.generated.h"

UCLASS()
class CPPGAMEPLAYPRACTICE_API ADirectionalTracePractice : public AActor
{
    GENERATED_BODY()

public:
    ADirectionalTracePractice();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

private:
    // Maximum trace distance in Unreal units (centimeters).
    float LineDistance;

    // Stores the previously detected actor to prevent repeated logging.
    AActor* PreviousHitActor = nullptr;

    // Performs a directional line trace using the supplied distance.
    void PerformLineTrace(float Distance);
};
