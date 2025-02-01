#include "filter.h"

void vLowPassFilterTask(void *pvParameters)
{
   int filteredValue, value;
   int sum = 0;

   while(1) {
    if(xQueueReceive(xSensorValueQueue, &value, portMAX_DELAY)==pdPASS) {
        sum = sum - (sum/FILTER_WINDOW_SIZE) + value;
        filteredValue = sum/FILTER_WINDOW_SIZE;
        xQueueSend(xFilteredValueQueue, &filteredValue, portMAX_DELAY);
    }
   }
}