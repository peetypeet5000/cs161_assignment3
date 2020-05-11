#include "animal.h"

Animal::Animal() {
    age = 48;
}

void Animal::incrementAge() {
    age++;
}


int Animal::getFoodCost(int base) {
    return base * food_mult;
}


int Animal::getRev() {
    if(age <= 6) {
        std::cout << "BabyBonus!!";
        return (cost * .1) * 2;
    } else {
        return cost * .1;
    }
}


int Animal::getAge() {
    return age;
}


void Animal::setAge(int age) {
    this->age = age;
}
