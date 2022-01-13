#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "freertos/semphr.h"

/**Binary semaphore is used to indicate that something is happen.*/
xQueueHandle queue;

void listenForHTTP(void *params){
  int count = 0 ;
  while(true)
  {
    count++;
    printf("received HTTP message \n ");
    vTaskDelay(5000/portTICK_PERIOD_MS);
  }
}

void task1(void *params){
  while(true){
    printf("doing something with http \n ");
  }
}


void app_main(void)
{
   //task1(); This will not working 
   //task2(); This will not working 
   queue = xQueueCreate(3,sizeof(int));
   
   xTaskCreate(&listenForHTTP,"get  ",2048,NULL,2,NULL);
   xTaskCreate(&task1,"do something with the http",2048,NULL,2,NULL);
}
