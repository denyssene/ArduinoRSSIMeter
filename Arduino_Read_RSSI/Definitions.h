/*
 * Arduino RSSI Monitor
 * 
 * Special definitions and
 * custom characters
 * 
 * Author: Denys Sene
 */


struct config_st {
  uint16_t minValue;
  uint16_t maxValue;
};

uint8_t happyface[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};


uint8_t sadface[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b01110,
  0b10001,
  0b00000
};


uint8_t neutralface[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b01110,
  0b00000,
  0b00000
};

uint8_t deadface[8] = {
  0b00000,
  0b00000,
  0b11011,
  0b00000,
  0b00000,
  0b01110,
  0b00000,
  0b00000
};


uint8_t heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};
