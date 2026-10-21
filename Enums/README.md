# C++ Enemy Combat State System — Enums

## Overview

This project is a simple enemy combat system written in C++ to practice using enums with classes and gameplay logic.

The program uses an `enum class` to represent different enemy states and determines whether an enemy can damage the player based on its current state.

## Concepts Practiced

- **Enum Classes:** Defining named enemy states using `enum class`.
- **Classes and Constructors:** Creating an enemy with a starting state and damage value.
- **Member Initializer Lists:** Initializing enemy attributes through a constructor.
- **Member Functions:** Changing enemy states and performing attacks.
- **Switch Statements:** Checking enemy states and displaying their corresponding messages.
- **Conditional Statements:** Allowing attacks only when the enemy is in the `Attacking` state.
- **References:** Using `int&` to modify the player's original health value.

## How It Works

1. An `EnemyState` enum defines three possible states: `Idle`, `Attacking`, and `Dead`.
2. An `Enemy` class stores the enemy's current state and attack damage.
3. The constructor initializes the enemy with its starting state and damage.
4. `ChangeState()` allows the enemy to transition between states.
5. `PrintState()` uses a switch statement to display the enemy's current state.
6. `Attack()` checks whether the enemy is in the `Attacking` state before damaging the player.
7. The program tests attacking while idle, attacking, and dead.

## Example Output

```text
Player health: 100
Player health: 80
Player health: 80
```

## What I Learned

This exercise helped me understand how enums can represent different states in a gameplay system.

I practiced combining enums with classes, constructors, and member functions to control enemy behavior.

I also reinforced my understanding of references by modifying the player's health directly through a function.

This project demonstrates a basic concept used in gameplay programming, where an object's current state determines which actions it is allowed to perform.

## Technologies Used

- C++
- Visual Studio Code
- C++ Standard Library

## Future Improvements

- Add enemy health and damage-taking mechanics.
- Automatically change the enemy's state to `Dead` when its health reaches zero.
- Add more AI states, such as `Chasing` and `Stunned`.
- Expand the system into a more complete enemy state machine.
