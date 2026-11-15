#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTransitionTrigger.generated.h"

class USphereComponent;

// Reusable trigger that loads a configured level when the player enters it.
UCLASS()
class CPPGAMEPLAYPRACTICE_API ALevelTransitionTrigger : public AActor
{
    GENERATED_BODY()

public:
    ALevelTransitionTrigger();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    USphereComponent* TriggerSphere;

    // Configurable overlap radius for each placed trigger.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radius")
    float DetectionRadius;

    // Name of the destination map, assigned in the editor.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
    FName LevelToLoad;

protected:
    virtual void BeginPlay() override;

    // Bound to the sphere's dynamic overlap delegate.
    UFUNCTION()
    void SphereOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
};
