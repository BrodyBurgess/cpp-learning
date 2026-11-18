#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

// Forward declaration: the header only needs a pointer to this class.
class UMySaveGame;

// GameInstance stays alive while the game runs, including across level changes.
UCLASS()
class CPPGAMEPLAYPRACTICE_API UMyGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    // Increase the score and save the updated value to disk.
    void AddScore(int32 amount);

    // Read the current score without modifying this GameInstance.
    int32 GetScore() const;

    void SavePlayerData();
    void LoadPlayerData();

    // Called when the GameInstance initializes; loads saved progress.
    virtual void Init() override;

private:
    // Current score held in memory while the game is running.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score", meta = (AllowPrivateAccess = "true"))
    int32 TotalScore = 0;

    // Reuse the loaded/created SaveGame object rather than recreating it for each save.
    // UPROPERTY keeps the UObject pointer visible to Unreal's garbage collector.
    UPROPERTY()
    UMySaveGame* CachedSaveData = nullptr;
};
