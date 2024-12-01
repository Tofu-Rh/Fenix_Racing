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
#include <Fenix_Task.h> // Funcoes de Task
//#include <C:\github\Fenix_Racing\VScode\Projetos\Queue_FREERTOS\include\Fenix_task.h>
//#include <Adafruit_MPU6050.h> // Acelerometro
//#include <Adafruit_MLX90614.h> // Temperatura
#include <avr/wdt.h> // Watchdog


// InicioTasks //


void setup(void)
{
Serial.begin(9600);
// Inicializa o watchdog para 2s
status_t CAN_Init();
wdt_enable(WDTO_2S);
RTOS_Init();

Serial.println("Teste");

//status_t CAN_Init(void);
/*
while(STATUS_ERROR == CAN_Init()){
  Serial.println("Tentando conectar novamente...");
}*/
}

void loop(){}

