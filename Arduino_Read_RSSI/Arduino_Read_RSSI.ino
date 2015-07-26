/*
 * Arduino RSSI Monitor
 * 
 * Main file
 * 
 * Author: Denys Sene <denys.sene@gmail.com>
 */

#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Definitions.h"


LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// pinout definitions
int speakerPin = 8; // speaker pin
int pushButtonPin = 12; // push button pin

unsigned long currentTime;
unsigned long timeMarkRssiMonitor;
unsigned long timeMarkSystem;
unsigned long timeMarkBeep;
unsigned long timeButtonMark;
boolean toggle;
int oldRssiValue;
float rssiPercent;
boolean beepAlarm;
int beepLevel;
int beepCount;
int buttonPushedCount;
boolean isConfigMenu;
config_st myConfig;

void setup() {

  timeMarkRssiMonitor=0;
  timeMarkSystem=0;
  timeMarkBeep=0;
  isConfigMenu=false;
  oldRssiValue=-255;
  
  lcd.init();
  lcd.backlight();

  // create a new character
  lcd.createChar(5, happyface);
  lcd.createChar(6, neutralface);
  lcd.createChar(7, sadface);
  lcd.createChar(8, deadface);
  lcd.createChar(9, heart);

  lcd.setCursor(0,0);
  lcd.print("RSSI METER ");
  
  pinMode(speakerPin, OUTPUT);

  beep(50);
  beep(50);
  beep(200);
  
  EEPROM.get(0,myConfig);
 
}

void loop() {

  if (isConfigMenu) {
    configurationMenu();
  } else {
    // rssi monitor screen
    monitorLoop();
  }

}

void monitorLoop() {

  currentTime = millis();

  // is button pressed for more than a second?
  // go to config menu
  if (timeButtonMark<currentTime) {
    int v = digitalRead(pushButtonPin);
    if (v==1) {
      buttonPushedCount++;
    } else {
      buttonPushedCount=0;
    }
    if (buttonPushedCount>10) {
      isConfigMenu=true;
      buttonPushedCount=0;
    }
    timeButtonMark=currentTime+100;
  }


  // refresh RSSI values every 100ms
  if (currentTime > timeMarkRssiMonitor) {
    updateRssiMonitor();
    timeMarkRssiMonitor = currentTime + 100;
  }

  
  // Refresh heart beat every 750ms
  if (currentTime > timeMarkSystem) {
    updateSystem();
    timeMarkSystem = currentTime + 750;
  }


  // refresh beep every 50ms
  if (currentTime > timeMarkBeep) {
    updateBeep();
    timeMarkBeep=currentTime+50;
  }

}

void updateSystem() {
  lcd.setCursor(15,0);
  int h=5;
  // update face (
  if (rssiPercent>=25 && rssiPercent <50 ) {
    h=6; //not so happy face
  } else if (rssiPercent<25 && rssiPercent>=0){
    h=7; // sad face
  } else if (rssiPercent<0){
    h=8; // dead face
  } else {
    h=5; // happy face
  }
  
  // write face char
  lcd.setCursor(11,0);
  lcd.write(h);
  
  // update heart char
  lcd.setCursor(15,0);
  if (toggle) {
    lcd.write(9);
  } else {
    lcd.print(" ");
  }
  toggle = !toggle;
}


void updateRssiMonitor() {

  int rssiValue = analogRead(A0);

  if (rssiValue == oldRssiValue) {    
    return;
  }

  oldRssiValue = rssiValue;
  
  rssiPercent = map(rssiValue, myConfig.minValue, myConfig.maxValue, 0, 100); // Adjust these values
  float rssiBar = map(rssiValue, myConfig.minValue, myConfig.maxValue, 0, 10); // Adjust these values
  
  if (rssiPercent>=20 && rssiPercent<30) {
    setBeepAlarmOn(40);
  } else if (rssiPercent>=10 && rssiPercent<20) {
    setBeepAlarmOn(30);
  } else if (rssiPercent>=5 && rssiPercent<10) {
    setBeepAlarmOn(20);
  } else if (rssiPercent>=0 && rssiPercent<5) {
    setBeepAlarmOn(10);
  } else {
    setBeepAlarmOff();
  }  


  if (rssiPercent >= 0) {
    
    if (rssiPercent > 100)
      rssiPercent=100;
    
    if (rssiBar > 10)
      rssiBar = 10;
    
    if (rssiPercent>0) {
      for (int i=0;i<=rssiBar;i++) {
        lcd.setCursor(i,1);
        lcd.write(1023);
      }
    }

    int blank = rssiBar;
    if (rssiPercent>0)
      blank++;
    
    for (int i=blank;i<=10;i++) {
      lcd.setCursor(i,1);
      lcd.print("_");
    }
  
    lcd.setCursor(11,1);
    char buffer[50];
    sprintf(buffer, "%4d%%", (int)rssiPercent);
    lcd.print(buffer);
    
  } else { // rssi percent < 0
    lcd.setCursor(0,1);
    lcd.print("No Signal Detected!");
  }
  
}  
