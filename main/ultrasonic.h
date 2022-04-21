#include <driver/gpio.h>
#include <driver/dac.h>



// we are going to use to nofity if all is ok 
#define ESP_ERR_ULTRASONIC_PING            0x200
#define ESP_ERR_ULTRASONIC_PING_TIMEOUT    0x201
#define ESP_ERR_ULTRASONIC_ECHO_TIMEOUT    0x202

/*Device descriptor*/

typedef struct 
{
    gpio_num_t trigger_pin;
    gpio_num_t echo_pin;
}ultrasonic_sensor_t;


void ultrasonic_init(const ultrasonic_sensor_t *dev);
esp_err_t ultrasonic_measure_cm(const ultrasonic_sensor_t *dev, uint32_t max_distance, uint32_t *distance);




