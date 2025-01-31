/* Environment includes */
#include "DriverLib.h"
#include "../include/graph.h"
#include "../include/sensor.h"
#include "../include/filter.h" 

/* Task priorities */
#define TASK_PRIORITY_GEN      (tskIDLE_PRIORITY + 1)
#define TASK_PRIORITY_FILTER   (tskIDLE_PRIORITY + 2)
#define TASK_PRIORITY_GRAPH    (tskIDLE_PRIORITY + 2)

/* Function prototypes */
static void prvSetupHardware(void);

/* Queue handles for inter-task communication */
QueueHandle_t xSensorValueQueue;
QueueHandle_t xFilteredValueQueue;

/* Function prototypes */
static void prvIntToString(int value, char *buffer);

int main(void)
{
    /* Initialize hardware */
    prvSetupHardware();

    /* Create the queues */
    xSensorValueQueue = xQueueCreate(10, sizeof(int));
    xFilteredValueQueue = xQueueCreate(10, sizeof(int));
    if (xFilteredValueQueue == NULL)
    {
        OSRAMStringDraw("Queue Fail", 0, 0);
        while(1);
    }
    
    /* Create the tasks */
    xTaskCreate(vRandomGenTask, "RandGen", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY_GEN, NULL);
    xTaskCreate(vLowPassFilterTask, "LowPassFilter", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY_FILTER, NULL);
    xTaskCreate(vGraphTask, "Graph", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY_GRAPH, NULL);
    
    /* Start the scheduler */
    vTaskStartScheduler();
    
    return 0;
}

static void prvSetupHardware(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    OSRAMInit(false);
    OSRAMClear();
    OSRAMStringDraw("Starting...", 0, 0);
}
