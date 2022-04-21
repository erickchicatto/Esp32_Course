#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"

#include <sys/time.h>
#include "ultrasonic.h"


#define MAX_DISTANCE_CM         500 // 5m max
#define GPIO_TRIGGER	           13           // this is the pins
#define GPIO_ECHO	              25           // this is the pins 
#define TRIGGER_LOW_DELAY       4
#define TRIGGER_HIGH_DELAY      10
#define PING_TIMEOUT            6000
#define ROUNDTRIP               58

#define CMD_START               100
#define CMD_STOP                200
#define CMD_MEASURE             300
#define CMD_CLEAR               400

#define timeout_expired(start, len) ((uint32_t)(get_time_us() - (start)) >= (len))
#define RETURN_CRTCAL(MUX, RES) do { portEXIT_CRITICAL(&MUX); return RES; } while(0)

typedef struct {
	uint16_t command;
	uint32_t distance;
	TaskHandle_t taskHandle;
} CMD_t;

static portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
QueueHandle_t xQueueCmd;

//Need to investigate for what this?
static inline uint32_t get_time_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_usec;
}


void ultrasonic_init(const ultrasonic_sensor_t *dev)
{
  gpio_pad_select_gpio(dev->trigger_pin);
  gpio_pad_select_gpio( dev->echo_pin );
  gpio_set_direction(dev->trigger_pin, GPIO_MODE_OUTPUT);
  gpio_set_direction(dev->echo_pin, GPIO_MODE_INPUT);

  gpio_set_level(dev->trigger_pin, 0);
}

esp_err_t ultrasonic_measure_cm(const ultrasonic_sensor_t *dev, uint32_t max_distance, uint32_t *distance)
{

  if(!distance){
    return ESP_ERR_INVALID_ARG;
  }

  portENTER_CRITICAL(&mux);

  //Ping Low for 2.4 us , then high 10 us  
  gpio_set_level(dev->trigger_pin, 0);
  ets_delay_us(TRIGGER_LOW_DELAY);
  gpio_set_level(dev->trigger_pin, 1);
  ets_delay_us(TRIGGER_HIGH_DELAY);
  gpio_set_level(dev->trigger_pin, 0);

  //previuos ping isn't ended
  if(gpio_get_level(dev->echo_pin)){
    RETURN_CRTCAL(mux, ESP_ERR_ULTRASONIC_PING);
  }

  //wait for the echo 
  uint32_t start = get_time_us();

  while(!gpio_get_level(dev->echo_pin))
  {
    if (timeout_expired(start, PING_TIMEOUT)){
      RETURN_CRTCAL(mux, ESP_ERR_ULTRASONIC_PING_TIMEOUT);
    }
  }

  // got echo measuring
  uint32_t echo_start = get_time_us();
  uint32_t time = echo_start;
  uint32_t meas_timeout = echo_start + max_distance * ROUNDTRIP;

  while(gpio_get_level(dev->echo_pin)){
    time = get_time_us();
    
    if(timeout_expired(echo_start, meas_timeout))
    {
     RETURN_CRTCAL(mux, ESP_ERR_ULTRASONIC_ECHO_TIMEOUT);
    }

  
  }
   portEXIT_CRITICAL(&mux);
  *distance = (time - echo_start) / ROUNDTRIP;
  return ESP_OK;
}


void ultrasonic(void *pvParamters)
{
	ESP_LOGI(pcTaskGetTaskName(0), "Start");
	CMD_t cmdBuf;
	cmdBuf.command = CMD_MEASURE;
	cmdBuf.taskHandle = xTaskGetCurrentTaskHandle();

	ultrasonic_sensor_t sensor = {
		.trigger_pin = GPIO_TRIGGER,
		.echo_pin = GPIO_ECHO
	};

	ultrasonic_init(&sensor);

	while (true) {
		uint32_t distance;
		esp_err_t res = ultrasonic_measure_cm(&sensor, MAX_DISTANCE_CM, &distance);
		if (res != ESP_OK) {
			printf("Error: ");
			switch (res) {
				case ESP_ERR_ULTRASONIC_PING:
					printf("Cannot ping (device is in invalid state)\n");
					break;
				case ESP_ERR_ULTRASONIC_PING_TIMEOUT:
					printf("Ping timeout (no device found)\n");
					break;
				case ESP_ERR_ULTRASONIC_ECHO_TIMEOUT:
					printf("Echo timeout (i.e. distance too big)\n");
					break;
				default:
					printf("%d\n", res);
			}
		} else {
			printf("Distance: %d cm, %.02f m\n", distance, distance / 100.0);
			cmdBuf.distance = distance;
			xQueueSend(xQueueCmd, &cmdBuf, 0);
		}
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}

void app_main()
{
	/* Create Queue */
	xQueueCmd = xQueueCreate( 10, sizeof(CMD_t) );
	xTaskCreate(ultrasonic, "ultrasonic", 1024*2, NULL, 2, NULL);
}
