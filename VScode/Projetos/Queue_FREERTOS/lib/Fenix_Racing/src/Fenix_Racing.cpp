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



void armazenarBytes(int valor, byte *dataArray, int startIndex) 
{
dataArray[startIndex] = highByte(valor);
dataArray[startIndex + 1] = lowByte(valor);
};


  //ToDo Testar
float Calcular_distancia(int16_t veloc,int16_t antiga_veloc, int8_t status)
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

