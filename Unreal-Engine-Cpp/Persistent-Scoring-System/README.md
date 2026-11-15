# Persistent Scoring System — Unreal Engine C++

## Overview

This project demonstrates a persistent scoring system developed in Unreal Engine 5 using C++. The system allows players to collect coins, accumulate points, and retain their total score when transitioning between levels.

The project focuses on gameplay programming fundamentals, including collision detection, object-oriented programming, encapsulation, pointer caching, and communication between Unreal Engine classes.

## Features

- Collectible coins with customizable point values.
- Sphere collision components for detecting player overlaps.
- Automatic coin destruction after collection.
- Persistent score storage using a custom GameInstance.
- Level transitions triggered by player overlaps.
- Configurable collision radii and destination levels through the Unreal Editor.
- Cached GameInstance pointer to avoid repeated casting.
- Private score variables accessed through public getter and modifier functions.
- Debug logging to track score changes and verify gameplay behavior.

## Technologies

- Unreal Engine 5.8
- C++
- Visual Studio
- Unreal Engine Blueprint integration

## System Architecture

The system is divided into four main C++ classes, each responsible for a specific part of the gameplay.

### Coin Pickup — AACoinPickupPractice

The coin pickup actor uses a sphere collision component to detect when the player enters its collection radius.

When a valid player overlaps the sphere, the coin passes its point value to the character's AddScore function, logs the updated total score, and destroys itself.

Each coin can have a different point value and detection radius, allowing designers to customize individual pickups directly in the Unreal Editor.

### Player Character — ACppGameplayPracticeCharacter

The player character acts as the communication layer between collectible actors and the GameInstance.

During BeginPlay, the character retrieves and caches a pointer to the custom GameInstance. This allows the character to reuse the same pointer instead of repeatedly casting whenever the score needs to be accessed.

The character exposes two public scoring functions:

- AddScore(int32 Amount): Passes the requested score increase to the GameInstance.
- GetTotalScore() const: Retrieves the current total score without modifying the character's state.

Null-pointer checks are used before accessing the cached GameInstance.

### GameInstance — UMyGameInstance

The custom GameInstance is responsible for storing and managing the player's total score.

The score is stored as a private variable to prevent other classes from modifying it directly. Public functions provide controlled access to the score.

Because the GameInstance remains active during level transitions, the player's accumulated score is retained when a new level is loaded.

### Level Transition Trigger — ALevelTransitionTrigger

The level transition actor uses a sphere collision component to detect player overlaps.

When the player enters the trigger, the actor loads the configured destination level using UGameplayStatics::OpenLevel().

The destination level and detection radius are editable in the Unreal Editor, making the trigger reusable across different levels.

## Gameplay Flow

1. The player overlaps a coin's collision sphere.
2. The coin verifies that the overlapping actor is the player character.
3. The coin calls the character's AddScore function.
4. The character forwards the score increase to the cached GameInstance.
5. The GameInstance updates its stored total score.
6. The updated score is printed to the Output Log.
7. The coin destroys itself.
8. The player enters a level transition trigger.
9. The next level loads while the GameInstance retains the accumulated score.
10. Additional coins continue increasing the existing score.

## Example

The player collects coins worth 5, 15, and 50 points in the first level, resulting in a total score of 70.

After transitioning to the second level, the player collects three additional coins worth 10 points each.

The Output Log displays:

```text
Player total score is 80
Coin collected!

Player total score is 90
Coin collected!

Player total score is 100
Coin collected!
```

This demonstrates that the player's score persists across level transitions.

## Project Setup

1. Create an Unreal Engine C++ Third Person project.
2. Add the custom C++ classes to the project.
3. Compile the project using Visual Studio.
4. Open Project Settings and navigate to Maps & Modes.
5. Set the Game Instance Class to MyGameInstance.
6. Create two playable levels.
7. Place coin pickup actors throughout both levels.
8. Configure each coin's point value and detection radius.
9. Place a LevelTransitionTrigger actor in the first level.
10. Set its LevelToLoad property to the destination level's name.
11. Play the game and collect coins before and after transitioning between levels.
12. Verify that the total score continues increasing in the Output Log.

## Concepts Practiced

- C++ classes and inheritance
- Object pointers and pointer caching
- Forward declarations
- Public, private, and protected access specifiers
- Encapsulation
- Const member functions
- Unreal Engine reflection macros
- UPROPERTY and UFUNCTION
- Dynamic overlap delegates
- Sphere collision components
- Actor lifecycle and destruction
- GameInstance lifecycle
- Level loading
- Communication between gameplay classes

## Future Improvements

- Display the current score through a UMG user interface.
- Implement a SaveGame system to retain the score after closing the application.
- Add collectible meshes, sounds, and visual effects.
- Implement score-based level unlocking.
- Expand
