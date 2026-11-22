#include "CppGameplayPracticeCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "CppGameplayPractice.h"
#include "MyGameInstance.h"
#include "TimerManager.h"
#include "Engine/World.h"

ACppGameplayPracticeCharacter::ACppGameplayPracticeCharacter()
{
    // Standard third-person character collision and movement settings.
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 500.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

    // Camera boom and follow camera are inherited by the character Blueprint.
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
}

void ACppGameplayPracticeCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Used by the existing scoring system, not by the speed boost.
    CachedGameInstance = Cast<UMyGameInstance>(GetGameInstance());

    // Do NOT activate the boost here: the pickup actor triggers it on overlap.
}

void ACppGameplayPracticeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACppGameplayPracticeCharacter::Move);
        EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ACppGameplayPracticeCharacter::Look);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACppGameplayPracticeCharacter::Look);
    }
    else
    {
        UE_LOG(LogCppGameplayPractice, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
    }
}

void ACppGameplayPracticeCharacter::Move(const FInputActionValue& Value)
{
    // Convert 2D input into right/forward movement.
    const FVector2D MovementVector = Value.Get<FVector2D>();
    DoMove(MovementVector.X, MovementVector.Y);
}

void ACppGameplayPracticeCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();
    DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ACppGameplayPracticeCharacter::DoMove(float Right, float Forward)
{
    if (GetController() != nullptr)
    {
        const FRotator Rotation = GetController()->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, Forward);
        AddMovementInput(RightDirection, Right);
    }
}

void ACppGameplayPracticeCharacter::DoLook(float Yaw, float Pitch)
{
    if (GetController() != nullptr)
    {
        AddControllerYawInput(Yaw);
        AddControllerPitchInput(Pitch);
    }
}

void ACppGameplayPracticeCharacter::DoJumpStart()
{
    Jump();
}

void ACppGameplayPracticeCharacter::DoJumpEnd()
{
    StopJumping();
}

void ACppGameplayPracticeCharacter::Heal(int32 Amount)
{
    Health += Amount;
    UE_LOG(LogTemp, Warning, TEXT("Player health after healing: %d"), Health);
}

void ACppGameplayPracticeCharacter::AddScore(int32 Amount)
{
    if (CachedGameInstance)
    {
        CachedGameInstance->AddScore(Amount);
    }
}

int32 ACppGameplayPracticeCharacter::GetTotalScore() const
{
    if (CachedGameInstance)
    {
        return CachedGameInstance->GetScore();
    }
    return 0;
}

bool ACppGameplayPracticeCharacter::ActivateSpeedBoost()
{
    // Reject another pickup while a boost is running.
    // Returning false lets that pickup remain available for later.
    if (!bIsSpeedBoostActive)
    {
        // Save the actual current speed rather than assuming a default value.
        NormalSpeed = GetCharacterMovement()->MaxWalkSpeed;

        BoostedSpeed = 1000.0f;
        GetCharacterMovement()->MaxWalkSpeed = BoostedSpeed;
        bIsSpeedBoostActive = true;

        // One-shot timer: call EndSpeedBoost after 5 seconds.
        // 'this' points to this character; &Class::Function identifies the callback.
        GetWorld()->GetTimerManager().SetTimer(
            SpeedBoostTimer,
            this,
            &ACppGameplayPracticeCharacter::EndSpeedBoost,
            5.0f,
            false
        );

        // The pickup checks this result before destroying itself.
        return true;
    }

    return false;
}

void ACppGameplayPracticeCharacter::EndSpeedBoost()
{
    // Restore the saved speed and allow future pickups to activate.
    GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
    bIsSpeedBoostActive = false;
}
