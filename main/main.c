#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

// To study eventGroups : https://www.freertos.org/RTOS_Task_Notification_As_Event_Group.html

EventGroupHandle_t evtGrp;
const int gotHttps = BIT0;
const int gotBle = BIT1;


void listenForHTTP(void *params){

  while(true)
  {
    xEventGroupSetBits(evtGrp,gotHttps);
    printf("got https\n");
    vTaskDelay(2000/portTICK_PERIOD_MS);
  }
}

void listenForBlueetooh(void *params){

  while(true)
  {
    xEventGroupSetBits(evtGrp,gotBle);
    printf("got BLE\n");
    vTaskDelay(5000/portTICK_PERIOD_MS);
  }

}

void task1(void *params){
  
  while(true){
    xEventGroupWaitBits(evtGrp,gotHttps | gotBle ,true,true,portMAX_DELAY);
    printf("received https and bluetooh \n");
    vTaskDelay(5000/portTICK_PERIOD_MS);
  }

}


void app_main(void)
{
   //task1(); This will not working 
   //task2(); This will not working 
   evtGrp = xEventGroupCreate();
   
   xTaskCreate(&listenForHTTP,"get htpps ",2048,NULL,1,NULL);
   xTaskCreate(&listenForBlueetooh,"get BLE",2048,NULL,1,NULL);
   xTaskCreate(&task1,"do something with the http",2048,NULL,1,NULL);
}
