/**
 * @file Fenix_Racing.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <Arduino_FreeRTOS.h>
#include "Fenix_Racing.h"
#include <Arduino.h>
#include <task.h>
#include <SPI.h>
#include <projdefs.h>


/**
 * @brief Funcao de auxilio para declarar a mensagem CAN.
 * O valor é dividido em 2 bytes e armazenado no array de dados.
 * 
 * @param valor 
 * variavel a ser armazenada
 * @param dataArray 
 * array de dados
 * @param startIndex
 * indice inicial do array 
 */
void armazenarBytes(int valor, byte *dataArray, int startIndex) 
{
dataArray[startIndex] = highByte(valor);
dataArray[startIndex + 1] = lowByte(valor);
};


  //ToDo Testar
/**
 * @brief Funcao de auxilio para calculo da distancia total percorrida pelo carro
 * 
 * @param veloc 
 * Velocidade do carro obtida por CAN
 * @param antiga_veloc
 * Armazena a velocidade calculada da ultima iteracao
 * @param status 
 * Status do carro, para zerar a distancia (0 - carro ligou agora)
 * @return float 
 */
float Calcular_Distancia(int16_t veloc,int16_t antiga_veloc, int8_t status)
{
  float distancia;
  float dt = 0.001; // Tempo de amostragem em segundos
  
  // Verificar se o carro ligou agora
  if (status == 0)
  {
    distancia = 0;
  }  
  // Iteracao para calcular a distancia percorrida
  distancia = distancia + 0.5*(veloc + antiga_veloc)*dt;
  return distancia;
};  

/**
 * @brief Calcula o tempo em ms da task. Precisa de ter um startTick
 * declaro no inicio da task : TickType_t startTick = xTaskGetTickCount();
 * 
 * @param startTick 
 */

void Calcular_Tempo(TickType_t startTick){
          // Capture end tick count
        TickType_t endTick = xTaskGetTickCount();

        // Calculate elapsed time in ticks
        TickType_t elapsedTicks = endTick - startTick;

        // Converte para ms (assuming configTICK_RATE_HZ is 1000)
        uint32_t elapsedTimeMs = elapsedTicks * portTICK_PERIOD_MS;

        // Print the elapsed time
        Serial.print("Task1Receive_CAN execution time: ");
        Serial.print(elapsedTimeMs);
        Serial.println(" ms");
}