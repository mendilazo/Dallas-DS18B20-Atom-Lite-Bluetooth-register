// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#include <M5Atom.h>
#include "BluetoothSerial.h"

// Data wire is plugged into port 32 on M5stickC, 32 on M5StickCPlus, 26 on Atom
#define ONE_WIRE_BUS 26
// BT Parameters
#define BT_WAITTIME 30
#define BT_STARTFLAG 18
#define BT_ACK 19
#define BT_ABORD 27

BluetoothSerial SerialBT;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

//VariablesMax y Min
float maxTemp =-100;
float minTemp=100;
unsigned long tiempo1 = 0;
unsigned long tiempo2 = 0;

void setup(void)
{
   M5.begin();
   sensors.begin();
   tiempo1 = millis();
   Serial.begin(115200);
   // BT Name
   SerialBT.begin("Termometro");
    
}


void loop(void)
{ 
  sensors.requestTemperatures(); // Send the command to get temperatures
  float tempC = sensors.getTempCByIndex(0);
  
   if (tempC>maxTemp){maxTemp = tempC;}
   if (tempC<minTemp){minTemp = tempC;}
   
 M5.update();  // Lectura de estado pulsadores
   if (M5.Btn.wasPressed()) {  // Boton A
   maxTemp = tempC;
   minTemp = tempC;
    }
    
  tiempo2 = millis();
  if(tiempo2 > (tiempo1+3000)){  //Si ha pasado 3 segundo ejecuta el IF
  tiempo1 = millis();
  
   
  // Check if reading was successful
  if(tempC != DEVICE_DISCONNECTED_C) 
  {
    
    Serial.println(tempC);
    SerialBT.print(" Real ");
    SerialBT.print(tempC);
    SerialBT.print(" Max ");
    SerialBT.print(maxTemp);
    SerialBT.print(" Min ");
    SerialBT.println(minTemp); 
  } 
 
   }   
 
    } 
  
