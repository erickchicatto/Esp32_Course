#include <stdio.h>
#include <string.h>
#include "freertos/FreeRtos.h"
#include "freertos/task.h"


void CallingFunk()
{
  char buffer[3000];
  memset(buffer,"x",3000); // fill the buffer with x 
}

void task1(void *parameters)
{
   CallingFunk();
}

void app_main(void)
{
  xTaskCreate(task1,"task1",1024*2,NULL,5,NULL);
}
