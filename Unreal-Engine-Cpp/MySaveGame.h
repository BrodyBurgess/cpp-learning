#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

// Data container that Unreal serializes to and from a save slot.
UCLASS()
class CPPGAMEPLAYPRACTICE_API UMySaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    // Score stored on disk; a new save starts at zero.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SavedScore")
    int32 SavedScore = 0;
};
