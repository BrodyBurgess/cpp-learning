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

ACppGameplayPracticeCharacter::ACppGameplayPracticeCharacter()
{
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Controller rotation affects the camera rather than directly rotating the character.
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

    // Create the third-person camera rig.
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // Mesh and animation assets are configured in the derived character Blueprint.
}

void ACppGameplayPracticeCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Retrieve the custom GameInstance once when this character begins play.
    // A newly spawned character after map travel retrieves the same session's instance.
    CachedGameInstance = Cast<UMyGameInstance>(GetGameInstance());
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
        UE_LOG(LogCppGameplayPractice, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
    }
}

void ACppGameplayPracticeCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();
    DoMove(MovementVector.X, MovementVector.Y);
}

void ACppGameplayPracticeCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();
    DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ACppGameplayPracticeCharacter::DoMove(float Right, float Forward)
{
    if (GetController() != nullptr)
    {
        // Convert input into movement relative to the controller's yaw.
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
    // The GameInstance owns and validates score changes; the character forwards them.
    if (CachedGameInstance)
    {
        CachedGameInstance->AddScore(Amount);
    }
}

int32 ACppGameplayPracticeCharacter::GetTotalScore() const
{
    // Return the persistent score without exposing its private storage.
    if (CachedGameInstance)
    {
        return CachedGameInstance->GetScore();
    }

    // Safe fallback if the custom GameInstance is unavailable.
    return 0;
}
