#include "commons.h"
#include "filter.h"

#define BAUD_RATE 19200
#define BUFFER_SIZE 32

void vUartTask(void *pvParameters);
void vUartSendString(const char* str, int newLine);
int vUartGet(char* buffer, int lenght);
int StringToInt(char *buffer);
void IntToStringUart(int num, char *str);
void vReverseStr(char* str, int length);