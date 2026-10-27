#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>

struct Enemy
{
    std::string name;
    int health;

    Enemy(std::string customName, int customHealth)
        : name(customName), health(customHealth)
    {
    }

    void heal(int amount)
    {
        health += amount;
    }
};


 int main()
{
    std::vector<Enemy> enemies;

    enemies.emplace_back("Skeleton", 80);
    enemies.emplace_back("Dragon", 300);
    enemies.emplace_back("Zombie", 120);
    enemies.emplace_back("Goblin", 40);

    enemies[2].heal(30);

    std::sort(enemies.begin(), enemies.end(),
    [](const Enemy& a, const Enemy& b)
    {
        return a.health < b.health;
    });

    for(std::size_t i = 0; i < enemies.size(); i++)
    {
        std::cout << "Priority " << i + 1 << ": " << enemies[i].name << " - " << enemies[i].health << " HP\n";
    }


    return 0;
}
