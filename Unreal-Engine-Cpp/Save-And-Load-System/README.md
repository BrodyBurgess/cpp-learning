# Unreal Engine C++ — Save and Load System

A learning exercise in **Unreal Engine 5 C++** that extends a coin-collection scoring system with persistent save data. The player's score is saved to disk after a valid coin pickup and restored when a new play session begins.

## Features

- Stores the current score in a custom `UGameInstance` subclass.
- Uses a custom `USaveGame` subclass to hold the saved score.
- Automatically saves after positive score changes.
- Automatically loads the saved score when `GameInstance::Init()` runs.
- Reuses a cached SaveGame object instead of allocating a new one on every pickup.
- Handles missing save files and failed loads by creating a fresh SaveGame object.
- Logs save success, save failure, and load results for debugging.

## Files

| File | Purpose |
| --- | --- |
| `MyGameInstance.h/.cpp` | Owns the runtime score and coordinates saving/loading. |
| `MySaveGame.h/.cpp` | Defines the serializable `SavedScore` data. |

## How it works

1. Unreal initializes `UMyGameInstance` and calls `Init()`.
2. `LoadPlayerData()` looks for slot `PlayerSave` (user index `0`).
3. If the save loads, `CachedSaveData->SavedScore` is copied into `TotalScore`. Otherwise, a new SaveGame object is created.
4. When the player collects a coin, the existing character/pickup system calls `AddScore(amount)`.
5. For positive amounts, `AddScore()` updates `TotalScore` and calls `SavePlayerData()`.
6. `SavePlayerData()` copies `TotalScore` into `CachedSaveData->SavedScore` and writes the object using `UGameplayStatics::SaveGameToSlot()`.

**Runtime versus disk:** `GameInstance` keeps score across level transitions during a play session. `SaveGameToSlot()` persists that score across separate play sessions; `LoadGameFromSlot()` restores it.

## Integration and testing

This exercise builds on an existing coin pickup, character scoring, and level-transition project. The four files in this folder are **not a standalone Unreal project**.

1. Add these C++ classes to an Unreal Engine C++ project and build.
2. In **Project Settings → Maps & Modes**, set **Game Instance Class** to the custom `UMyGameInstance` class (or its Blueprint subclass).
3. Connect your pickup/character scoring logic to `UMyGameInstance::AddScore()`.
4. Play, collect coins, and check the Output Log for a successful save.
5. Stop Play, start a new session, and confirm the previously saved score loads.
6. Collect another coin and confirm the score increases from the loaded total.

## C++ and Unreal concepts practiced

- Inheritance from `UGameInstance` and `USaveGame`
- `UCLASS`, `UPROPERTY`, and `GENERATED_BODY()`
- Forward declarations and header/implementation separation
- UObject pointers, `Cast<>`, and null checks
- Member-variable caching and garbage collection awareness
- `const` getters and private data encapsulation
- Overriding `Init()` and calling `Super::Init()`
- Save slots, serialization, and logging with `UE_LOG`

## Current limitations

- Saves only the score, not coin locations, player position, or other game state.
- Uses one fixed save slot (`PlayerSave`) and user index (`0`).
- Saves synchronously after each positive score change.
- If a saved file exists but cannot be loaded, the fallback creates a fresh in-memory object; a subsequent save may overwrite the previous slot.
- If creating the fallback SaveGame object also fails, saving is skipped and logged.

## What I learned

This exercise helped me understand the difference between data kept in memory and data written to disk, why a cached UObject pointer is useful, and how Unreal's GameInstance and SaveGame classes work together to preserve progress between play sessions.
