#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeedBoostPickUp.generated.h"

class USphereComponent;

/** Placeable pickup that grants a temporary speed boost when collected. */
UCLASS()
class CPPGAMEPLAYPRACTICE_API ASpeedBoostPickUp : public AActor
{
    GENERATED_BODY()

public:
    ASpeedBoostPickUp();

    /** Overlap trigger; retained as a UPROPERTY for Unreal reflection/GC. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    USphereComponent* ColSphere;

    /** Default radius of the trigger sphere (in Unreal units). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereSize")
    float SphereRadius = 125.0f;

protected:
    /** AddDynamic requires a UFUNCTION with the overlap delegate's signature. */
    UFUNCTION()
    void SphereSpeedBoostOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
};
