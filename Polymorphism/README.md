# Enemy Combat System — Polymorphism

## Overview
A small C++ combat simulation demonstrating runtime polymorphism through different enemy types.

## Features
- Abstract Enemy base class
- Skeleton, Zombie, and Dragon enemy classes
- Unique attack behavior for each enemy type
- Player health and damage calculations
- Enemy health modification

## Concepts Practiced
- Inheritance
- Constructors
- Pure virtual functions
- Function overriding
- Pointers and references
- Runtime polymorphism

## How It Works
Each enemy inherits from the Enemy base class and overrides the Attack() function.

The PerformAttack() function accepts an Enemy reference, allowing different enemy types to execute their own attack implementations.

## What I Learned
This exercise helped me understand how virtual functions allow different objects to respond differently through a shared base class interface.
