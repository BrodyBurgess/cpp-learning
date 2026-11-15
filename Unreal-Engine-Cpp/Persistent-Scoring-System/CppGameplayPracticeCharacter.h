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

// Third-person character that forwards score operations to the GameInstance.
UCLASS(abstract)
class ACppGameplayPracticeCharacter : public ACharacter
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
    UCameraComponent* FollowCamera;

protected:
    UPROPERTY(EditAnywhere, Category="Input")
    UInputAction* JumpAction;
    UPROPERTY(EditAnywhere, Category="Input")
    UInputAction* MoveAction;
    UPROPERTY(EditAnywhere, Category="Input")
    UInputAction* LookAction;
    UPROPERTY(EditAnywhere, Category="Input")
    UInputAction* MouseLookAction;

public:
    ACppGameplayPracticeCharacter();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
    int32 Health = 100;

    void Heal(int32 Amount);

    // Forward score changes to the GameInstance, which owns the total.
    void AddScore(int32 Amount);

    // Read the score without modifying this character.
    int32 GetTotalScore() const;

protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void BeginPlay() override;

private:
    // Cache the typed GameInstance once per character to avoid repeated casts.
    UPROPERTY()
    UMyGameInstance* CachedGameInstance = nullptr;

protected:
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);

public:
    UFUNCTION(BlueprintCallable, Category="Input")
    virtual void DoMove(float Right, float Forward);
    UFUNCTION(BlueprintCallable, Category="Input")
    virtual void DoLook(float Yaw, float Pitch);
    UFUNCTION(BlueprintCallable, Category="Input")
    virtual void DoJumpStart();
    UFUNCTION(BlueprintCallable, Category="Input")
    virtual void DoJumpEnd();

    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
