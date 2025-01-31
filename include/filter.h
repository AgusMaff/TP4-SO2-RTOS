#include "commons.h"
/* Filter configuration */
#define FILTER_WINDOW_SIZE     30 /* Number of samples for low-pass filter */

extern QueueHandle_t xFilteredValueQueue;
extern QueueHandle_t xSensorValueQueue;

void vLowPassFilterTask(void *pvParameters);