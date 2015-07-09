
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int speakerPin = 8;
unsigned long timeCurrent;
unsigned long timeMarkRssiMonitor;
unsigned long timeMarkSystem;
unsigned long timeMarkBeep;
boolean toggle;
int oldRssiValue;
float rssiPercent;
boolean beepAlarm;
int beepLevel;
int beepCount;
int cursorBeepCount;



byte happyface[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

byte sadface[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b01110,
  0b10001,
  0b00000
};

byte neutralface[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b01110,
  0b00000,
  0b00000
};

byte deadface[8] = {
  0b00000,
  0b00000,
  0b11011,
  0b00000,
  0b00000,
  0b01110,
  0b00000,
  0b00000
};

byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

void setup() {
  
  timeMarkRssiMonitor=0;
  timeMarkSystem=0;
  timeMarkBeep=0;
  cursorBeepCount=0;

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

  oldRssiValue=-255;
}

void beep(unsigned char delayms){
  beepOn();           // Almost any value can be used except 0 and 255
  delay(delayms);     // wait for a delayms ms
  beepOff();          // 0 turns it off
  delay(delayms);     // wait for a delayms ms   
}  

void beepOn(){
  analogWrite(speakerPin, 0);
}  

void beepOff(){
  analogWrite(speakerPin, 255);
}  

void loop() {
  
  timeCurrent = millis();

  // refresh RSSI values every 100ms
  if (timeCurrent > timeMarkRssiMonitor) {
    updateRssiMonitor();
    timeMarkRssiMonitor = timeCurrent + 100;
  }
  
  // Refresh heart beat every 750ms
  if (timeCurrent > timeMarkSystem) {
    updateSystem();
    timeMarkSystem = timeCurrent + 750;
  }
  
  // refresh beep every 50ms
  if (millis() > timeMarkBeep) {
    updateBeep();
    timeMarkBeep=millis()+50;
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


void updateBeep() {
  if (beepAlarm) {
    if (beepCount==beepLevel) {
      beepOn();
    } else {
      beepOff();
    }

    if (beepCount>0) {
      beepCount--;
    } else {
      beepCount=beepLevel;
    }   
  }
  
}

void setBeepAlarmOn(int bl) {
  if (bl!=beepLevel) { 
    beepLevel = bl;
    beepCount = bl;
    beepAlarm=true;
  }
}

void setBeepAlarmOff() {
  beepCount = 0;
  beepLevel = 0;
  beepAlarm=false;
  beepOff();
}


void updateRssiMonitor() {

  int rssiValue = analogRead(A0);

  if (rssiValue == oldRssiValue) {    
    return;
  }

  oldRssiValue = rssiValue;
  
  rssiPercent = map(rssiValue, 23, 881, 0, 100); // Adjust these values
  float rssiBar = map(rssiValue, 23, 881, 0, 10); // Adjust these values
  
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
