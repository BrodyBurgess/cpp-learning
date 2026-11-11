#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACoinPickupPractice.generated.h"

class USphereComponent;

// A collectible Actor that awards points when the player overlaps its trigger sphere.
UCLASS()
class CPPGAMEPLAYPRACTICE_API AACoinPickupPractice : public AActor
{
    GENERATED_BODY()

public:
    AACoinPickupPractice();

    // Trigger used to detect when another Actor enters the pickup area.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    USphereComponent* PickupSphere;

    // Can be adjusted separately for each placed pickup in the editor.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
    float DetectionRadius;

    // Points awarded to the player when this pickup is collected.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
    int32 CoinValue;

protected:
    virtual void BeginPlay() override;

    // Bound to the sphere's begin-overlap event in the constructor.
    UFUNCTION()
    void SphereOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

public:
    virtual void Tick(float DeltaTime) override;
};
