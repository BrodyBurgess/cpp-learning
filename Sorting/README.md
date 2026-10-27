# C++ Enemy Priority System

## Overview

This project is a simple enemy priority system developed in C++ to practice sorting custom objects using Standard Library algorithms and lambda functions.

The program creates multiple enemies, modifies an enemy's health, and sorts the enemies from lowest to highest health to determine their combat priority.

## Concepts Practiced

- **Structs:** Creating a custom `Enemy` type with name and health members.
- **Constructors:** Initializing enemy objects using a member initializer list.
- **Member Functions:** Implementing a `heal()` function to modify enemy health.
- **std::vector:** Dynamically storing multiple enemy objects.
- **emplace_back():** Constructing enemy objects directly inside a vector.
- **std::sort():** Rearranging enemies based on their health values.
- **Lambda Functions:** Defining a custom comparison for sorting objects.
- **Const References:** Using `const Enemy&` to compare objects without copying or modifying them.
- **Indexed For Loops:** Displaying enemy priority rankings.

## How It Works

1. An `Enemy` struct stores each enemy's name and health.
2. A constructor initializes each enemy's starting values.
3. Four enemies are added to a vector using `emplace_back()`.
4. The Zombie receives 30 additional health through the `heal()` function.
5. `std::sort()` uses a lambda function to compare enemy health values.
6. Enemies are sorted from lowest to highest health.
7. An indexed loop displays each enemy's priority ranking.

## Example Output

```text
Priority 1: Goblin - 40 HP
Priority 2: Skeleton - 80 HP
Priority 3: Zombie - 150 HP
Priority 4: Dragon - 300 HP
```

## What I Learned

This exercise helped me understand how to sort custom objects rather than just integers.

I learned that `std::sort()` can use a lambda function to determine which member variable should control the sorting order.

I also reinforced my understanding of constructors, vectors, member functions, and const references.

This project demonstrates a basic enemy targeting priority system that could be expanded into a larger combat system.

## Technologies Used

- C++
- Visual Studio Code
- C++ Standard Library

## Future Improvements

- Automatically select the enemy with the highest priority as the next target.
- Add enemy damage and attack functions.
- Update enemy priorities after taking damage or receiving healing.
- Add different sorting rules based on distance, damage, or enemy type.
- Integrate the targeting system into an Unreal Engine gameplay project.
