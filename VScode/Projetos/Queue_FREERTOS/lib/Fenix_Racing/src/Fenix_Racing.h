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
#include <avr/wdt.h> 
#include <mcp_can.h>

/*************************************************************************************
 *                                       VARIAVEIS                                   * 
**************************************************************************************/


/**
 * @brief Handlers para as funcoes de Task
 * 
 */
typedef enum
{
    STATUS_SUCESS = 0U, 				/*!< Generic operation success status */
    STATUS_ERROR,						/*!< Generic operation failure status */
} status_t;

/**
 * @brief  Struct para Sensores analogicos para Suspensao
 *  " VER RELACAO LINEAR "
 * Legenda: E e D - Esquerda,Direita ; D e T - Diantero,Traseiro 
 */
typedef struct { 
  int16_t potDD;
  int16_t potDE;
  int16_t potTD;
  int16_t potTE;
  int16_t potdirecao;
  int16_t pressao; 
}int16_Analog_Sensores;

typedef struct{
  int16_t ax;
  int16_t ay;
  int16_t az;
  int16_t gx;
  int16_t gy;
  int16_t gz;
  float ax_scaled;
  float ay_scaled;
  float az_scaled;
  float gx_scaled;
  float gy_scaled;
  float gz_scaled;
  float temp;
}ft_I2C_Sensores;

/**
     * @brief Dados obtidos da ECU via CAN
     * 
     */
typedef struct{
    int16_t seconds; // (segundos) Tempo em que a ECU esta ligada 
    int16_t rpm; // (RPM) Rotacao do motor
    int16_t baro; // (kPa) Pressao barometrica
    int16_t map; // (kPa) Pressao do coletor de admissao
    int16_t mat; // (C) Temperatura do ar de admissao/
    int16_t cltc; // Temperatura do motor
    int16_t tps; // (%) Posicao do acelerador
    float maf; // (g/s) Fluxo de ar
    int8_t gear; // Marcha
    float batt; // (V) Tensao da bateria
    float VSS1; // (km/h) Velocidade da roda 1
    float VSS2; // (km/h) Velocidade da roda 2
    float VSS3; // (km/h) Velocidade da roda 3
    float VSS4; // (km/h) Velocidade da roda 4
}Engine_Data;

/**
 * @brief Struct para dados a serem enviados via CAN
 * 
 */
typedef struct {
  uint8_t data[8]; // Byte (teste)
  long unsigned int id;
  uint8_t length; // unsigned char

}CAN_Message;



/*************************************************************************************
 *                                       FUNCOES                                     * 
**************************************************************************************/
// CAN
status_t CAN_Init(void);
void ECU_CAN_Read(Engine_Data *);
void ECU_CAN_Print(Engine_Data *);
void CAN_SendMsg1(int16_Analog_Sensores *, CAN_Message *);
void CAN_SendMsg2(int16_Analog_Sensores *, CAN_Message *);
void CAN_SendMsg3(ft_I2C_Sensores *, CAN_Message *);
void CAN_SendMsg4(ft_I2C_Sensores *, CAN_Message *);


// Calcular
void armazenarBytes(int valor, byte *dataArray, int startIndex);
void Calcular_Distancia();
void Calcular_Curso_Amortecedor(uint16_t pot);
void Calcular_Curso_Direcao(uint16_t direcao);
#endif