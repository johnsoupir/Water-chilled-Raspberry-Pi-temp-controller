double dewPoint(double celsius, double humidity)
{
  // (1) Saturation Vapor Pressure = ESGG(T)
  double RATIO = 373.15 / (273.15 + celsius);
  double RHS = -7.90298 * (RATIO - 1);
  RHS += 5.02808 * log10(RATIO);
  RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1 / RATIO ))) - 1) ;
  RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
  RHS += log10(1013.246);

  // factor -3 is to adjust units - Vapor Pressure SVP * humidity
  double VP = pow(10, RHS - 3) * humidity;

  // (2) DEWPOINT = F(Vapor Pressure)
  double T = log(VP / 0.61078); // temp var
  return (241.88 * T) / (17.558 - T);
}



char SerialInput;


#include <TMP36.h>
#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTTYPE DHT11 // DHT 11
#define DHTPIN 2 //DHT Sensor pin
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 



DHT dht(DHTPIN, DHTTYPE);
TMP36 myTMP36(A0, 5.0); //pin and voltage

int target = 1;
int chiller = 3;
int chillerState = 0;
int dew;
int displayTarget;


void setup() {
  Serial.begin(9600);
  Serial.println("Chill Pi CONTROL UNIT STARTING...");
  dht.begin();
  pinMode(chiller, OUTPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
      Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  
}


void loop() {
  float h = dht.readHumidity(); //reading humidity
  float t = dht.readTemperature(); //reading temp in C
  float f = dht.readTemperature(true); //reading temp in F

  //If reading fails try again.
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);
  float hiDegC = dht.convertFtoC(hi);

  Serial.print("Ambient Temp and Humidity");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hiDegC);
  Serial.print(" *C ");
  Serial.print(hi);
  Serial.print(" *F ");
  Serial.print("Dew Point (*C): ");
  Serial.println(dewPoint(t, h));

  
  float celsius = myTMP36.getTempC(); 
  float fahrenheit = myTMP36.getTempF(); 
  Serial.print("Reservoir Temperature:");
  Serial.print("Celsius: ");
  Serial.print(celsius);
  Serial.print(" Fahrenheit: ");
  Serial.println(fahrenheit);
  delay(500);
if ((dewPoint(t,h)) + target > (celsius)){
    digitalWrite(chiller,LOW);
    chillerState = 0;
  } else{
    digitalWrite(chiller,HIGH);
    chillerState = 1;
    }

  displayTarget = (dewPoint(t,h)) + target;
  Serial.print("**TARGET TEMP**  ");
  Serial.println(displayTarget);








if (Serial.available()){
    SerialInput=Serial.read();
    if(SerialInput=='I'){
      target=Serial.parseInt();
      //((dewPoint(t,h)) + target = (displayTarget));
      //Serial.println("TARGET TEMP SET TO");
      //Serial.print(displayTarget);
    }
    }

display.clearDisplay();
display.setTextSize(1.5);      // Normal 1:1 pixel scale
display.setTextColor(WHITE); // Draw white text
display.setCursor(0, 5);     // Start at top-left corner
display.print("Target: ");
display.println(displayTarget);

display.setTextSize(1.5);      // Normal 1:1 pixel scale
display.setTextColor(WHITE); // Draw white text
display.setCursor(0, 15);     // Start at top-left corner
display.print("Res: ");
display.println(celsius);

display.setTextSize(1.5);      // Normal 1:1 pixel scale
display.setTextColor(WHITE); // Draw white text
display.setCursor(0, 25);     // Start at top-left corner
display.print("Ambient: ");
display.println(t);

if (chillerState == HIGH) {
   display.setTextSize(1.5);      // Normal 1:1 pixel scale
   display.setTextColor(WHITE); // Draw white text
   display.setCursor(0, 35);     // Start at top-left corner
   display.print("Chiller: ON ");
   } 
if (chillerState == LOW) {
   display.setTextSize(1.5);      // Normal 1:1 pixel scale
   display.setTextColor(WHITE); // Draw white text
   display.setCursor(0, 35);     // Start at top-left corner
   display.print("Chiller: OFF ");
   } 


display.setTextSize(1.5);      // Normal 1:1 pixel scale
display.setTextColor(WHITE); // Draw white text
display.setCursor(0, 45);     // Start at top-left corner
display.println(chillerState);

display.display();



    
}




  


