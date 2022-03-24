# Water chilled Raspberry Pi controller

This is the code to control the chiller in my water chilled Raspberry Pi project. It cycles the peltier on and off to keep the water just above the dew point. This pervents condensation.



The following hardware was used:


Arduino Nano - The brains.

DHT-11 Digital temp & humidity sensor - readings are used to calculate dew point.

TMP36 Analog temp sensor - used to measure the temperature of the water.

SSD1306 OLED Display - Displays the current temp, target temp and ambient temp.

5v Relay module - Switches the peltier on and off.

Proto board - For soldering everything to.

Various wires and pin headers - for connecting everything.


