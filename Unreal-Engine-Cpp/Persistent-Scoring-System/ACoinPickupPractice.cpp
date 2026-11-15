#include "ACoinPickupPractice.h"
#include "Components/SphereComponent.h"
#include "CppGameplayPracticeCharacter.h"

AACoinPickupPractice::AACoinPickupPractice()
{
    // Collection is event-driven, so Tick is unnecessary.
    PrimaryActorTick.bCanEverTick = false;

    PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere."));
    DetectionRadius = 125.0f;
    CoinValue = 10;
    RootComponent = PickupSphere;

    PickupSphere->SetCollisionProfileName(TEXT("Trigger"));

    PickupSphere->OnComponentBeginOverlap.AddDynamic(
        this,
        &AACoinPickupPractice::SphereOverlap
    );
}

void AACoinPickupPractice::BeginPlay()
{
    Super::BeginPlay();

    // Apply the editor-configured radius rather than only the constructor default.
    PickupSphere->SetSphereRadius(DetectionRadius);
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
    ACppGameplayPracticeCharacter* Player = Cast<ACppGameplayPracticeCharacter>(OtherActor);

    if (Player)
    {
        // The character forwards the points to the persistent GameInstance.
        Player->AddScore(CoinValue);

        UE_LOG(LogTemp, Warning, TEXT("Player total score is %d"), Player->GetTotalScore());
        UE_LOG(LogTemp, Warning, TEXT("Coin collected!"));

        // Remove the collected pickup from the level.
        Destroy();
    }
}
