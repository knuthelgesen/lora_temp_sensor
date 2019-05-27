#include <OneWire.h>
#include <DallasTemperature.h>

//Data wire is plugged into Arduino port 2
#define ONE_WIRE_BUS 2
//Create OneWire instance to communicate with temperature sensor (any OneWire device)
OneWire oneWire(ONE_WIRE_BUS);
//Give the OneWire instance to DallasTemperature
DallasTemperature sensors(&oneWire);

void setup() {
  //Start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  //Start the temperature library
  sensors.begin();
  delay(1000); 
}

void loop() {
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus 
  /********************************************************************/
  Serial.print(" Requesting temperatures..."); 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  Serial.println("DONE"); 
  /********************************************************************/
  Serial.print("Temperature is: "); 
  Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?  
  // You can have more than one DS18B20 on the same bus.  
  // 0 refers to the first IC on the wire 
  delay(1000); 
}
