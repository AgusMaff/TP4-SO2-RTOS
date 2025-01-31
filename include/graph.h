#include "commons.h"

/* Graph configuration */
#define LCD_WIDTH              64      
#define LCD_HEIGHT             16       
#define GRAPH_X_OFFSET         20   

static void prvIntToString(int value, char *buffer);
void vGraphTask(void *pvParameters);