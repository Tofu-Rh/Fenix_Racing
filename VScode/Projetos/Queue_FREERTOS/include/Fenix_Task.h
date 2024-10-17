#ifndef FENIX_TASK_H_
#define FENIX_TASK_H_

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <mcp_can.h>

#define TASK_PRIORITY_CAN
#define TASK_PRIORITY_SENSORS
#define TASK_PRIORITY_I2C





typedef enum
{
    STATUS_SUCESS = 0U, 				/*!< Generic operation success status */
    STATUS_ERROR,						/*!< Generic operation failure status */
} status_t;



void TasksCreate(void);

status_t CAN_Init(void);

#endif

