/**
 * @file Fenix_Racing.h
 * @author Rhomulo Thiago
 * @brief 
 * @version 0.1
 * @date 2024-08-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef FENIX_RACING_H
#define FENIX_RACING_H
#include <Arduino.h>
#include <stdint.h>

/*************************************************************************************
 *                                       VARIAVEIS                                   * 
**************************************************************************************/
/**
 * @brief  Struct para Sensores analogicos para Suspensao
 *  " VER RELACAO LINEAR "
 * Legenda: E e D - Esquerda,Direita ; D e T - Diantero,Traseiro 
 */
typedef struct { 
  int16_t potED;
  int16_t potDD;
  int16_t potET;
  int16_t potDT;
  int16_t potdirecao;
  int16_t pressao; 
}int16_Analog_Sensores;

/**
 * @brief Struct para Sensores aquisitados pela ECU
 * 
 */
typedef struct{
  int16_t cltc;
  int16_t rpm;
  int16_t veloc;
  byte gear; 
  float sec;
  float batt;
}ECU_Data;

/**
 * @brief Struct para dados a serem enviados via CAN
 * 
 */
typedef struct {
  uint8_t data[8]; // Byte (teste)
  long unsigned int id;
  uint8_t length; // unsigned char

}CAN_Data;


/*************************************************************************************
 *                                       FUNCOES                                     * 
**************************************************************************************/

void armazenarBytes(int valor, byte *dataArray, int startIndex);
void Calcular_distancia();
void Calcular_Curso_Amortedor(uint16_t pot);
void Calcular_Curso_Direcao(uint16_t direcao);

#endif