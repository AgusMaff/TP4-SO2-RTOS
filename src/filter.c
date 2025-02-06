#include "filter.h"

volatile int newFilterValue = 0;

void vLowPassFilterTask(void *pvParameters)
{
    while (newFilterValue == 0) {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    int n = newFilterValue;
    int filteredValue, value;
    int sum = 0;    
    while(1) {   
        if(xQueueReceive(xSensorValueQueue, &value, portMAX_DELAY)==pdPASS) {
            sum = sum - (sum/n) + value;
            filteredValue = sum/n;
            xQueueSend(xFilteredValueQueue, &filteredValue, portMAX_DELAY);
        }
    }
}