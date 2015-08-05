/*
 * Arduino RSSI Monitor
 * 
 * Configuration routine
 * 
 * Author: Denys Sene <denys.sene@gmail.com>
 */

void configurationMenu() {
  lcd.clear();
  lcd.setCursor(0,0);

  lcd.print("VRX=On / VTX=Off");
  delay(1000);

  lcd.setCursor(0,1);
  lcd.print("Min Value: ");

  char s[5];
  config_st cfg = {};
  int b = digitalRead(pushButtonPin);
  float voltage=0.0;
  while (b==0) {
    b=digitalRead(pushButtonPin);
    cfg.minValue=analogRead(A0);
    voltage = cfg.minValue * (5.0f / 1024);
    delay(100);
    lcd.setCursor(11,1);
    lcd.print(voltage);
    lcd.print("V");
    lcd.setCursor(15,1);
  }

  lcd.clear();
  lcd.print("VRX=On / VTX=On");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Max Value:");

  b = digitalRead(pushButtonPin);
  while (b==0) {
    b=digitalRead(pushButtonPin);
    cfg.maxValue=analogRead(A0);
    voltage = cfg.maxValue * (5.0f / 1024);
    delay(100);
    lcd.setCursor(11,1);
    lcd.print(voltage);
    lcd.print("V");
    lcd.setCursor(15,1);
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Saving values...");

  EEPROM.put(0,cfg);

  setup();

  timeMarkRssiMonitor=0;
  timeMarkSystem=0;
  timeMarkBeep=0;
  isConfigMenu=false;
  
}

