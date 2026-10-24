# C++ RPG Inventory System — Arrays and Structs

## Overview

This project is a simple RPG weapon inventory system developed in C++ to practice using `std::array` with custom structs.

The program creates an inventory containing three weapons, displays their starting stats, upgrades a specific weapon's damage, and prints the updated inventory.

## Concepts Practiced

- **Structs:** Creating a custom `Weapon` type containing a name and damage value.
- **std::array:** Storing a fixed number of weapon objects.
- **Aggregate Initialization:** Initializing multiple weapon structs inside an array using braces.
- **Range-Based For Loops:** Iterating through weapon objects to display their stats.
- **Indexed For Loops:** Accessing inventory slots using their indexes.
- **References:** Accessing weapon objects without creating copies.
- **Member Access:** Using the dot operator to read and modify struct members.
- **Modifying Array Elements:** Increasing the damage of an individual weapon.

## How It Works

1. A `Weapon` struct stores each weapon's name and damage.
2. A `std::array<Weapon, 3>` creates an inventory with three fixed slots.
3. The inventory is initialized with an Iron Sword, Battle Axe, and Wooden Bow.
4. A range-based loop displays the starting weapon stats.
5. The Battle Axe's damage is increased by 10 using its array index.
6. An indexed loop displays each inventory slot and its updated weapon stats.

## Example Output

```text
Starting inventory:
Iron Sword - 25 damage
Battle Axe - 40 damage
Wooden Bow - 15 damage

Updated inventory
Slot 1: Iron Sword - 25 damage
Slot 2: Battle Axe - 50 damage
Slot 3: Wooden Bow - 15 damage
```

## What I Learned

This exercise helped me understand how `std::array` can store custom objects rather than just integers or other basic data types.

I practiced initializing an array of structs, accessing individual objects, and modifying their members using array indexes.

I also reinforced my understanding of range-based loops, indexed loops, and references.

This project demonstrates a basic fixed-slot inventory system that could be expanded into a larger gameplay inventory system.

## Technologies Used

- C++
- Visual Studio Code
- C++ Standard Library

## Future Improvements

- Add weapon durability and rarity.
- Allow weapons to be equipped or unequipped.
- Create functions to upgrade or repair weapons.
- Add support for empty inventory slots.
