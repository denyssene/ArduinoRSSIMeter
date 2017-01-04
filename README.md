# Arduino RSSI Meter

RSSI meter for FPV Ground Stations.

* LCD: I2C - try your own LCD library that works for you
* Pin D12: Config Button
* Pin D8: Piezzo Buzzer Signal
* Pin A0: RSSI from Video RX

Please, see the schema below.

<h3>Configuring</h3>

With the config button, you don't to look for the voltages in RSSI and change in the source code.

Press the button in D12 for 1 second to enter in configuration mode.
- Step 1 - Set the minimum value. It's when your is VRX is On and your VTX is Off. RSSI Meter will show a value comming from your VRX meaning your 0% signal. Press buton to save.
- Step 2 - Set the maximum value. Now your VRX and your VTX must be turned On and close to each other. The value is shown in LCD and this is your 100% RSSI signal. Press button again to save.

The values are saved in EEPROM. You will need to enter in config again only if you replace your VRX or start using another type of antenna.

Please, feel free to suggest any improvements.

denys.sene@gmail.com
<p>
<img src="ArduinoRSSIMeter_bb.png">
</p>
