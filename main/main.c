#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "freertos/semphr.h"

/**Binary semaphore is used to indicate that something is happen.*/
xSemaphoreHandle binSemaphore;

void listenForHTTP(void *params){
  while(true){
    printf("received HTTP message \n ");
    xSemaphoreGive(binSemaphore);
    vTaskDelay(5000/portTICK_PERIOD_MS);
  }
}

void task2(){
  while(true){
    xSemaphoreTake(binSemaphore,portMAX_DELAY);
    printf("doing something with http \n ");
  }
}


void app_main(void)
{
   //task1(); This will not working 
   //task2(); This will not working 
   binSemaphore = xSemaphoreCreateBinary();
   
   xTaskCreate(&listenForHTTP,"temperature reading ",2048,NULL,2,NULL);
   xTaskCreate(&task2,"do something with the http",2048,NULL,2,NULL);
      
}
