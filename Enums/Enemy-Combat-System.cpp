#include <iostream>


enum class EnemyState
{
    Idle,
    Attacking,
    Dead
};

class Enemy
{

    public:

        int damage;
    
        EnemyState currrentState;

        Enemy(EnemyState startingState, int customDamage)
            :   currrentState(startingState), damage(customDamage)
            {
            }

            void ChangeState(EnemyState changeState)
            {
                currrentState = changeState;
            }

            void PrintState()
            {
                switch(currrentState)
                {
                    case EnemyState::Idle:
                        std::cout << "Enemy is idle\n";
                        break;
                    
                    case EnemyState::Attacking:
                        std::cout << "Enemy is attacking\n";
                        break;

                    case EnemyState::Dead:
                        std::cout << "Enemy is dead\n";
                        break;
                    
                }
            }

            void Attack(int& playerHealth)
            {
                if(currrentState == EnemyState::Attacking)
                {
                    playerHealth -= damage;
                }
                
            }

};


 int main()
{
    int playerHealth = 100;

    Enemy enemy(EnemyState::Idle, 20);

    enemy.Attack(playerHealth);

    std::cout << "Player health: " << playerHealth << "\n";

    enemy.ChangeState(EnemyState::Attacking);

    enemy.Attack(playerHealth);

    std::cout << "Player health: " << playerHealth << "\n";

    enemy.ChangeState(EnemyState::Dead);

    enemy.Attack(playerHealth);

    std::cout << "Player health: " << playerHealth << "\n";


    return 0;
}

