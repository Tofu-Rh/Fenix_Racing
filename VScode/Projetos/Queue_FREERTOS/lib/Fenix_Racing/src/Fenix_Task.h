#ifndef FENIX_TASK_H_
#define FENIX_TASK_H_

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <mcp_can.h>
#include <Fenix_Racing.h>


#define TASK_PRIORITY_CAN
#define TASK_PRIORITY_SENSORS
#define TASK_PRIORITY_I2C


/**
 * @brief Inicializa o RTOS com três tasks rodando em Loop:
 * Task1: Leitura de dados da CAN
 * Task2: Leitura de dados analogico e envio destes CAN
 * Task3: Leitura de dados I2C e envio destes via CAN
 */
void RTOS_Init(void);


#endif

