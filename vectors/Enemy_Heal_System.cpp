#include <iostream>
#include <vector>

class Enemy
{

    public:
        int health;
        int damage;

        Enemy(int startingHealth, int startingDamage)
            : health(startingHealth), damage(startingDamage)
            {
            }

            void Heal(int amount)
            {
                health += amount;
            }
};


 int main()
{
    std::vector<Enemy> enemy;

    enemy.emplace_back(100, 15);
    enemy.emplace_back(35, 20);
    enemy.emplace_back(80, 10);
    enemy.emplace_back(20, 25);

    for(std::size_t i = 0; i < enemy.size(); i++)
    {
        if(enemy[i].health < 50)
        {
            enemy[i].Heal(25);
        }

        std::cout << "Enemy " << i + 1 << ": " << enemy[i].health << "\n";

    }

    
    return 0;
}
