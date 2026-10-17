# Smart Pointers and Polymorphism in C++

## Overview

This project demonstrates how to use `std::unique_ptr` to manage dynamically allocated objects in C++.

The program creates a Goblin enemy and later replaces it with a Dragon using the same smart pointer. Memory is managed automatically without manually calling `delete`.

## Concepts Practiced

- Smart pointers using `std::unique_ptr`
- Creating objects with `std::make_unique`
- Inheritance with base and derived classes
- Polymorphism using virtual functions
- Pure virtual functions and abstract classes
- Function overriding with `override`
- Virtual destructors
- Automatic memory management and object lifetimes

## How It Works

1. An abstract `Enemy` base class defines a virtual `Attack()` function and a virtual destructor.
2. The `Goblin` and `Dragon` classes inherit from `Enemy` and implement their own attack behaviors.
3. A `std::unique_ptr<Enemy>` initially owns a Goblin.
4. The Goblin attacks before being replaced by a Dragon.
5. Reassigning the smart pointer automatically destroys the Goblin.
6. The Dragon attacks and is automatically destroyed when the program ends.

## What I Learned

This exercise helped me understand how smart pointers manage memory and how polymorphism allows a base-class pointer to work with different derived classes.

I also learned that `std::unique_ptr` provides exclusive ownership, that assigning a newly created object replaces the previously owned object, and that virtual destructors are important when managing derived objects through base-class pointers.

## Technologies

- C++
- C++14 or later
- Visual Studio Code
