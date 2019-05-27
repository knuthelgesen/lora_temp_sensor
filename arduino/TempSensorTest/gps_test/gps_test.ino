#include <gp20u7.h>

GP20U7 gps = GP20U7(Serial);

Geolocation currentLocation;

void setup() {
  gps.begin();
}

void loop() {
  if(gps.read()){
    currentLocation = gps.getGeolocation();
    Serial.println("Your current location is:");
    Serial.print("    Latitude: ");
    Serial.println(currentLocation.latitude,5);
    Serial.print("    Longitude: ");
    Serial.println(currentLocation.longitude,5);
    delay(1000); 
  }
}
