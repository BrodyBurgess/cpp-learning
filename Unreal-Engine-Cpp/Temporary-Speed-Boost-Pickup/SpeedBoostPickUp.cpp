#include "SpeedBoostPickUp.h"
#include "Components/SphereComponent.h"
#include "CppGameplayPracticeCharacter.h"

ASpeedBoostPickUp::ASpeedBoostPickUp()
{
    // This pickup responds to overlap events, so it doesn't need Tick().
    PrimaryActorTick.bCanEverTick = false;

    // Create a sphere trigger and make it the actor's root component.
    ColSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    RootComponent = ColSphere;
    ColSphere->InitSphereRadius(SphereRadius);
    ColSphere->SetCollisionProfileName(TEXT("Trigger"));

    // Register the callback that runs when another actor enters the sphere.
    ColSphere->OnComponentBeginOverlap.AddDynamic(
        this,
        &ASpeedBoostPickUp::SphereSpeedBoostOverlap
    );
}

void ASpeedBoostPickUp::SphereSpeedBoostOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    // Only the intended player character should be able to collect this pickup.
    ACppGameplayPracticeCharacter* Player = Cast<ACppGameplayPracticeCharacter>(OtherActor);

    if (Player)
    {
        // The function executes here and returns true only for a NEW boost.
        // Don't call it a second time inside this block.
        if (Player->ActivateSpeedBoost())
        {
            Destroy(); // Consumed successfully: remove this pickup from the level.
        }
        // If already boosted, leave the pickup in the world for later.
    }
}
