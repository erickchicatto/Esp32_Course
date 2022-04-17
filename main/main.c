#include <stdio.h>
#include "freertos/FreeRtos.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/ledc.h"
#include "esp_log.h"

static char tag[]="servo1";


void sweepServo_task(void *ignore){

   int bitSize = 15;
   int minValue = 500;
   int maxValue = 2500;
   int sweepDuration = 1500;
   int duty = (1<<bitSize)*minValue /20000;
   int direction = 1;
   int valueChangeRate = 20;

   ESP_LOGD(tag, ">> task_Servo1");

  // for the timmer 
   ledc_timer_config_t timer_config; // for the timer config
   timer_config.bit_num=LEDC_TIMER_15_BIT;
   timer_config.freq_hz= 50;
   timer_config.speed_mode = LEDC_HIGH_SPEED_MODE;
   timer_config.timer_num = LEDC_TIMER_0;
   ledc_timer_config(&timer_config);
  
  //for the channel
   ledc_channel_config_t ledc_config;
   ledc_config.channel = LEDC_CHANNEL_0;
   ledc_config.duty = duty;
   ledc_config.gpio_num = 16;
   ledc_config.intr_type = LEDC_INTR_DISABLE;
   ledc_config.speed_mode = LEDC_HIGH_SPEED_MODE;
   ledc_config.timer_sel = LEDC_TIMER_0;
   ledc_channel_config(&ledc_config);


   // you can alterate that after
   int changesPerSweep = sweepDuration / valueChangeRate ;
   int changeDelta = ((maxValue-minValue)/changesPerSweep);
   int i;
   ESP_LOGD(tag, "sweepDuration : %d seconds",sweepDuration);
   ESP_LOGD(tag, "changesPerSweep : %d seconds",changesPerSweep);
   ESP_LOGD(tag, "changeDelta : %d seconds",changeDelta);
   ESP_LOGD(tag, "valueChangeRate: %d ",valueChangeRate);

   while(1)
   {
      for(i=0;i<changesPerSweep;++i)
      {
         if(direction > 0)
         {
          duty += changeDelta;
         }

         else 
         {
          duty -= changeDelta;
         }
       ledc_set_duty(LEDC_HIGH_SPEED_MODE,LEDC_CHANNEL_0,duty);
       ledc_update_duty(LEDC_HIGH_SPEED_MODE,LEDC_CHANNEL_0);
       vTaskDelay(valueChangeRate/portTICK_PERIOD_MS);
      }
     direction = -direction;
     ESP_LOGD(tag,"Direction now  %d",direction);

   }
vTaskDelete(NULL);
}


void app_main(){
 
 xTaskCreate(&sweepServo_task,"sweepServo_task",2048,NULL,5,NULL);
 printf("Servo sweep task started \n");

} 