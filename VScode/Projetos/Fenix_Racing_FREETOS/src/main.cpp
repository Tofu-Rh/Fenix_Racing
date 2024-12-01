/**
 * @file main.cpp
 * @author Rhomulo Thiago
 * @brief 
 * @version 0.2
 * @date 2024-08-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <Arduino_FreeRTOS.h> // FreeRTOS
#include <Arduino.h> // Config Arduino
#include <mcp_can.h> // Protocolo CAN 
#include <SPI.h>  // Protocolo SPI
#include <Wire.h> // Protocolo I2C
#include <Fenix_Racing.h> // Funcoes da equipe e Type structs de variaveis
//#include <Adafruit_MPU6050.h> // Acelerometro
//#include <Adafruit_MLX90614.h> // Temperatura
//#include <avr/wdt.h> // Watchdog


// InicioVariaveis //
int16_Analog_Sensores Analog_Sensores;
CAN_Data CAN_Data1; // CAN_Data.id; CAN_Data.length; CAN_Data.data;
CAN_Data CAN_Data2;
CAN_Data CAN_Receive;
ECU_Data ECU;
MCP_CAN CAN0(53);
float led_pin,tach;
TaskHandle_t CANHandle;
TaskHandle_t I2CHandle;
// FimVariaveis //

// InicioTasks //
void Task1Receive_CAN(void *pvParameters)

 {
  while(1){
   (void) pvParameters; 

  if (!digitalRead(2)) // Se o pino CAN0_INT (Pino 2) é 0, recebe o buffer (buffer = dados)
  {
    CAN0.readMsgBuf(&CAN_Receive.id, &CAN_Receive.length, CAN_Receive.data); // CAN0.readMsgBuf( rxId: ID std(11bits) ou extd(29bits), len = data length, buf = data byte(s))
for (byte i = 0; i < CAN_Receive.length; i++) {
      if ((CAN_Receive.id & 0x5F0) == 0x5F0) {
        ECU.sec = CAN_Receive.data[0] * 256 + CAN_Receive.data[1];
        ECU.rpm = CAN_Receive.data[6] * 256 + CAN_Receive.data[7];
      }
      tach = 19.152 * ECU.rpm + 10.662;
      analogWrite(led_pin, tach);
      if ((CAN_Receive.id & 0x5F2) == 0x5F2) {
        // Conversao de faraday para celsius
        ECU.cltc = (((CAN_Receive.data[6] * 256 + CAN_Receive.data[7]) / 10) - 32) * 0.55;
      }
      if ((CAN_Receive.id & 0x611) == 0x611) {
        ECU.gear = CAN_Receive.data[6];
        }
      }
    }
    Serial.println("TASK_1_CAN");
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }

 }

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
      armazenarBytes(Analog_Sensores.potED,CAN_Data1.data, 0); // Funcao da Fenix_Racing.h 
      armazenarBytes(Analog_Sensores.potDD,CAN_Data1.data, 2);
      armazenarBytes(Analog_Sensores.potET,CAN_Data1.data, 6);
      armazenarBytes(Analog_Sensores.potDT,CAN_Data1.data, 8);
      armazenarBytes(Analog_Sensores.potdirecao,CAN_Data2.data, 0);
      armazenarBytes(Analog_Sensores.pressao,CAN_Data2.data, 2);
      byte sndStat1 = CAN0.sendMsgBuf(0x001, 0, 8, CAN_Data1.data);
       if (sndStat1 == CAN_OK) {
       Serial.println("Msg enviada!");
       } else {
       Serial.println("Error ao enviar msg...");
       }
      byte sndStat2 = CAN0.sendMsgBuf(0x002, 0, 8, CAN_Data2.data);
      if (sndStat2 == CAN_OK) {
      Serial.println("Msg enviada!");
      } else {
      Serial.println("Error ao enviar msg...");
      }
        Serial.println("TASK_2_ANALOG");
      // Delay for a period
      vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
};



void Task3I2C_Sensores(void *pvParameters)
 {
  while(1){
    if(Wire.read() == -1){
      vTaskSuspend(I2CHandle);
    }
   (void) pvParameters; 
   Serial.println("TASK_3_I2C");
   vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
  };

// FimTasks //
void setup(void)
{
  Serial.begin(9600);
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("Modulo CAN iniciado!");
  } else {
    Serial.println("Erro");
  }
    CAN0.setMode(MCP_NORMAL);// Set operation mode to normal so the MCP2515 sends acks to received data.
    // Recebe os dados da ECU
    xTaskCreate(Task1Receive_CAN,"CAN Data ECU",1024,NULL,3,NULL);
    // Cria a task  para ler os sensores analogicos e enviar os dados via CAN
    xTaskCreate(Task2Analog_Sensores, "Ler Sensores Analogicos", 1024, NULL, 2, &I2CHandle);
    // Cria a task para ler os sensores I2C 
    xTaskCreate(Task3I2C_Sensores, "Ler Sensores I2C", 128, NULL, 1, NULL);
}

void loop(){}

