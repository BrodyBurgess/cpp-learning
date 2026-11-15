#include "LevelTransitionTrigger.h"
#include "Components/SphereComponent.h"
#include "CppGameplayPracticeCharacter.h"
#include "Kismet/GameplayStatics.h"

ALevelTransitionTrigger::ALevelTransitionTrigger()
{
    // Overlap events drive this actor; no per-frame updates are needed.
    PrimaryActorTick.bCanEverTick = false;

    TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    DetectionRadius = 150.0f;
    RootComponent = TriggerSphere;

    TriggerSphere->SetCollisionProfileName(TEXT("Trigger"));

    TriggerSphere->OnComponentBeginOverlap.AddDynamic(
        this,
        &ALevelTransitionTrigger::SphereOverlap
    );
}

void ALevelTransitionTrigger::BeginPlay()
{
    Super::BeginPlay();

    // Apply the radius configured on this actor instance in the editor.
    TriggerSphere->SetSphereRadius(DetectionRadius);
}

void ALevelTransitionTrigger::SphereOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    // Only the player character should activate the level transition.
    ACppGameplayPracticeCharacter* Player = Cast<ACppGameplayPracticeCharacter>(OtherActor);

    if (Player)
    {
        // The GameInstance survives map travel, preserving the stored score.
        UGameplayStatics::OpenLevel(this, LevelToLoad);
    }
}
