/**
 * @file Fenix_Racing.cpp
 * @author Rhomulo Thiago (you@domain.com)
 * @brief funcoes de calculo e tratamento de dados com a ECU Megasquirt 3X via CAN
 * @version 0.2 
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

/*************************************************************************************
 *                                       VARIAVEIS                                   *
 * ***********************************************************************************/

CAN_Message Send_Msg1;
CAN_Message Send_Msg2;
CAN_Message Send_Msg3;
CAN_Message Send_Msg4;
CAN_Message CAN_ECU1;
MCP_CAN CAN0(53);


/*************************************************************************************
 *                                       FUNCOES                                     * 
**************************************************************************************/
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

 // Calcular
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



// CAN
/**
 * @brief Inicializa o modulo CAN, retorna 1 caso tenha sucesso
 * 
 * @return status_t 
 */
status_t CAN_Init(void){
    if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("Modulo CAN iniciado!");
    CAN0.setMode(MCP_NORMAL);// Set operation mode to normal so the MCP2515 sends acks to received data.
    return STATUS_SUCESS;
  } else {
    Serial.println("Erro ao iniciar CAN!");
    return STATUS_ERROR;
  }
}

/**
 * @brief  Funcao para leitura dos dados da ECU via CAN
 *  Dados lidos: 
 * @param ECU 
 */
void ECU_CAN_Read(Engine_Data *ECU) {
    
        CAN0.readMsgBuf(&CAN_ECU1.id, &CAN_ECU1.length, CAN_ECU1.data);
        
        // Endereco 1520 (5F0), pega segundos da mega e rpm do motor
        if ((CAN_ECU1.id & 0x5F0) == 0x5F0) {
            ECU->seconds = CAN_ECU1.data[0] * 256 + CAN_ECU1.data[1];
            ECU->rpm = CAN_ECU1.data[6] * 256 + CAN_ECU1.data[7];
        }

        // Endereco 1522 (5F2), pega P_Barometrica,MAP,MAT e temperatura do motor
        if ((CAN_ECU1.id & 0x5F2) == 0x5F2) {
            ECU->baro = (CAN_ECU1.data[0] * 256 + CAN_ECU1.data[1]) / 10;
            ECU->map = (CAN_ECU1.data[2] * 256 + CAN_ECU1.data[3]) / 10;
            ECU->mat = (((CAN_ECU1.data[4] * 256 + CAN_ECU1.data[5]) / 10) - 32) * 0.55;
            ECU->cltc = (((CAN_ECU1.data[6] * 256 + CAN_ECU1.data[7]) / 10) - 32) * 0.55;
        }

        // Endereco ?, pega
        if ((CAN_ECU1.id & 0x5F3) == 0x5F3) {
            ECU->tps = (CAN_ECU1.data[0] * 256 + CAN_ECU1.data[1]) / 10;
            ECU->batt = (CAN_ECU1.data[2] * 256 + CAN_ECU1.data[3]) / 10;
        }

        if ((CAN_ECU1.id & 0x5F8) == 0x5F8) {
            ECU->maf = (CAN_ECU1.data[6] * 256 + CAN_ECU1.data[7]) / 100;
        }

        if ((CAN_ECU1.id & 0x611) == 0x611) {
            ECU->gear = CAN_ECU1.data[6];
        }

        if ((CAN_ECU1.id & 0x61A) == 0x61A) {
            ECU->VSS1 = (CAN_ECU1.data[0] * 256 + CAN_ECU1.data[1]) / 10;
            ECU->VSS2 = (CAN_ECU1.data[2] * 256 + CAN_ECU1.data[3]) / 10;
            ECU->VSS3 = (CAN_ECU1.data[4] * 256 + CAN_ECU1.data[5]) / 10;
            ECU->VSS4 = (CAN_ECU1.data[6] * 256 + CAN_ECU1.data[7]) / 10;
        }
    
}


