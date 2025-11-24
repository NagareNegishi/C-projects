#ifndef OVEN_H
#define OVEN_H

#include "food.h"

// Assuming oven is hardware expensive to test
// it takes power and produces heat
const float MAX_TEMPERATURE = 250.0;
float temperature;

void oven_on();
void oven_off();
float get_temperature();
void set_timer(int minutes);
void bake(FoodItem* item, int minutes);



#endif // OVEN_H