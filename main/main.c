#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

static TaskHandle_t receiverHandler = NULL;

void sender(void* params){
  while(true)
  {
   xTaskNotifyGive(receiverHandler);
   xTaskNotifyGive(receiverHandler);
   xTaskNotifyGive(receiverHandler);
   xTaskNotifyGive(receiverHandler);
   vTaskDelay(5000/portTICK_PERIOD_MS);
  }
}

void receiver(void* params){
  while(true)
  {
    int count = ulTaskNotifyTake(pdFALSE,portMAX_DELAY);
    printf("received notification %d times \n",count);
  }
}


void app_main(void)
{
   xTaskCreate(&receiver,"sender",2048,NULL,2,&receiverHandler);
   xTaskCreate(&sender,"receiver",2048,NULL,2,NULL);
}
