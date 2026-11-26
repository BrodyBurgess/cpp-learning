#include "DirectionalTracePractice.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

ADirectionalTracePractice::ADirectionalTracePractice()
{
    // Enable continuous line tracing every frame.
    PrimaryActorTick.bCanEverTick = true;
}

void ADirectionalTracePractice::BeginPlay()
{
    Super::BeginPlay();

    // Set the maximum detection distance to five meters.
    LineDistance = 500.0f;
}

void ADirectionalTracePractice::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update the trace as the actor moves or rotates.
    PerformLineTrace(LineDistance);
}

void ADirectionalTracePractice::PerformLineTrace(float Distance)
{
    // Calculate the trace origin and endpoint using the actor's
    // current world location and forward direction.
    const FVector TraceStart = GetActorLocation();

    const FVector TraceEnd =
        TraceStart + (GetActorForwardVector() * Distance);

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;

    // Prevent the trace from detecting its own actor.
    QueryParams.AddIgnoredActor(this);

    // Detect the first blocking hit on the Visibility channel.
    const bool bDidHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        TraceStart,
        TraceEnd,
        ECC_Visibility,
        QueryParams
    );

    if (bDidHit)
    {
        AActor* HitActor = HitResult.GetActor();
        const FVector HitLocation = HitResult.ImpactPoint;

        // Draw a green line ending at the collision impact point.
        DrawDebugLine(
            GetWorld(),
            TraceStart,
            HitLocation,
            FColor::Green,
            false,
            0.0f,
            0,
            3.0f
        );

        // Only log when a valid, different actor is detected.
        if (HitActor && HitActor != PreviousHitActor)
        {
            const FString ActorName = HitActor->GetName();

            UE_LOG(LogTemp, Warning, TEXT("Actor Hit: %s"), *ActorName);

            // Remember the detected actor for the next frame.
            PreviousHitActor = HitActor;
        }
    }
    else
    {
        // Draw a red line across the full distance when no hit occurs.
        DrawDebugLine(
            GetWorld(),
            TraceStart,
            TraceEnd,
            FColor::Red,
            false,
            0.0f,
            0,
            3.0f
        );

        // Reset detection so the same actor can be detected again.
        PreviousHitActor = nullptr;
    }
}
