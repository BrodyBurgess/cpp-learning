#include <iostream>
#include <string>
#include <vector>

struct Armor
{
    std::string name;
    int defense;
    int durability;

    Armor(std::string customName, int customDefense, int customDurability)
        : name(customName), defense(customDefense), durability(customDurability)
        {
        }

        void TakeDamage(int amount)
        {
            durability -= amount;
        }

};


 int main()
{
    std::vector<Armor> armors;

    armors.emplace_back("Iron Chestplate", 40, 100);
    armors.emplace_back("Leather Armor", 15, 60);
    
    armors[0].TakeDamage(25);

    for(Armor& armor : armors)
    {
        std::cout << armor.name << "\n";
        std::cout << "Defense: " << armor.defense << "\n";
        std::cout << "Durabaility: " << armor.durability << "\n\n";
    }
    
    return 0;
}

