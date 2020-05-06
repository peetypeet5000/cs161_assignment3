#include "zoo.h"

Zoo::Zoo() {
    doTurn();
    srand(time(NULL));
}

void Zoo::doTurn() {
    bool done = false;
    do {
    getSpecialEvent();
    getFoodBase();
    loopAnimalsRev();
    buyAnimals();
    loopAnimalsCost();
    printInfo();
    } while(done == false);
}


void Zoo::getSpecialEvent() {
    high_attendance = false;   //resets so only for 1 turn


    int random_event = (rand() % 4);    //rand 0-3
    switch(random_event) {
        case 0:
            //makeSick();
            break;
        case 1:
            //giveBirth();
            break;
        case 2:
            high_attendance = true;
            break;
        case 3:
            break; //do nothing
    }
}


void Zoo::getFoodBase() {
    float rand_mult = ((rand() % 46) + 80);  //rand 8-12
    //makes deimal .8 - 1.2
    std::cout << "food mult" << (rand_mult/100);
    food_base = food_base * (rand_mult/100);
}


void Zoo::loopAnimalsRev() {
    for(int i  = 0; i < num_sealions; i++) {
        bank = bank + sea_lions[i].getRev();
    }
    for(int i  = 0; i < num_tigers; i++) {
        bank = bank + tigers[i].getRev();
    }
    for(int i  = 0; i < num_blackbears; i++) {
        bank = bank + black_bears[i].getRev();
    }
}



void Zoo::loopAnimalsCost() {
    for(int i  = 0; i < num_sealions; i++) {
        bank = bank - sea_lions[i].getFoodCost(food_base);
        //std::cout << sea_lions[i].getFoodCost(food_base);
    }
    for(int i  = 0; i < num_tigers; i++) {
        bank = bank - tigers[i].getFoodCost(food_base);
        //std::cout << sea_lions[i].getFoodCost(food_base);
    }
    for(int i  = 0; i < num_blackbears; i++) {
        bank = bank - black_bears[i].getFoodCost(food_base);
        //std::cout << sea_lions[i].getFoodCost(food_base);
    }
}


void Zoo::buyAnimals() {
    int choice, amount;
    std::cout << "Do you want to buy any animals? \n[1] - yes\n[0] - no\n";
    do {
        choice = getInt();
    } while (checkRange(choice, 1, 0) == false);

    if(choice == 1) {
        std::cout << "Which animal?\n[2] - Sea Lions\n[1] - Tigers\n[0] - Bears\n";
        do {
        choice = getInt();
        } while (checkRange(choice, 2, 0) == false);

        std::cout << "How many?\n[1 - 2]\n";;
        do {
        amount = getInt();
        } while (checkRange(amount, 2, 1) == false);

        addAnimal(choice, amount);
    }
}


void Zoo::addAnimal(int choice, int amount) {
    for(int i = 0; i < amount; i++) {
        if(choice == 2) {
            num_sealions++; //make new array, copy in
            SeaLion* sea_lions_temp = new SeaLion[num_sealions];
            if(num_sealions >= 2) {
                for(int i = 0; i < num_sealions - 1; i++) { //copy all but new one
                    sea_lions_temp[i] = sea_lions[i];
                }
                delete [] sea_lions;
            }
            sea_lions = sea_lions_temp; //new array overights old
        }
        else if(choice == 1) {
            num_tigers++; //make new array, copy in
            Tiger* tigers_temp = new Tiger[num_tigers];
            if(num_tigers >= 2) {
                for(int i = 0; i < num_tigers - 1; i++) { //copy all but new one
                    tigers_temp[i] = tigers[i];
                }
                delete [] tigers;
            }
            tigers = tigers_temp; //new array overights old
        }
        else {
            num_blackbears++; //make new array, copy in
            BlackBear* blackbears_temp = new BlackBear[num_blackbears];
            if(num_blackbears >= 2) {
                for(int i = 0; i < num_blackbears - 1; i++) { //copy all but new one
                    blackbears_temp[i] = black_bears[i];
                }
                delete [] black_bears;
            }
            black_bears = blackbears_temp; //new array overights old
        }
    }

}


void Zoo::printInfo() {
    months++;
    std::cout << "\n\nCurrent Zoo Status: \n\n";
    std::cout << "Number of Sea Lions: " << num_sealions << std::endl;
    std::cout << "Number of Tigers: " << num_tigers << std::endl;
    std::cout << "Number of Black Bears: " << num_blackbears << std::endl;
    std::cout << "Bank Balance: " << bank << std::endl;
    std::cout << "Months Elapsed: " << months << std::endl;
    std::cout << "Food Base: " << food_base << std::endl;
    std::cout << "High Attendance?: " << high_attendance << std::endl;
    std::cout << "Food Type: " << food_type << std::endl;

}