#ifndef TASKS_H_
#define TASKS_H_

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>


#define TASK_PRIORITY_CAN
#define TASK_PRIORITY_SENSORS
#define TASK_PRIORITY_I2C


typedef enum
{
    STATUS_SUCCESS = 0U, 				/*!< Generic operation success status */
    STATUS_ERROR,						/*!< Generic operation failure status */
} status_t;




status_t TasksCreate(void);


#endif

