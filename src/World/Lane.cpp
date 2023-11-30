#include "../../include/World/Lane.h"

Lane::Lane() {
    //random 2 -> 5 lane
    //numOfLane = 2 + rand() % 3;
    reverse = rand() % 2;
}

bool Lane::isReverse() {
    return reverse;
}