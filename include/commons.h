#include "../Source/include/FreeRTOS.h"
#include "../Source/include/task.h"
#include "../Source/include/queue.h"
#include "../hw_include/hw_ints.h"
#include "../hw_include/hw_memmap.h"
#include "../Source/portable/GCC/ARM_CM3/portmacro.h"
#include <stdlib.h>

#define TEMP_MIN               12
#define TEMP_MAX               40
#define GENERATION_DELAY_MS    1000

extern QueueHandle_t xFilteredValueQueue;
extern QueueHandle_t xSensorValueQueue;