#include "Fenix_Racing.h"
#include "Arduino.h"



void armazenarBytes(int valor, byte *dataArray, int startIndex) {
dataArray[startIndex] = highByte(valor);
dataArray[startIndex + 1] = lowByte(valor);
}