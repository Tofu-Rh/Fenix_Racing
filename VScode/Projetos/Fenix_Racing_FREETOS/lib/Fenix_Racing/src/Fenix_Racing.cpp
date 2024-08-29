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

void Calcular_distancia()
{
  //ToDo Testar
  

};  