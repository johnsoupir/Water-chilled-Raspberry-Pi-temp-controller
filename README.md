# Water-chilled-Raspberry-Pi-temp-controller

This is the code to control the chiller in my water chilled Raspberry Pi project. It cycles the peltier on and off to keep the water just above the dew point. This pervents condensation.
I do not claim that this is the best of most efficient code, but hey, it worked! Feel free to improve this code in any way you wish. If you do, please include a link to the original project so people can find the rest of the information about this project. 

The following hardware was used:

Arduino Nano - The brains
DHT-11 Digital temp & humidity sensor - readings are used to calculate dew point.
TMP36 Analog temp sensor - used to measure the temperature of the water.
SSD1306 OLED Display - Displays the current temp, target temp and ambient temp.
5v Relay module - Switches the peltier on and off.
Proto board - For soldering everything to.
Various wires and pin headers - for connecting everything.


If you somehow came here without seeing the video, it can be found on my YouTube channel: https://www.youtube.com/channel/UCjEhg90nUsyxH6BprUDUW3w

