#include <iostream>
#include <string>
#include <array>

struct Weapon
{

    std::string name;
    int damage;
};

 int main()
{
    std::array<Weapon, 3> inventory = {{
        {"Iron Sword", 25},
        {"Battle Axe", 40},
        {"Wooden Bow", 15}

    }};

    std::cout << "Starting inventory:\n";

    for(Weapon& slot : inventory)
    {
        std::cout << slot.name << " - " << slot.damage << " damage\n";
    }

    std::cout << "\n";

    inventory[1].damage += 10;

    std::cout << "Updated inventory\n";
  
    for(std::size_t i = 0; i < inventory.size(); i++)
    {
        std::cout << "Slot " << i + 1 << ": " << inventory[i].name << " - " << inventory[i].damage << " damage\n";
    }

    return 0;
}

