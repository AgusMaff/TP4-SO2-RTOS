#include "graph.h"

void vGraphTask(void *pvParameters)
{
    int value;
    int xPos = GRAPH_X_OFFSET + 1;
    OSRAMClear();
    while(1)
    {
        if (xQueueReceive(xFilteredValueQueue, &value, portMAX_DELAY) == pdPASS)
        {
            char buffer[10];
            IntToStringGraph(value, buffer);
            OSRAMStringDraw(buffer, 8, 1);
            OSRAMStringDraw("t", 14, 0);
            unsigned char yAxis[] = {0xFF, 0xFF};
            OSRAMImageDraw(yAxis, 20, 0, 1, 2);
            uint8_t graphData[2] = {0x00, 0x80};
            uint16_t heigth = 1 + (value - TEMP_MIN) * 15 / (TEMP_MAX - TEMP_MIN);
            if (heigth > 7)
            {
                graphData[0] |= 0x01 << (7 - (heigth - 7));
            }
            else
            {
                graphData[1] |= 0x01 << (7 - heigth);
            }
            OSRAMImageDraw(graphData, xPos, 0, 1, 2);
            uint8_t xAxis[2] = {0x00, 0x80};
            for (int i = xPos + 1; i < 96; i++)
            {
                OSRAMImageDraw(xAxis, i, 0, 1, 2);
            }
            xPos = (xPos < 96) ? xPos + 1 : GRAPH_X_OFFSET + 1;
        }
    }
}

void IntToStringGraph(int num, char *str)
{
    int i = 0;

    if (num == 0)
        str[i++] = '0';
    else
    {
        while (num) 
        {
            str[i++] = num % 10 + '0';
            num = num / 10;
        }
    }

    str[i] = '\0';

    vReverseStr(str, i);
}