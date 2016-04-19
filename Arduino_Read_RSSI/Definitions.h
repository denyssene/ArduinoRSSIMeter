/*
 * Arduino RSSI Monitor
 * 
 * Special definitions and
 * custom characters
 * 
 * Author: Denys Sene <denys.sene@gmail.com>
 */

/*
 * I2C LCD PCF8574T
 */
#define I2C_ADDR    0x27
#define BACKLIGHT_PIN  3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
#define  LED_OFF  1
#define  LED_ON  0

/*
 * Config structure to save in EEPROM
 */
struct config_st {
  uint16_t minValue;
  uint16_t maxValue;
};

/*
 * Custom chars
 * Happy face, sad face, Heart, etc
 */
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
