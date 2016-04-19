/*
 * Arduino RSSI Monitor
 * 
 * Beep related functions
 * 
 * Author: Denys Sene <denys.sene@gmail.com>
 */

void beep(unsigned char delayms){
  beepOn();           
  delay(delayms);     
  beepOff();          
  delay(delayms);
}  

void beepOn(){
  digitalWrite(speakerPin, HIGH);
}  

void beepOff(){
  digitalWrite(speakerPin, LOW);
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

