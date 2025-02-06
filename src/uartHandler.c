#include "uartHandler.h"

void vUartTask(void *pvParameters){
    char buffer [BUFFER_SIZE];
    int result;

    while(1){
        result = vUartGet(buffer, BUFFER_SIZE);

        if (result == -1) {
            vUartSendString("\nCommand longer than buffer size\n", 0);
        } else if (result == 1) {
            int newValue = StringToInt(buffer);
            if(newValue > 0) {
                newFilterValue = newValue;
                vUartSendString("\nFilter length set in: ", 0);
                IntToStringUart(newFilterValue, buffer);
                vUartSendString(buffer, 1);
            }
            else
            {
                newFilterValue = 10;
                vUartSendString("\nFilter length set as default: ", 0);
                IntToStringUart(newFilterValue, buffer);
                vUartSendString(buffer, 1);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

int vUartGet(char* buffer, int length) {
    int i = 0;

    while (i < length && UARTCharsAvail(UART0_BASE))
        buffer[i++] = UARTCharGet(UART0_BASE);

    buffer[i] = '\0';

    return i > 0 ? (i > length ? -1 : 1) : 0;
}

void vUartSendString(const char* str, int newLine) {
    while (*str != '\0') 
    {
        UARTCharPut(UART0_BASE, *str);
        str++;
    }

    if (newLine)
        UARTCharPut(UART0_BASE, '\n');
}

int StringToInt(char *buffer)
{
    int value = 0;
    while (*buffer) {
        if (*buffer < '0' || *buffer > '9')
            return -1;
        value = value * 10 + (*buffer - '0');
        ++buffer;
    }
    return value;
}

void IntToStringUart(int num, char *str)
{
    int i = 0, isNegative = 0;

    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    if (num == 0)
        str[i++] = '0';
    else {
        while (num) {
            str[i++] = num % 10 + '0';
            num = num / 10;
        }
    }

    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';
    vReverseStr(str, i);
}


void vReverseStr(char* str, int length) 
{
    int start = 0;
    int end = length - 1;

    while (start < end) 
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}