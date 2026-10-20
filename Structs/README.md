# C++ Armor System — Structs and Constructors

## Overview

This project is a simple RPG armor system created in C++ to practice working with structs, constructors, member functions, and vectors.

The program creates multiple armor objects with different stats, stores them in a vector, and allows individual armor pieces to take durability damage.

## Concepts Practiced

- **Structs:** Grouping related variables and functions into a single data type.
- **Constructors:** Initializing armor objects with custom values.
- **Member Initializer Lists:** Initializing struct members directly through a constructor.
- **Member Functions:** Using `TakeDamage()` to modify an armor object's durability.
- **std::vector:** Storing multiple armor objects in one container.
- **emplace_back():** Creating new armor objects directly inside a vector.
- **Range-Based For Loops:** Iterating through armor objects to display their stats.
- **References:** Using `Armor&` to access objects without copying them.

## How It Works

1. An `Armor` struct is created with three attributes: `name`, `defense`, and `durability`.
2. A constructor initializes each armor object's attributes using a member initializer list.
3. Two armor objects, Iron Chestplate and Leather Armor, are created and stored in a vector.
4. The `TakeDamage()` member function reduces the Iron Chestplate's durability by 25.
5. A range-based for loop displays each armor object's name, defense, and remaining durability.

## Example Output

```text
Iron Chestplate
Defense: 40
Durability: 75

Leather Armor
Defense: 15
Durability: 60
```

## What I Learned

Through this exercise, I practiced using structs to organize related gameplay data and constructors to initialize objects with different values.

I also learned how to store multiple struct objects inside a vector, access individual objects using indexes, and modify their data through member functions.

This exercise helped reinforce the similarities between structs and classes and how these concepts can be applied to gameplay programming.

## Technologies Used

- C++
- Visual Studio Code
- C++ Standard Library
