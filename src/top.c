#include "top.h"
#include "uartHandler.h"

void vTopTask(void *pvParameters) {
    TaskStatus_t* taskStatusArray;
    uint32_t totalRunTime;
    UBaseType_t taskCount;
    char buffer[12];

    // Obtener el número inicial de tareas
    UBaseType_t uxArraySize = uxTaskGetNumberOfTasks();
    taskStatusArray = pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));

    while (1) {
        // Obtener el estado del sistema y el tiempo total de ejecución
        taskCount = uxTaskGetSystemState(taskStatusArray, uxArraySize, &totalRunTime);

        for (UBaseType_t i = 0; i < taskCount; i++) {
            if (taskStatusArray[i].pcTaskName == NULL || taskStatusArray[i].pcTaskName[0] == '\0') {
                continue;
            }
            
            vUartSendString("\r\nTask Name:\t", 0);
            vUartSendString(taskStatusArray[i].pcTaskName, 0);

            vUartSendString("\r\nStack Free:\t", 0);
            IntToStringUart(taskStatusArray[i].usStackHighWaterMark, buffer);
            vUartSendString(buffer, 0);
            vUartSendString(" words\t", 0);

            if (totalRunTime == 0) {
                vUartSendString("\r\nCPU Usage:\t", 0);
                vUartSendString("Warning: totalRunTime is 0. CPU usage may be incorrect.\r\n", 0);
            } else { 
                uint8_t cpuUsage = (taskStatusArray[i].ulRunTimeCounter * 100 / totalRunTime);
                IntToStringUart(cpuUsage, buffer);
                vUartSendString("\r\nCPU Usage:\t", 0);
                vUartSendString(buffer, 0);
                vUartSendString("%", 0);
            }

            vUartSendString("\r\nTime:\t", 0);
            IntToStringUart(taskStatusArray[i].ulRunTimeCounter, buffer);
            vUartSendString(buffer, 0);
            vUartSendString("\r\n-----------------------------------------------\r\n", 0);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
