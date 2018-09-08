# Arduino RSSI Meter

RSSI meter for FPV Ground Stations.

* LCD: I2C - try your own LCD library that works for you
* Pin D12: Config Button
* Pin D11: Piezzo Buzzer Signal
* Pin A0: RSSI from Video RX

Please, see the schema below.

<h3>Configuring</h3>

Press the button in D12 for 1 second to enter in configuration mode.
- Step 1 - Set the minimum voltage that means your VRX is on but is not receiving any signal. You do that by keeping the VRX on and your VTX Off. Usually the voltage will be something very low like 0.3V. A short press in the config button will save this value and go to the next step.
- Step 2 - Set the maximum voltage that represents 100% RSSI. Keep both VRX and TRX on and close to each other. The voltage shown in LCD  means 100% RSSI signal and is usually something like 3.3v. Short press the button again to save and return to the default screen.

The values are saved in EEPROM. You will need to enter in config again only if you replace your VRX or start using another type of antenna.

Please, feel free to suggest any improvements.

denys.sene@gmail.com
<p>
<img src="ArduinoRSSIMeter_bb.png">
</p>
