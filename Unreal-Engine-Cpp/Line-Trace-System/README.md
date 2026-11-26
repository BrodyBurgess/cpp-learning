# Directional Line Trace System

## Overview

A real-time directional line tracing system developed in Unreal Engine 5 using C++.

The system continuously detects objects in the actor's forward direction, visualizes collision results, and tracks previously detected actors to prevent repetitive logging.

This project builds upon basic line tracing and introduces reusable functions, directional vectors, collision filtering, and persistent actor tracking.

## Features

- Real-time directional line tracing using Tick().
- Configurable trace distance through a function parameter.
- Dynamic detection based on actor location and rotation.
- Visibility collision channel filtering.
- Self-collision prevention.
- Actor and impact point retrieval.
- Color-coded debug visualization.
- Duplicate log prevention using actor pointer comparisons.
- Target tracking and reset functionality.

## How It Works

1. Retrieve the actor's current world location.
2. Calculate the trace endpoint using its forward vector and trace distance.
3. Configure collision query parameters to ignore the tracing actor.
4. Perform a single line trace using the Visibility collision channel.
5. Retrieve the detected actor and collision impact point.
6. Draw a green debug line when a blocking collision occurs.
7. Log the detected actor only when the target changes.
8. Draw a red debug line and reset the previous target when no collision occurs.

## Debug Visualization

| Color | Meaning |
|-------|---------|
| Green | Blocking collision detected |
| Red | No blocking collision detected |

The debug line updates every frame as the actor moves or rotates.

## C++ Concepts Practiced

- Pointers and nullptr
- Pointer comparisons
- Function parameters
- Reusable functions
- Conditional statements
- Const variables
- Member and local variables
- Actor state tracking

## Unreal Engine Concepts Practiced

- Actor lifecycle functions
- Tick-based gameplay logic
- FVector calculations
- GetActorLocation()
- GetActorForwardVector()
- LineTraceSingleByChannel()
- FCollisionQueryParams
- FHitResult
- Collision channels
- DrawDebugLine()
- UE_LOG()

## Testing

1. Create a Blueprint derived from DirectionalTracePractice.
2. Add a visible mesh to represent the tracing actor.
3. Place the actor in the level.
4. Place objects with query collision enabled that block Visibility nearby.
5. Start the game and eject from the player character.
6. Rotate or move the tracing actor toward different objects.
7. Observe the debug line and Output Log.

## Gameplay Applications

This system provides a foundation for:

- Hitscan combat systems
- Laser detection systems
- Enemy line-of-sight detection
- Player interaction systems
- Target detection
- Environmental obstacle detection

## Technologies

- Unreal Engine 5
- C++
- Visual Studio

## Future Improvements

- Custom collision channels
- Sphere and capsule tracing
- Player-controlled interaction
- Damage application
- Weak object pointers for safer target tracking
- Configurable editor properties

## Purpose

This project is part of an ongoing gameplay programming portfolio focused on developing practical C++ skills and reusable gameplay systems within Unreal Engine.
