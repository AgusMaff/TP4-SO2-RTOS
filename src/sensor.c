#include "sensor.h"

float generateRandNumbers(){
    srand48(time(NULL));
    float temp;
    temp = drand48() * (MAX_TEMP - 0.0);
    return temp;
}