#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

void task1(){
  while(true){
    printf("reading temperature \n ");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void task2(){
  while(true){
    printf("reading humedicity \n ");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}




void app_main(void)
{
   //task1(); This will not working 
   //task2(); This will not working 
   xTaskCreate(&task1,"temperature reading ",2048,NULL,2,NULL);
   xTaskCreate(&task2,"humidity reading",2048,NULL,2,NULL);
   

}
