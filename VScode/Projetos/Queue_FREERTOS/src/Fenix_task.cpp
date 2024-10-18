/**
 * @file tasks.cpp
 * @author Rhomulo
 * @brief 
 * @version 0.1
 * @date 2024-10-16
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
#include <C:\github\Fenix_Racing\VScode\Projetos\Queue_FREERTOS\include\Fenix_task.h>

// Inicio Variaveis //
int16_Analog_Sensores Analog_Sensores;
CAN_Message CAN_Msg1; // id, length, data
CAN_Message CAN_Msg2;
CAN_Message CAN_Msg3;
CAN_Message CAN_ECU1;
ECU_Data ECU;
float led_pin,tach;
TaskHandle_t I2CHandle;
QueueHandle_t Queue_CAN;
MCP_CAN CAN0(53);
// Fim Variaveis //

/**
 * @brief Task para recebimento das mensagens CAN da ECU
 * 
 * @param pvParameters 
 */
void Task1Receive_CAN(void *pvParameters)
 {
  while(1){
   (void) pvParameters; 


  if (!digitalRead(2)) // Se o pino CAN0_INT (Pino 2) é 0, recebe o buffer (buffer = dados)
  {
    CAN0.readMsgBuf(&CAN_ECU1.id, &CAN_ECU1.length, CAN_ECU1.data); // CAN0.readMsgBuf( rxId: ID std(11bits) ou extd(29bits), len = data length, buf = data byte(s))
for (byte i = 0; i < CAN_ECU1.length; i++) {
      if ((CAN_ECU1.id & 0x5F0) == 0x5F0) {
        ECU.sec = CAN_ECU1.data[0] * 256 + CAN_ECU1.data[1];
        ECU.rpm = CAN_ECU1.data[6] * 256 + CAN_ECU1.data[7];
      }
      tach = 19.152 * ECU.rpm + 10.662;
      analogWrite(led_pin, tach);
      if ((CAN_ECU1.id & 0x5F2) == 0x5F2) {
        // Conversao de faraday para celsius
        ECU.cltc = (((CAN_ECU1.data[6] * 256 + CAN_ECU1.data[7]) / 10) - 32) * 0.55;
      }
      if ((CAN_ECU1.id & 0x611) == 0x611) {
        ECU.gear = CAN_ECU1.data[6];
        }
      }
    }
    Serial.println("TASK 1");
    vTaskDelay(1000/ portTICK_PERIOD_MS);
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
      Analog_Sensores.potED = analogRead(A0);
      Analog_Sensores.potDD = analogRead(A1);
      Analog_Sensores.potET = analogRead(A2);
      Analog_Sensores.potDT = analogRead(A3);
      Analog_Sensores.potdirecao = analogRead(A4);
      Analog_Sensores.pressao = analogRead(A5);
      //ToDo Conversao para deslocamento da suspensao 
      armazenarBytes(Analog_Sensores.potED,CAN_Msg1.data, 0); // Funcao da Fenix_Racing.h 
      armazenarBytes(Analog_Sensores.potDD,CAN_Msg1.data, 2);
      armazenarBytes(Analog_Sensores.potET,CAN_Msg1.data, 6);
      armazenarBytes(Analog_Sensores.potDT,CAN_Msg1.data, 8);
      armazenarBytes(Analog_Sensores.potdirecao,CAN_Msg2.data, 0);
      armazenarBytes(Analog_Sensores.pressao,CAN_Msg2.data, 2);
      byte sndStat1 = CAN0.sendMsgBuf(0x001, 0, 8, CAN_Msg1.data);
       if (sndStat1 == CAN_OK) {
       Serial.println("Msg enviada!");
       } else {
       Serial.println("Error ao enviar msg...");
       }
      byte sndStat2 = CAN0.sendMsgBuf(0x002, 0, 8, CAN_Msg2.data);
      if (sndStat2 == CAN_OK) {
      Serial.println("Msg enviada!");
      } else {
      Serial.println("Error ao enviar msg...");
      }
        Serial.println("TASK2");
      // Delay for a period
      vTaskDelay(100000/ portTICK_PERIOD_MS);
        wdt_reset();
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
  if(Wire.read() ==-1){
    vTaskSuspend(I2CHandle);
  }

   Serial.println("TASK 3");
   vTaskDelay(1000/ portTICK_PERIOD_MS);

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


/**
 * @brief Construct init modulo CAN
 * 
 * @return status_t 
 */
status_t CAN_Init(void){
    if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("Modulo CAN iniciado!");
    return STATUS_SUCESS;
  } else {
    Serial.println("Erro ao iniciar CAN!");
    return STATUS_ERROR;
  }
  
CAN0.setMode(MCP_NORMAL);// Set operation mode to normal so the MCP2515 sends acks to received data.

}

