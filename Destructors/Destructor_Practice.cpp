#include <iostream>

class Enemy
{

    public:
        Enemy()
        {
            std::cout << "Enemy constructed!\n";
        }

        virtual ~Enemy()
        {
            std::cout << "Enemy destroyed!\n";
        }
};

class Skeleton : public Enemy
{

    public:
        Skeleton()
        {
            std::cout << "Skeleton constructed!\n";
        }

        ~Skeleton() override
        {
            std::cout << "Skeleton destroyed!\n";
        }
};


 int main()
{
    Enemy* skeleton = new Skeleton();

    std::cout << "Game Running!\n";

    delete skeleton;
    skeleton = nullptr;
    
    return 0;
}
