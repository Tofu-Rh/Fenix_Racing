#include <mcp_can.h>
#include <SPI.h>
#include <Wire.h>
#include <Fenix_Racing.h>
struct Sensores {
  int potED,potDD,potET,potDT,potcurso,pressao; // E e D - Esquerda,Direita ; D e T - Diantero,Traseiro
};
struct ECU {
  int cltf,cltc,sec,rpm,batt,gear; 
};
byte data1[8]; byte data2[8]; byte data3[8]; 
int led_pin = 5; int tach; 
const int CAN0_INT = 2; MCP_CAN CAN0(53);
long unsigned int rxId; unsigned char len = 0; byte rxBuf[8]; char msgString[128];

void setup(void)
{
  Serial.begin(115200);
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("Modulo CAN iniciado!");
  } else {
    Serial.println("Erro");
  }
  CAN0.setMode(MCP_NORMAL);
}

void loop()
{
  Sensores sensor; ECU ECU;
  sensor.potED = analogRead(A0);
  sensor.potDD = analogRead(A1);
  sensor.potET = analogRead(A2);
  sensor.potDT = analogRead(A3);
  sensor.potcurso = analogRead(A5);
  sensor.pressao = analogRead(A4);
  armazenarBytes(sensor.potED,data1, 0);
  armazenarBytes(sensor.potDD,data1, 2);
  armazenarBytes(sensor.potET,data1, 4);
  armazenarBytes(sensor.potDT,data1, 6);
  armazenarBytes(sensor.potcurso,data2, 0);
  armazenarBytes(sensor.pressao,data2, 2);
  byte sndStat1 = CAN0.sendMsgBuf(0x001, 0, 8, data1);
  if (sndStat1 == CAN_OK) {
    Serial.println("Msg enviada!");
  } else {
    Serial.println("Error ao enviar msg...");
  }

  byte sndStat2 = CAN0.sendMsgBuf(0x002, 0, 8, data2);
  if (sndStat2 == CAN_OK) {
    Serial.println("Msg enviada!");
  } else {
    Serial.println("Error ao enviar msg...");
  }
  if (!digitalRead(CAN0_INT))
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);
    if ((rxId & 0x80000000) == 0x80000000) {  
      sprintf(msgString, "Extended ID: 0x%.8lX DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    } else {
      sprintf(msgString, "Standard ID: 0x%.3lX DLC: %1d  Data:", rxId, len);
      Serial.print(msgString);
    }
    if ((rxId & 0x40000000) == 0x40000000) { 
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } else {
for (byte i = 0; i < len; i++) {
      Serial.print(" 0x");
      Serial.print(rxBuf[i], HEX);

      if ((rxId & 0x5F0) == 0x5F0) {
        ECU.sec = rxBuf[0] * 256 + rxBuf[1];
        ECU.rpm = rxBuf[6] * 256 + rxBuf[7];
      }
      tach = 19.152 * ECU.rpm + 10.662;
      analogWrite(led_pin, tach);

      if ((rxId & 0x5F2) == 0x5F2) {
        ECU.cltf = (rxBuf[6] * 256 + rxBuf[7]) / 10;
        ECU.cltc = (ECU.cltf - 32) * 0.55;
      }

      if ((rxId & 0x611) == 0x611) {
        ECU.gear = rxBuf[6];
        }
      }
    }
  }

  Wire.beginTransmission(0x08); 
  Wire.write(ECU.gear);
  Wire.write(0);
  Wire.write(ECU.cltc);
  Wire.write(0);
  Wire.endTransmission();
  delay(1);
}