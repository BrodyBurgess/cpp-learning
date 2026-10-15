#include <iostream>

class Enemy
{

    protected:
        int health;
        int damage;

    public:
        Enemy(int startingHealth, int startingDamage)
            : health(startingHealth), damage(startingDamage)
            {
            }
        void TakeDamage(int amount)
        {
            health -= amount;
        }
        int ReadHealth()
        {
            return health;
        }

        virtual void Attack(int* playerHealth) = 0;
};

class Skeleton : public Enemy
{

    public:
        Skeleton(int startingHealth, int startingDamage)
            : Enemy(startingHealth, startingDamage)
            {
            }

        void Attack(int* playerHealth) override
        {
            if(playerHealth != nullptr)
            {
                *playerHealth -= damage;
                std::cout << "Skeleton shoots an arrow for 15 damage!\n";
            }
        }
};

class Zombie : public Enemy
{

    public:
    Zombie(int startingHealth, int startingDamage)
            : Enemy(startingHealth, startingDamage)
            {
            }
    void Attack(int* playerHealth) override
    {
        if(playerHealth != nullptr)
        {
            *playerHealth -= damage;
            std::cout << "Zombie bites for 25 damage!\n";
        }
    }
        
};

class Dragon : public Enemy
{

    public:
    Dragon(int startingHealth, int startingDamage)
            : Enemy(startingHealth, startingDamage)
            {
            }
    void Attack(int* playerHealth) override
    {
        if(playerHealth != nullptr)
        {
            *playerHealth -= damage;
            std::cout << "Dragon breathes fire for 40 damage!\n";
        }
    }
};

void PerformAttack(Enemy& enemy, int* playerHealth)
{
    enemy.Attack(playerHealth);
}

 int main()
{
   int playerHealth = 200;

    Skeleton skeleton(100, 15);
    Zombie zombie(150, 25);
    Dragon dragon(500, 40);


    int* currentPlayerHealth = &playerHealth;

    PerformAttack(skeleton, currentPlayerHealth);

    PerformAttack(zombie, currentPlayerHealth);

    PerformAttack(dragon, currentPlayerHealth);

    skeleton.TakeDamage(30);

    std::cout << "Skeleton Health: " << skeleton.ReadHealth() << "\n";

    std::cout << "Player Health: " << *currentPlayerHealth << "\n";

    return 0;
}
