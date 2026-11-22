#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "CppGameplayPracticeCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UMyGameInstance;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/** Third-person player character with health, persistent scoring, and a timed speed boost. */
UCLASS(abstract)
class ACppGameplayPracticeCharacter : public ACharacter
{
    GENERATED_BODY()

    /** Camera boom that follows behind the player. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;

    /** Camera attached to the boom. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;

protected:
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* MouseLookAction;

public:
    ACppGameplayPracticeCharacter();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    int32 Health = 100;

    void Heal(int32 Amount);

    /** Existing scoring system: delegates score updates to the custom GameInstance. */
    void AddScore(int32 Amount);
    int32 GetTotalScore() const;

    /** Returns true only when a NEW boost starts; false if already boosted. */
    bool ActivateSpeedBoost();

    /** Timer callback: restores the speed recorded before the boost. */
    void EndSpeedBoost();

protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void BeginPlay() override;

private:
    /** Cached GameInstance from the earlier persistent-scoring exercise. */
    UPROPERTY()
    UMyGameInstance* CachedGameInstance = nullptr;

    /** Saved speed to restore when the boost expires. */
    float NormalSpeed = 0.0f;

    /** Speed applied while the temporary boost is active. */
    float BoostedSpeed = 1000.0f;

    /** Identifies the timer responsible for ending this boost. */
    FTimerHandle SpeedBoostTimer;

    /** Prevents overlapping boosts and accidental speed overwrites. */
    bool bIsSpeedBoostActive = false;

protected:
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);

public:
    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoMove(float Right, float Forward);

    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoLook(float Yaw, float Pitch);

    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoJumpStart();

    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoJumpEnd();

    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
