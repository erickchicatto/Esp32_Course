#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_system.h"

//Handle for a Task
static TaskHandle_t receiverHandler = NULL;
//Handle for a semaphore
xSemaphoreHandle mutexBus;

//Handle for a binary semaphore
xSemaphoreHandle binSemaphore;

//queue
struct AMessage
{
  char ucMessageID;
  char ucData[20];
}

//event group


//Example enddianes using pointers in C and apply to this board 


// To study eventGroups : https://www.freertos.org/RTOS_Task_Notification_As_Event_Group.html
void writeToBus(char *message)
{
  printf("message")
}

void on_timer(TimerHandle_t xTimer)
{
    printf("time hit %lld \n",esp_timer_get_time() /1000);
}

/*For a simple task */
void task1()
{
    while(true)
    {
     printf("This is an example of a task ");
     vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

/*For a mutex*/
void task2()
{
  while(true)
  {
    if(xSemaphoreTake(mutexBus,1000/portTICK_PERIOD_MS))
    {
      writeToBus("Example of how to use semaphore \n");
      xSemaphoreGive(mutexBus);
    }
    else
    {
     writeToBus("Fail with this example  \n");
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
    }
  
}

/*For a binary semaphore that is used to indicate that something is happen */
void task3()
{
  while(true)
  {
    printf("Use a binary semaphore \n");
    xSemaphoreGive(binSemaphore);
  }
  vTaskDelay(1000/portTICK_PERIOD_MS);
    
}

void task4()
{
    while(true)
    {
      xSemaphoreTake(binSemaphore,portMAX_DELAY);
      printf("do something with this semaphore take \n");
    }
  vTaskDelay(1000/portTICK_PERIOD_MS);
}


void vTask(void *pvParameters)
{
  QueueHandle_t xQueue1, xQueue2;
  
  //Create a queue capable of containing  10 unsigned long values
  xQueue1 = xQueueCreate(10,sizeof(unsigned long));

  if(xQueue1 == NULL)
  {
   /*Queue is not created*/
  }
  
  xQueue2 = xQueueCreate( 10, sizeof( struct AMessage * ) );

  if(xQueue2 == NULL)
  {
   /*Queue is not created*/
  }

  printf("All works ok \n");

}


void app_main(void)
{
  //Simple task
  xTaskCreate(&task1,"example for task ",2048,NULL,2,NULL);
  
  
  //Task using semaphore
  mutexBus = xSemaphoreCreateMutex();
  xTaskCreate(&task2,"example for semaphore ",2048,NULL,2,NULL);
  
  
  
  //Create a binSemaphore
  binSemaphore = xSemaphoreCreateBinary();
  xTaskCreate(&task3,"example for semaphore binary",2048,NULL,2,NULL);
  xTaskCreate(&task4,"example for semaphore binary",2048,NULL,2,NULL);
  
  //Queue 
  xTaskCreate(&vTask,"example for a queue",2048,NULL,2,NULL);

  //Event Group
  //http://www.openrtos.net/xEventGroupWaitBits.html    


  //This is for the timer 
  printf("app started %lld \n",esp_timer_get_time() /1000);
  TimerHandle_t xTimer = xTimerCreate("my timer",pdMS_TO_TICKS(1000),true,NULL,on_timer);
  xTimerStart(xTimer,0);
}
