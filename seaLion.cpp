#include "seaLion.h"


SeaLion::SeaLion() {
    //set protected variables
    food_mult = 1;
    offspring_count = 1;
    cost = 800;
    

}


int SeaLion::getRev(bool high_attendance) {
    int extra = 0;
    if(high_attendance == true) {
        std::cout << "Thanks to the high attendance, your sea lion generated: ";
        extra = (rand() % 250) + 150;
        std::cout << ((rand() % 250) + 150) << std::endl;
    }
    return cost * .2 + extra;
}
