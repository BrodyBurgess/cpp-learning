# C++ Enemy Health Management — Vectors and Loops

## Overview

This project demonstrates how to use `std::vector` to manage multiple enemy objects in C++.

The program creates four enemies with different health and damage values. It then loops through the enemies, checks their health, and automatically heals any enemy with less than 50 health.

## Concepts Practiced

- Classes and constructors
- Storing objects using `std::vector`
- Adding objects with `emplace_back()`
- Indexed `for` loops
- Accessing objects through vector indexes
- Conditional statements
- Calling class member functions
- Modifying object data

## How It Works

1. An `Enemy` class stores health and damage values.
2. The class includes a `Heal()` function that restores 25 health.
3. Four Enemy objects are created and stored in a vector.
4. An indexed `for` loop checks each enemy's health.
5. Enemies with less than 50 health are healed.
6. The program displays each enemy's number and final health.

## What I Learned

This exercise helped me understand how vectors can store multiple objects from a class and how indexed loops can access and modify those objects.

I also practiced using conditional statements inside loops and calling member functions on individual objects.

## Technologies

- C++
- C++11 or later
- Visual Studio Code
