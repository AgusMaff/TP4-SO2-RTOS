#include "commons.h"

extern QueueHandle_t xFilteredValueQueue;
extern QueueHandle_t xSensorValueQueue;

extern volatile int newFilterValue;

void vLowPassFilterTask(void *pvParameters);
void IntToString(int num, char *str);