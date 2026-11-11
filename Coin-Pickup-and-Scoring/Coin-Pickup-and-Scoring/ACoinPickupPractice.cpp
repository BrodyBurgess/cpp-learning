#include "ACoinPickupPractice.h"
#include "Components/SphereComponent.h"
#include "CppGameplayPracticeCharacter.h"

AACoinPickupPractice::AACoinPickupPractice()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create the trigger sphere and make it the Actor's root component.
    PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere."));
    DetectionRadius = 125.0f;
    CoinValue = 10;
    RootComponent = PickupSphere;

    // Use Unreal's Trigger collision preset to generate overlap events.
    PickupSphere->SetCollisionProfileName(TEXT("Trigger"));

    // Call SphereOverlap whenever something enters the trigger sphere.
    PickupSphere->OnComponentBeginOverlap.AddDynamic(
        this,
        &AACoinPickupPractice::SphereOverlap
    );
}

void AACoinPickupPractice::BeginPlay()
{
    Super::BeginPlay();

    // Apply the radius configured for this individual pickup instance.
    PickupSphere->SetSphereRadius(DetectionRadius);
}

void AACoinPickupPractice::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AACoinPickupPractice::SphereOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    // Only award points if the overlapping Actor is our player character.
    ACppGameplayPracticeCharacter* Player = Cast<ACppGameplayPracticeCharacter>(OtherActor);

    if (Player)
    {
        // Store the running total on the player, not on individual coins.
        Player->TotalScore += CoinValue;

        UE_LOG(LogTemp, Warning, TEXT("Coin collected!"));
        UE_LOG(LogTemp, Warning, TEXT("Total score is %d"), Player->TotalScore);

        // Remove this pickup after a successful collection.
        Destroy();
    }
}
