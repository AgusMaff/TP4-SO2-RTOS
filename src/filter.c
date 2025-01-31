#include "filter.h"

void vLowPassFilterTask(void *pvParameters)
{
    int buffer[FILTER_WINDOW_SIZE] = {0};
    int index = 0, sum = 0, value, filteredValue;
    for(;;)
    {
        if (xQueueReceive(xSensorValueQueue, &value, portMAX_DELAY) == pdPASS)
        {
            sum -= buffer[index];
            buffer[index] = value;
            sum += value;
            index = (index + 1) % FILTER_WINDOW_SIZE;
            filteredValue = sum / FILTER_WINDOW_SIZE;
            xQueueSend(xFilteredValueQueue, &filteredValue, portMAX_DELAY);
        }
    }
}