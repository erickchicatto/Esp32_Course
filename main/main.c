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
    long ok  = xQueueSend(queue, &count, 1000/portTICK_PERIOD_MS);
    
    if(ok){
      printf("added message to queue");
    }
    else{
       printf("fail to add message to queue");
    }

    vTaskDelay(1000/portTICK_PERIOD_MS);
    
  }
}

void task1(void *params){
  
  while(true){

    int rxInt;
    if(xQueueReceive(queue,&rxInt,5000/portTICK_PERIOD_MS))
    {
      printf("doing something with http %d \n ",rxInt);
    }
    
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
