# Exercise 17 — Temporary Speed Boost Pickup (Unreal Engine C++)

## Overview

A placeable **speed boost pickup** built in Unreal Engine C++. When the player overlaps the pickup, their movement speed increases from its current value to **1000 Unreal units/second** for **5 seconds**. A one-shot timer then restores the original speed.

The pickup is consumed **only if the boost successfully activates**. If the player is already boosted, the second pickup remains in the level and can be collected after the first boost expires.

## Features

- Placeable `AActor` with a `USphereComponent` trigger
- `OnComponentBeginOverlap.AddDynamic()` event binding
- Player identification using `Cast<ACppGameplayPracticeCharacter>()`
- Temporary movement-speed change via `GetCharacterMovement()->MaxWalkSpeed`
- Five-second, non-looping `FTimerHandle` timer
- `bool` return value to communicate whether activation succeeded
- Protection against stacking or overwriting an active boost
- Pickup destruction only on successful activation

## Files

| File | Purpose |
| --- | --- |
| `SpeedBoostPickUp.h` | Declares the pickup actor, collision sphere, and overlap callback. |
| `SpeedBoostPickUp.cpp` | Configures the sphere trigger, binds the event, and attempts to activate the boost. |
| `CppGameplayPracticeCharacter.h` | Declares the speed boost functions, timer handle, speed variables, and active-state Boolean. |
| `CppGameplayPracticeCharacter.cpp` | Saves normal speed, applies boosted speed, starts the timer, and restores speed on expiration. |

**Note:** The character files also contain code from earlier exercises (camera, input, health, and scoring). They are included here to show how the boost integrates into the existing character. This exercise depends on the existing `MyGameInstance` and project files; these four files alone are **not a standalone Unreal project**.

## How it works

1. The player enters the pickup's sphere trigger.
2. The overlap callback casts `OtherActor` to the player character.
3. The pickup calls `Player->ActivateSpeedBoost()` **once**.
4. If no boost is active, the character saves `MaxWalkSpeed`, sets it to `1000.0f`, marks the boost active, and schedules `EndSpeedBoost()` after five seconds.
5. The function returns `true`, so the pickup calls `Destroy()`.
6. After five seconds, `EndSpeedBoost()` restores the saved speed and clears the active-state flag.
7. If a boost was already active, `ActivateSpeedBoost()` returns `false`; the new pickup stays in the level.

## Key C++ concepts practiced

- **Pointer and cast:** `Cast<ACppGameplayPracticeCharacter>(OtherActor)` provides access to the player's methods.
- **Delegate binding:** `AddDynamic(this, &ASpeedBoostPickUp::SphereSpeedBoostOverlap)` connects a sphere event to a `UFUNCTION` callback.
- **Timer callback:** `SetTimer(SpeedBoostTimer, this, &ACppGameplayPracticeCharacter::EndSpeedBoost, 5.0f, false)` schedules a one-time callback.
- **Return values:** `return true;` or `return false;` immediately exits the function and lets the pickup decide whether to destroy itself.
- **State tracking:** `bIsSpeedBoostActive` prevents multiple simultaneous activations.

## Setup and testing

1. Add these source files to the existing `CppGameplayPractice` Unreal C++ project (or use them as reference when integrating with your character class).
2. Compile the editor target and open Unreal Engine.
3. Place two `SpeedBoostPickUp` actors in the level.
4. Start Play In Editor and overlap the first pickup. The character should speed up and the first pickup should disappear.
5. While the first boost is active, overlap the second pickup. It should **remain** in the level.
6. After five seconds, verify normal movement speed returns.
7. Leave the second pickup's trigger and re-enter it. It should now activate a fresh boost and disappear.

**Tested in the learning exercise:** The two-pickup behavior worked as intended.

## Implementation notes

- The character's original `BeginPlay()` call to `ActivateSpeedBoost()` was removed from this portfolio version so the boost is triggered by pickups rather than automatically at level start.
- The duplicate `CharacterMovementComponent` include was removed.
- Unused `Tick()` and `BeginPlay()` overrides were removed from the pickup; overlap events handle the mechanic without per-frame polling.
- The sphere's component name spelling was corrected to `"Collision"`.
- `SphereRadius` is a constructor default. Editing it on an actor instance after construction does not automatically resize the collision sphere; change the sphere component's radius directly in the editor or add a synchronization method if needed.

## Possible future improvements

- Expose boost duration and boosted speed as editable properties.
- Add a mesh, particle effect, and pickup sound.
- Display remaining boost time on the HUD.
- Choose whether collecting another pickup refreshes the timer or remains blocked.
