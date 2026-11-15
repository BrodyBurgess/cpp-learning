#include "LevelTransitionTrigger.h"
#include "Components/SphereComponent.h"
#include "CppGameplayPracticeCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelTransitionTrigger::ALevelTransitionTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
void ALevelTransitionTrigger::BeginPlay()
{
	Super::BeginPlay();

	TriggerSphere->SetSphereRadius(DetectionRadius);
	
}

// Called every frame
void ALevelTransitionTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	ACppGameplayPracticeCharacter* Player = Cast<ACppGameplayPracticeCharacter>(OtherActor);

	if (Player)
	{
		UGameplayStatics::OpenLevel(this, LevelToLoad);
	}

}
