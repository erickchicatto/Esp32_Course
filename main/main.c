#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#define PIN_LED     2
#define PIN_SWITCH  15

void app_main()
{
  gpio_pad_select_gpio(PIN_LED);
  gpio_set_direction(PIN_LED,GPIO_MODE_OUTPUT);
  
  gpio_pad_select_gpio(PIN_SWITCH);
  gpio_set_direction(PIN_SWITCH,GPIO_MODE_INPUT);

  gpio_pullup_en(PIN_SWITCH);
  //gpio_pullup_dis(PIN_SWITCH);

  
  while(true)
  {
    //isOn = !isOn; simulate push button
    int level = gpio_get_level(PIN_SWITCH);
    gpio_set_level(PIN_LED,level);
    vTaskDelay(1);
  }


}