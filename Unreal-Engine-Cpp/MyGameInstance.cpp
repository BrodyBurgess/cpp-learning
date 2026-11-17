#include "MyGameInstance.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::AddScore(int32 amount)
{
    // Ignore zero or negative pickup values.
    if (amount > 0)
    {
        TotalScore += amount;

        // Persist each valid score change immediately.
        SavePlayerData();
    }
}

int32 UMyGameInstance::GetScore() const
{
    return TotalScore;
}

void UMyGameInstance::SavePlayerData()
{
    if (CachedSaveData)
    {
        // Copy the in-memory score into the object that will be serialized.
        CachedSaveData->SavedScore = TotalScore;

        UE_LOG(LogTemp, Warning, TEXT("The Score Is: %d"), CachedSaveData->SavedScore);

        // "PlayerSave" is the save slot name; 0 is the user index.
        bool bSaveSuccessful = UGameplayStatics::SaveGameToSlot(CachedSaveData, TEXT("PlayerSave"), 0);

        if (bSaveSuccessful)
        {
            UE_LOG(LogTemp, Warning, TEXT("Game saved successfully!"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to save game!"));
        }
    }
    else
    {
        // Avoid dereferencing a null pointer if no save object is available.
        UE_LOG(LogTemp, Warning, TEXT("Save skipped, cached was invalid"));
    }
}

void UMyGameInstance::LoadPlayerData()
{
    bool bSaveExist = UGameplayStatics::DoesSaveGameExist(TEXT("PlayerSave"), 0);

    if (bSaveExist)
    {
        // Load the disk save and cast it to our custom SaveGame class.
        CachedSaveData = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSave"), 0));

        if (CachedSaveData)
        {
            // Restore the score from the saved object into the GameInstance.
            TotalScore = CachedSaveData->SavedScore;
            UE_LOG(LogTemp, Warning, TEXT("LoadedScore: %d"), TotalScore);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load save data!"));

            // If loading fails, provide a fresh object for future saves.
            CachedSaveData = Cast<UMySaveGame>(
                UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass())
            );
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No save file found!"));

        // First run: start with a new in-memory SaveGame object.
        CachedSaveData = Cast<UMySaveGame>(
            UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass())
        );
    }
}

void UMyGameInstance::Init()
{
    Super::Init();

    // Restore progress when the GameInstance starts.
    LoadPlayerData();
}