void ECU_CAN_Print(Engine_Data *ECU, int8_t time) {
    Serial.print("Seconds: ");
    Serial.println(ECU->seconds);
    Serial.print("RPM: ");
    Serial.println(ECU->rpm);
    Serial.print("Baro: ");
    Serial.println(ECU->baro);
    Serial.print("MAP: ");
    Serial.println(ECU->map);
    Serial.print("MAT: ");
    Serial.println(ECU->mat);
    Serial.print("CLT: ");
    Serial.println(ECU->cltc);
    Serial.print("MAF: ");
    Serial.println(ECU->maf);
    Serial.print("Gear: ");
    Serial.println(ECU->gear);
    Serial.print("Battery: ");
    Serial.println(ECU->batt);
    Serial.print("VSS1: ");
    Serial.println(ECU->VSS1);
    Serial.print("VSS2: ");
    Serial.println(ECU->VSS2);
    Serial.print("VSS3: ");
    Serial.println(ECU->VSS3);
    Serial.print("VSS4: ");
    Serial.println(ECU->VSS4);
    vTaskDelay( time / portTICK_PERIOD_MS);
}



void CAN_SendMsg1(int16_Analog_Sensores *Analog_Sensores, CAN_Message *CAN_Msg1) {
    CAN_Msg1->id = 0x001;
    CAN_Msg1->length = 8;

    // Organizar os dados no pacote CAN
    armazenarBytes(Analog_Sensores->potDD, CAN_Msg1->data, 0);
    armazenarBytes(Analog_Sensores->potDE, CAN_Msg1->data, 2);
    armazenarBytes(Analog_Sensores->potTD, CAN_Msg1->data, 4);
    armazenarBytes(Analog_Sensores->potTE, CAN_Msg1->data, 6);

    byte sndStat1 = CAN0.sendMsgBuf(CAN_Msg1->id, 0, CAN_Msg1->length, CAN_Msg1->data);
    if (sndStat1 == CAN_OK) {
        Serial.println("Msg enviada!");
    } else {
        Serial.println("Error ao enviar msg...");
    }
}


void CAN_SendMsg2(int16_Analog_Sensores *Analog_Sensores,CAN_Message *CAN_Msg2){
    CAN_Msg2->id = 0x002;
    CAN_Msg2->length = 8;

    // Organizar os dados no pacote CAN
    armazenarBytes(Analog_Sensores->potdirecao, CAN_Msg2->data, 0);
    armazenarBytes(Analog_Sensores->potDE, CAN_Msg2->data, 2);
    armazenarBytes(Analog_Sensores->potTD, CAN_Msg2->data, 4);
    armazenarBytes(Analog_Sensores->potTE, CAN_Msg2->data, 6);

    byte sndStat2 = CAN0.sendMsgBuf(CAN_Msg2->id, 0, CAN_Msg2->length, CAN_Msg2->data);
    if (sndStat2 == CAN_OK) {
        Serial.println("Msg enviada!");
    } else {
        Serial.println("Error ao enviar msg...");
    }
}
void CAN_SendMsg3(ft_I2C_Sensores *I2C_Sensores,CAN_Message *CAN_Msg3){
    CAN_Msg3->id = 0x003;
    CAN_Msg3->length = 8;

    // Organizar os dados no pacote CAN
    armazenarBytes(I2C_Sensores->ax, CAN_Msg3->data, 0);
    armazenarBytes(I2C_Sensores->ay, CAN_Msg3->data, 2);
    armazenarBytes(I2C_Sensores->az, CAN_Msg3->data, 4);
    armazenarBytes(I2C_Sensores->gx, CAN_Msg3->data, 6);

    byte sndStat3 = CAN0.sendMsgBuf(CAN_Msg3->id, 0, CAN_Msg3->length, CAN_Msg3->data);
    if (sndStat3 == CAN_OK) {
        Serial.println("Msg enviada!");
    } else {
        Serial.println("Error ao enviar msg...");
    }
}
