#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "math.h"

#define TAG "DICE"



void example_logs()
{
 esp_log_level_set("LOG",ESP_LOG_INFO);

 ESP_LOGE("LOG","This is an error");
 ESP_LOGW("LOG","This is a warning");
 ESP_LOGI("LOG","This is an info");
 ESP_LOGD("LOG","This is a debbug");
 ESP_LOGV("LOG","This is verbose");

 int number = 0 ;
 ESP_LOGE("TAG 2 ","This is an error %d ",number++);
 ESP_LOGW("TAG 2","This is a warning %d",number++);
 ESP_LOGI("TAG 2","This is an info %d",number++);
 ESP_LOGD("TAG 2","This is a debbug %d ",number++);
 ESP_LOGV("TAG 2","This is verbose %d ",number++);

}

int dice_role()
{
  int random = esp_random();
  int positiveNumber = abs(random);
  int diceNumber = (positiveNumber%6)+1;
  return diceNumber;
}


void app_main(void)
{
   while(1)
   {
     vTaskDelay(1000/portTICK_PERIOD_MS);
     ESP_LOGI(TAG,"random number %d ",dice_role());
   }

}
