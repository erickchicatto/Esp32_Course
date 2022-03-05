#include <stdio.h>
#include <esp_log.h>  
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

#define TAG "Memory"

int x = 3;
int y = 0;
int data = 3;
char bss[100];


void app_main(void)
{
  printf("%d %s",data,bss);
  ESP_LOGI(TAG,"xPortGetHeapSize = %d DRAM",xPortGetFreeHeapSize());

  int DRam = heap_caps_get_free_size(MALLOC_CAP_8BIT);
  int IRam = heap_caps_get_free_size(MALLOC_CAP_32BIT) - heap_caps_get_free_size(MALLOC_CAP_8BIT);

  ESP_LOGI(TAG,"DRAM \t \t %d"  ,DRam);
  ESP_LOGI(TAG, "IRam \t \t %d" ,IRam);

}
