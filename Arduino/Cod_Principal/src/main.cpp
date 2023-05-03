#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;

long unsigned int rxId;
unsigned char len = 0;
byte rxBuf[8] = {1, 1, 1, 1, 1, 1, 1, 1};
byte data[8] = {1, 1, 1, 1, 1, 1, 1, 1}; byte datai[8] = {1, 1, 1, 1, 1, 1, 1, 1};
char msgString[128];
byte aa, b, c, d;
int pot1, pot2, pot3, pot4, pot5, ext, pressao, temp1, temp2, temp3, accx, accy, accz, gear, i, ii;
int cltf, cltc, sec, rpm, batt, tach;

int led_pin = 5;
#define CAN0_INT 2
MCP_CAN CAN0(53);

void setup(void)
{
  Serial.begin(115200);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 Initialized Successfully!");
  } else {
    Serial.println("Error Initializing MCP2515...");
  }
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input

}


void loop()
{
  ////ComSensores////
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  pot1 = analogRead(A0);
  pot2 = analogRead(A1);
  pot3 = analogRead(A2);
  pot4 = analogRead(A3);
  Serial.println(pot4);
  data[0] = highByte(pot1);
  data[1] = lowByte(pot1);
  data[2] = highByte(pot2);
  data[3] = lowByte(pot2);
  data[4] = highByte(pot3);
  data[5] = lowByte(pot3);
  data[6] = highByte(pot4);
  data[7] = lowByte(pot4);
  ////fimSensores////

  ////ComenviarCAN////
  byte sndStat = CAN0.sendMsgBuf(0x001, 0, 8, data);
  if (sndStat == CAN_OK) {
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }

  byte sndStat1 = CAN0.sendMsgBuf(0x002, 0, 8, datai);
  if (sndStat == CAN_OK) {
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }
  ////fimenviarCAN/////

  ////ComlerCAN////

  if (!digitalRead(CAN0_INT))                        // If CAN0_INT pin is low, read receive buffer
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)

    if ((rxId & 0x80000000) == 0x80000000) {   // Determine if ID is standard (11 bits) or extended (29 bits)
      sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    } else {
      sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);

      Serial.print(msgString);
    }
    if ((rxId & 0x40000000) == 0x40000000) {  // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } else {

      for (byte ii = 0; ii < len; ii++) {
        sprintf(msgString, " 0x%.2X", rxBuf[ii]);
        if ((rxId & 0x5F0) == 0x5F0) {
          aa = rxBuf[0];
          b = rxBuf[1];
          c = rxBuf[6];
          d = rxBuf[7];
          sec = aa * 256 + b;
          rpm = c * 256 + d;
          Serial.println(rpm);
        }

        tach = 19.152 * rpm + 10.662;
        analogWrite(led_pin, tach);


        if ((rxId & 0x5F2) == 0x5F2) {
          aa = rxBuf[6];
          b = rxBuf[7];
          cltf = (aa * 256 + b) / 10;
          cltc = (cltf - 32) * 0.55;
        }

        if ((rxId & 0x5F3) == 0x5F3) {
          aa = rxBuf[6];
          batt = (aa * 256 + b) / 10;
          Serial.print(cltc);
          Serial.print("OBAA");
          }

        if ((rxId & 0x611) == 0x611) {
          aa = rxBuf[6];
          gear = aa;
        }
      }
    }
  }

  ////ComenviarI2C////
  int bat = batt;
  Wire.beginTransmission(0x08); // transmite para o dispositivo slave
  Wire.write(gear);
  Wire.write(rpm);// envia a mensagem
  Wire.write(cltc);
  Wire.write(bat);
  Wire.endTransmission();  //para de transmitir
  ////fimlerI2C////

}