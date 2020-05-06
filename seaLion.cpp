#include "seaLion.h"


SeaLion::SeaLion() {
    //set protected variables
    food_mult = 1;
    offspring_count = 1;
    cost = 800;
    

}


int SeaLion::getRev() {
    return cost * .2;
}
