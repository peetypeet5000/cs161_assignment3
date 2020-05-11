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
    done = checkLoss();
    } while(done == false);
}


void Zoo::getSpecialEvent() {
    high_attendance = false;   //resets so only for 1 turn


    int random_event = (rand() % 4);    //rand 0-3
    switch(random_event) {
        case 0:
            makeSick();
            break;
        case 1:
            checkBirth();
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
    food_base = food_base * (rand_mult/100);
}


void Zoo::loopAnimalsRev() {
    for(int i  = 0; i < num_sealions; i++) {
        bank = bank + sea_lions[i].getRev(high_attendance);
        sea_lions[i].incrementAge();
    }
    for(int i  = 0; i < num_tigers; i++) {
        bank = bank + tigers[i].getRev();
        tigers[i].incrementAge();
    }
    for(int i  = 0; i < num_blackbears; i++) {
        bank = bank + black_bears[i].getRev();
        black_bears[i].incrementAge();
    }
}


void Zoo::checkBirth() {
    int counter = 0;
    if((num_sealions + num_tigers + num_blackbears) > 0) {
        for(int i  = 0; i < num_sealions; i++) {
            if(sea_lions[i].getAge() >= 48) {
                counter++;
            }
        }
        for(int i  = 0; i < num_tigers; i++) {
            if(tigers[i].getAge() >= 48) {
                counter++;
            }
        }
        for(int i  = 0; i < num_blackbears; i++) {
            if(black_bears[i].getAge() >=48) {
                counter++;
            }
        }
    }
    if(counter > 0) {
        giveBirth(); //only calls if there is a valid animal
        //otherwise it could get stuck in an infinite loop
    }
}



void Zoo::giveBirth() {
    int selection = 0, animal_type = rand() % 3, done = 0;
    if(animal_type == 2) {
        if(num_sealions > 0) {
            selection = (rand() % num_sealions);    //gets random animal
            if(sea_lions[selection].getAge() >= 48) {
                addAnimal(2, 1, 0); //makes babies
                done = 1;
            }
        } 
   } else if(animal_type == 1) {
        if(num_tigers > 0) {
            selection = (rand() % num_tigers);
            if(tigers[selection].getAge() >= 48) {
                addAnimal(1, 3, 0);
                done = 1;
            } 
        }
   } else {
        if(num_blackbears > 0) {
            selection = (rand() % num_blackbears);
            if(black_bears[selection].getAge() >= 48) {
                addAnimal(0, 2, 0);
                done = 1;
            }
        } 
    }
    if(done == 0) {
        giveBirth(); //calls again if couldnt find one
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



void Zoo::makeSick() {
    if(num_tigers + num_blackbears + num_sealions > 0) {
        int choice = (rand() % 3);
        if(choice == 2) {
            if(num_sealions > 0) {
                int animal_num = (rand() % num_sealions);
                sickAnimal(choice, animal_num, sea_lions[animal_num].getAge());
            } else {
                makeSick(); //call again untill it works
            }
        } else if(choice == 1) {
            if(num_tigers > 0) {
                int animal_num = (rand() % num_tigers);
                sickAnimal(choice, animal_num, tigers[animal_num].getAge());
            } else {
                makeSick(); //call again untill it works
            }
        } else {
            if(num_blackbears > 0) {
                int animal_num = (rand() % num_blackbears);
                sickAnimal(choice, animal_num, black_bears[animal_num].getAge());
            } else {
                makeSick(); //call again untill it works
            }
        }

    } else {
        std::cout << "One of your animals would have gotten sick, but you have no animals\n";
    }
}



void Zoo::sickAnimal(int type, int num, int age) {
    int cost_to_heal = 0;
    //calculates cost to heal
    if(type == 2)
        cost_to_heal = 400;
    else if(type == 1)
        cost_to_heal = 7500;
    else
        cost_to_heal = 3000;

    if(age <= 6) {
        cost_to_heal = cost_to_heal * 2; //double sickness cost for baby
    }
    
    if(bank > cost_to_heal) {
        std::cout << "One of your " << getFancyType(type) << "s got sick, but it recovered. This cost $" << cost_to_heal << std::endl << std::endl;
        bank = bank - cost_to_heal;
    } else {
        removeAnimal(type, num); //kills animal if they could not afford
    }
}



void Zoo::removeAnimal(int type, int num) {
    int counter = 0;
    std::cout << "Sadly, one of your " << getFancyType(type) << "s has passed away...\n\n";
    if(type == 2) {
        num_sealions--; //new array with one less
        SeaLion* sea_lions_temp = new SeaLion[num_sealions];
        for(int i = 0; i < num_sealions + 1; i++) { //copy all but new one
            if(i == num) {
                 continue;   //skip the one to be deleted
            }
            sea_lions_temp[counter] = sea_lions[i];
        }
        delete [] sea_lions;
        sea_lions = sea_lions_temp; //new array overights old
    }
    else if(type == 1) {
        num_tigers--; //make new array, copy in
        Tiger* tigers_temp = new Tiger[num_tigers];
        for(int i = 0; i < num_tigers + 1; i++) { //copy all but new one
            if(i == num) {
                continue;
            }
            tigers_temp[counter] = tigers[i];
        }
        delete [] tigers;
        tigers = tigers_temp; //new array overights old
    }
    else {
        num_blackbears--; //make new array, copy in
        BlackBear* blackbears_temp = new BlackBear[num_blackbears];
        for(int i = 0; i < num_blackbears + 1; i++) { //copy all but new one
            if(i == num) {
                continue;
            }
            blackbears_temp[counter] = black_bears[i];
        }
        delete [] black_bears;
        black_bears = blackbears_temp; //new array overights old
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

        addAnimal(choice, amount, 48);
    }
}


void Zoo::addAnimal(int choice, int amount, int age) {
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
            sea_lions_temp[num_sealions - 1].setAge(48);
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
            tigers_temp[num_tigers - 1].setAge(48);
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
            blackbears_temp[num_blackbears - 1].setAge(48);
            black_bears = blackbears_temp; //new array overights old
        }
    }

}


void Zoo::printInfo() {
    months++;
    std::cout << "============= END OF MONTH " << months << " =============";
    std::cout << "\n\nCurrent Animals: \n\n";
    std::cout << "Number of Sea Lions: " << num_sealions << std::endl;
    for(int i = 0; i < num_sealions; i++) {
        std::cout << "  Sea Lion " << (i + 1) << " age: " << sea_lions[i].getAge();
    }
    std::cout << "\n\nNumber of Tigers: " << num_tigers << std::endl;
    for(int i = 0; i < num_tigers; i++) {
        std::cout << "  Tiger " << (i + 1) << " age: " << tigers[i].getAge();
    }
    std::cout << "\n\nNumber of Black Bears: " << num_blackbears << std::endl;
    for(int i = 0; i < num_blackbears; i++) {
        std::cout << "  Black Bear " << (i + 1) << " age: " << black_bears[i].getAge();
    }
    std::cout << "\n\nCurrent Zoo Status:\nBank Balance: " << bank << std::endl;
    std::cout << "Months Elapsed: " << months << std::endl;
    std::cout << "Food Base: " << food_base << std::endl;
    std::cout << "High Attendance?: " << high_attendance << std::endl;
    std::cout << "Food Type: " << food_type << std::endl;
    std::cout << "===================================================\n\n";

}



bool Zoo::checkLoss() {
    if(bank <= 0) {
        std::cout << "You lost the game!\n\n";
        return true;
    } else {
        return false;
    }
}