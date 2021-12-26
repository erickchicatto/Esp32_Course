#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

#include "freertos/semphr.h"

xSemaphoreHandle mutexBus;

void writeToBus(char * message){
    printf(message);
}

void task1(){
  while(true){
    printf("reading temperature \n ");
    if(xSemaphoreTake(mutexBus,1000/portTICK_PERIOD_MS))
    {
      writeToBus("temperature is 25c \n");
      xSemaphoreGive(mutexBus);// to make mutex available
    }
    else
    {
      printf("reading temperature timed out \n");
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void task2(){
  while(true){
    printf("reading humedicity \n ");
    if(xSemaphoreTake(mutexBus,1000/portTICK_PERIOD_MS))
    {
      writeToBus("humedicity is 50c \n");
      xSemaphoreGive(mutexBus);// to make mutex available
    }
    else
    {
      printf("writting humedicity timed out \n");
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}


void app_main(void)
{
   //task1(); This will not working 
   //task2(); This will not working
   mutexBus = xSemaphoreCreateMutex();


   xTaskCreate(&task1,"temperature reading ",2048,NULL,2,NULL);
   xTaskCreate(&task2,"humidity reading",2048,NULL,2,NULL);
   

}
