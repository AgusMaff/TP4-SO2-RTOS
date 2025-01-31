#include "graph.h"

void vGraphTask(void *pvParameters)
{
    int value;
    int xPos = GRAPH_X_OFFSET + 1;
    OSRAMClear();
    for (;;)
    {
        if (xQueueReceive(xFilteredValueQueue, &value, portMAX_DELAY) == pdPASS)
        {
            char buffer[10];
            prvIntToString(value, buffer);
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

static void prvIntToString(int value, char *buffer)
{
    char temp[10];
    int i = 0, j = 0;
    if (value == 0) {
        buffer[j++] = '0';
        buffer[j] = '\0';
        return;
    }
    if (value < 0) {
        buffer[j++] = '-';
        value = -value;
    }
    while (value > 0) {
        temp[i++] = '0' + (value % 10);
        value /= 10;
    }
    while (i > 0) {
        buffer[j++] = temp[--i];
    }
    buffer[j] = '\0';
}