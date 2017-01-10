// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"
#include <Wire.h>

#define DHTPIN 2     // what digital pin we're connected to
#define TEMP 5
#define HUMID 10
#define ERROR_VAL 111

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
int request_val;
int i_t;
int i_h;
void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  //i2c
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(10000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C \n");
  i_t=t;
  i_h=h;
}
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  request_val=x;
}
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Serial.print("ardruino is requested \n "); // respond with message of 6 bytes
  if(request_val==TEMP)
  {
    Wire.write(i_t);
    Serial.print("sent temp :");
    Serial.print(i_t);
    Serial.print("\n");
    
    }
     else if(request_val==HUMID)
   {
    Wire.write(i_h);
    Serial.print("sent humid :");
    Serial.print(i_h);
    Serial.print("\n");    
    }
    else
    {
      Wire.write(ERROR_VAL);
     Serial.print("request only temp/humid \n");
    }
    
    }
  // as expected by master

