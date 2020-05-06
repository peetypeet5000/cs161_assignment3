#include "animal.h"



void Animal::incrementAge() {
    age++;
}


int Animal::getFoodCost(int base) {
    return base * food_mult;
}


int Animal::getRev() {
    return cost * .1;
}


