#ifndef ZOO
#define ZOO

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "animal.h"
#include "seaLion.h"
#include "bear.h"
#include "tiger.h"
#include "util.h"

class Zoo {
    private:
        SeaLion* sea_lions;
        int num_sealions = 0;
        BlackBear* black_bears;
        int num_blackbears = 0;
        Tiger* tigers;
        int num_tigers = 0;
        int months = 0;
        bool high_attendance = false;
        int food_type = 1;
        long int bank = 100000;
        int food_base = 80;

        
    public:
        Zoo();
        void doTurn();
        void getSpecialEvent();
        void getFoodBase();
        void checkBirth();
        void giveBirth();
        void loopAnimalsRev();
        void loopAnimalsCost();
        void makeSick();
        void sickAnimal(int, int, int);
        void removeAnimal(int, int);
        void buyAnimals();
        void addAnimal(int, int, int);
        void printInfo();
        int getTotalAnimals();
        bool checkLoss();

};


#endif