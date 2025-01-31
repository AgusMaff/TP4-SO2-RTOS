/* FreeRTOS includes */
#include "../Source/include/FreeRTOS.h"
#include "../Source/include/task.h"
#include "../Source/include/queue.h"

/* Constants for random number generation */
#define TEMP_MIN               12
#define TEMP_MAX               40
#define GENERATION_DELAY_MS    1000

extern QueueHandle_t xFilteredValueQueue;
extern QueueHandle_t xSensorValueQueue;