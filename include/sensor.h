#include "commons.h"

static uint32_t ulRandomSeed = 12345;

static int prvGenerateRandomNumber(int min, int max);
void vRandomGenTask(void *pvParameters);