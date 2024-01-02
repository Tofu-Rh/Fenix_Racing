#include <mcp_can.h>
#include <SPI.h>
#include <Wire.h>
#include <Fenix_Racing.h>
// InicioVariáveis //
struct Sensores {
  int potED,potDD,potET,potDT,potcurso,pressao; // E e D - Esquerda,Direita ; D e T - Diantero,Traseiro
};
struct ECU {
  int cltf,cltc,sec,rpm,batt,gear; // Dados coletados da ECU
};
byte data1[8]; byte data2[8]; byte data3[8]; //Bytes para envio de dados
int led_pin = 5; int tach; // dados do tacometro
const int CAN0_INT = 2; MCP_CAN CAN0(53); //Config do modulo CAN 2515
long unsigned int rxId; unsigned char len = 0; byte rxBuf[8]; char msgString[128]; // var's para o recebimento de dados
// FimVariáveis //
void setup(void)
{
  Serial.begin(115200);
  // Inicialize o MCP2515 em execução a 16MHz com uma taxa de transmissão de 500kb/s e as máscaras e os filtros desativados.
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("Modulo CAN iniciado!");
  } else {
    Serial.println("Erro");
  }
  CAN0.setMode(MCP_NORMAL);// Set operation mode to normal so the MCP2515 sends acks to received data.
}

void loop()
{
  ////InicioSensores////
  Sensores sensor; ECU ECU; // declaração das variaveis struct
  sensor.potED = analogRead(A0);
  sensor.potDD = analogRead(A1);
  sensor.potET = analogRead(A2);
  sensor.potDT = analogRead(A3);
  sensor.potcurso = analogRead(A5);
  sensor.pressao = analogRead(A4);
  // Primeiro pacote de data
  armazenarBytes(sensor.potED,data1, 0); // Função da Fenix_Racing.h 
  armazenarBytes(sensor.potDD,data1, 2);
  armazenarBytes(sensor.potET,data1, 4);
  armazenarBytes(sensor.potDT,data1, 6);
  // Segundo pacote de data
  armazenarBytes(sensor.potcurso,data2, 0);
  armazenarBytes(sensor.pressao,data2, 2);
  ////FimSensores////
  ////InicioenviarCAN////
  byte sndStat1 = CAN0.sendMsgBuf(0x001, 0, 8, data1); // CAN0.sendMsgBuf(ID da msg, std=0 ou extd=1, len = tamanho da msg, buf=data byte(s))
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
  ////FimenviarCAN/////
  ////IniciolerCAN////
  if (!digitalRead(CAN0_INT)) // Se o pino CAN0_INT está em estado baixo, recebe o buffer (buffer = dados)
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf); // CAN0.readMsgBuf( rxId: ID std(11bits) ou extd(29bits), len = data length, buf = data byte(s))
    if ((rxId & 0x80000000) == 0x80000000) {   // Determine if ID is standard (11 bits) or extended (29 bits)
      sprintf(msgString, "Extended ID: 0x%.8lX DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    } else {
      sprintf(msgString, "Standard ID: 0x%.3lX DLC: %1d  Data:", rxId, len);
      Serial.print(msgString);
    }
    if ((rxId & 0x40000000) == 0x40000000) {  // Determine if message is a remote request frame.
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
  ////FimlerCAN////
  ////InicioenviarI2C////
  Wire.beginTransmission(0x08); // transmite para o dispositivo slave
  Wire.write(ECU.gear);
  Wire.write(0);// envia a mensagem
  Wire.write(ECU.cltc);
  Wire.write(0);
  Wire.endTransmission();  //para de transmitir
  ////FimlerI2C////
  delay(1);
}