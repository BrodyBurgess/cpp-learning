#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACoinPickupPractice.generated.h"

class USphereComponent;

// Collectible actor that awards points when the player overlaps its sphere.
UCLASS()
class CPPGAMEPLAYPRACTICE_API AACoinPickupPractice : public AActor
{
    GENERATED_BODY()

public:
    AACoinPickupPractice();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    USphereComponent* PickupSphere;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
    float DetectionRadius;

    // Points awarded by this individual pickup.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
    int32 CoinValue;

protected:
    virtual void BeginPlay() override;

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
