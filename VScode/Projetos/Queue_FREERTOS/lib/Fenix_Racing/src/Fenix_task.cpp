/**
 * @file tasks.cpp
 * @author Rhomulo
 * @brief 
 * @version 0.2
 * @date 2024-10-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <Fenix_Racing.h> // Funcoes da equipe e Type structs de variaveis
#include <task.h>
#include <queue.h>
#include <mcp_can.h>
#include <Wire.h>
#include <Fenix_Task.h>
//#include <MPU6050.h>

// Inicio Variaveis //
int16_Analog_Sensores Analog_Sensores;
CAN_Message CAN_Msg1; // id, length, data
CAN_Message CAN_Msg2;
CAN_Message CAN_Msg3;
CAN_Message CAN_Msg4;
Engine_Data ECU_Data;

float led_pin,tach;
TaskHandle_t I2CHandle;
QueueHandle_t Queue_CAN;
// Fim Variaveis //

/**
 * @brief Task para recebimento das mensagens CAN da ECU
 * 
 * @param pvParameters 
 */
void Task1Receive_CAN(void *pvParameters)
 {
     (void) pvParameters; 
  while(1){
   // Armazena os valores da mega no struct ECU_Data
    ECU_CAN_Read(&ECU_Data); 
    Serial.println("TASK 1");
    vTaskDelay(100/ portTICK_PERIOD_MS);
  }
 }

/**
 * @brief Task para leitura dos sensores analogicos e envio destes dados via CAN
 * 
 * @param pvParameters 
 */
void Task2Analog_Sensores(void *pvParameters) 
{
  (void) pvParameters; 
    while (1) {
      Analog_Sensores.potDD = analogRead(A0);
      Analog_Sensores.potDE = analogRead(A1);
      Analog_Sensores.potTD = analogRead(A2);
      Analog_Sensores.potTE = analogRead(A3);
      Analog_Sensores.potdirecao = analogRead(A4);
      // Olhar Fenix_Racing.cpp para entender o que esta sendo feito
      CAN_SendMsg1(&Analog_Sensores, &CAN_Msg1);
      CAN_SendMsg2(&Analog_Sensores, &CAN_Msg2);
      
      Serial.println("TASK2");
      vTaskDelay(100/ portTICK_PERIOD_MS);
    }
};

/**
 * @brief Task para leitura de sensores I2C
 * 
 * @param pvParameters 
 */
void Task3I2C_Sensores(void *pvParameters)
 {
  (void) pvParameters; 
  while(1){
    
    // If q se cair a conexao ira suspender a task
    if(Wire.read() ==-1){vTaskSuspend(I2CHandle);}

    // Leitura dos sensores I2C
    Serial.println("TASK 3");
    vTaskDelay(100/ portTICK_PERIOD_MS);
  }
 };

/**
 * @brief Construct das tasks do RTOS
 * 
 * @return status_t 
 */
void RTOS_Init(void)
{
    //Cria a queue
   Queue_CAN = xQueueCreate(4, sizeof(CAN_Message));
   // Recebe os dados da ECU
   Serial.println("Criando as tasks...");
    xTaskCreate(Task1Receive_CAN,"CAN Data ECU",1024,NULL,3,NULL);
    // Cria a task  para ler os sensores analogicos e enviar os dados via CAN
    xTaskCreate(Task2Analog_Sensores, "Ler Sensores Analogicos", 1024, NULL, 2, &I2CHandle);
    // Cria a task para ler os sensores I2C 
    xTaskCreate(Task3I2C_Sensores, "Ler Sensores I2C", 128, NULL, 1, NULL);
    //return STATUS_SUCESS;
    vTaskStartScheduler();
}




