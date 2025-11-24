#ifndef FOOD_H
#define FOOD_H

typedef struct {
    const char* name;
    float temperature;
    float moisture;
    float temp_coeff;
    float moist_coeff;
} FoodItem;

void process_food(FoodItem* item, float heat);
#endif // FOOD_H