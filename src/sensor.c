#include "sensor.h"

static int prvGenerateRandomNumber(int min, int max)
{
    ulRandomSeed = (ulRandomSeed * 1664525U + 1013904223U);
    return (ulRandomSeed % (max - min + 1)) + min;
}

void vRandomGenTask(void *pvParameters)
{
    int randomNumber;
    for(;;)
    {
        randomNumber = prvGenerateRandomNumber(TEMP_MIN, TEMP_MAX);
        xQueueSend(xSensorValueQueue, &randomNumber, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(GENERATION_DELAY_MS));
    }
}