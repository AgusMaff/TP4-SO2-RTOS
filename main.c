/* Environment includes */
#include "DriverLib.h"
#include "../include/graph.h"
#include "../include/sensor.h"
#include "../include/filter.h"
#include "../include/uartHandler.h"
#include "../include/commons.h"
#include "../include/top.h"

static void prvSetupHardware(void);

QueueHandle_t xSensorValueQueue;
QueueHandle_t xFilteredValueQueue;

int main(void)
{
    prvSetupHardware();

    xSensorValueQueue = xQueueCreate(10, sizeof(int));
    xFilteredValueQueue = xQueueCreate(10, sizeof(int));
    if (xFilteredValueQueue == NULL)
    {
        OSRAMStringDraw("Queue Fail", 0, 0);
        while(1);
    }
    
    xTaskCreate(vRandomGenTask, "RandGen", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES, NULL);
    xTaskCreate(vLowPassFilterTask, "LowPassFilter", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES, NULL);
    xTaskCreate(vGraphTask, "Graph", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES, NULL);
    xTaskCreate(vUartTask, "Uart", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
    xTaskCreate(vTopTask, "Top", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES, NULL);
    
    vTaskStartScheduler();
    
    return 0;
}

static void prvSetupHardware(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	UARTConfigSet(UART0_BASE, BAUD_RATE, UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE);
    OSRAMInit(false);
    OSRAMClear();
    OSRAMStringDraw("Starting...", 0, 0);
}




