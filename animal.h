#ifndef ANIMAL
#define ANIMAL

#include <iostream>

class Animal {
    protected:
        int age = 0;
        int offspring_count;
        int food_mult;
        int cost;
        
    public:
        Animal() { };
        void incrementAge();
        int getFoodCost(int);
        int getRev();
        int getCost();


};


#endif