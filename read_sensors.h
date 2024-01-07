#ifndef READ_SENSORS_H
#define READ_SENSORS_TASK_H

#include "FreeRTOS.h"
#include "queue.h"

#define READ_SENSORS_TASK_PRIORITY (3)
#define READ_SENSORS_TASK_QUEUE_LENGTH  (3u)
#define READ_SENSORS_TASK_STACK_SIZE    (1024*8)

extern TaskHandle_t read_sensors_task_handle;

extern QueueHandle_t read_sensors_task_q;

// Function to create and initialize the analog reader task
void read_sensors_task(void *pvParameters);

#endif /* READ_SENSORS_TASK_H */
