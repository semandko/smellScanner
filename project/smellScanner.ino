/***************************************************************************
  This is a 

  This sketch puts the sensor in color mode and reads the RGB and clear values.

  Designed specifically to work with the 


  Written by  for .
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/


#include "Adafruit_APDS9960.h"

//
bool initAPDS9960(void);
void getAPDS9960(void);
//


uint16_t r;
uint16_t g;
uint16_t b;
uint16_t c;
uint16_t luxVal;


Adafruit_APDS9960 apds;
bool isConfigApds;



//**************************************************************************
//**************************************************************************
//**************************************************************************
void setup() 
{
  
  Serial.begin(115200);
  Serial.println("setup: INFO: SERIAL=115200//");


  //Wire.begin();

  isConfigApds = false;
  isConfigApds = initAPDS9960();

}

void loop() 
{

  
  getAPDS9960();
  
}
//**************************************************************************
//**************************************************************************
//**************************************************************************


//**********************Framework***********************



bool initAPDS9960(void)
{
	Serial.println("setup: init apds...");
 
  if (!apds.begin())
  {
    Serial.println("failed to initialize device! Please check your wiring.");
    return false;
  }
  else
  {
    Serial.println("Device initialized!");
  }
  
  // configuration
  //
  //apds.setADCIntegrationTime(uint16_t iTimeMS); // defaul (ms) =  10 // 2.78ms = 1 cycle (low sensitivity) // 27.8ms = 10 cycles // 200ms = 72 cycles // 712ms = 256 cycles (max sensitivity) 
  //float iTimeMS = apds.getADCIntegrationTime();
  //apds.setADCGain(APDS9960_AGAIN_4X); // apds9960AGain_t: // APDS9960_AGAIN_1X // APDS9960_AGAIN_4X // APDS9960_AGAIN_16X // APDS9960_AGAIN_64X
  //apds9960AGain_t gain = apds.getADCGain();
  
  apds.enableColor(true); // enable color sensign mode
  return true;
}

void getAPDS9960()
{
  
  if (isConfigApds == true)
  {
    // wait for color data to be ready
    while (!apds.colorDataReady())
    {
      delay(5);
    }

    // get the data and print the different channels
    apds.getColorData(&r, &g, &b, &c);
  
    Serial.print("red: ");
    Serial.print(r);
  
    Serial.print("; green: ");
    Serial.print(g);
  
    Serial.print("; blue: ");
    Serial.print(b);
  
    Serial.print("; clear: ");
    Serial.println(c);
  
    delay(1000);
   }
  
}
