#include <NMEAGPS.h>
#include <SoftwareSerial.h>

uint32_t const GPS_TIMEOUT = 120000;

uint8_t const GPS_PIN = 8;
SoftwareSerial gpsSerial(GPS_PIN, GPS_PIN);
NMEAGPS gps;
gps_fix gps_data;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(F("Begynner"));
  getPosition();
  if (gps_data.valid.location && gps_data.valid.status && gps_data.status >= gps_fix::STATUS_STD) {
    Serial.print(F("lat/lon: "));
    Serial.print(gps_data.latitudeL()/10000000.0, 6);
    Serial.print(F(","));
    Serial.println(gps_data.longitudeL()/10000000.0, 6);
  } else {
    Serial.println(F("No GPS fix"));
  }

  Serial.println(F("Slutter"));
  delay(1000);
}

void getPosition() {
  //Clear previous data
  memset(&gps_data, 0, sizeof(gps_data));
  gps.statistics.init();

  //Turn on GPS
  //digitalWrite(SW_GND_PIN, HIGH);

  unsigned long startTime = millis();
  int valid = 0;
  while (millis() - startTime < GPS_TIMEOUT && valid < 10) {
    if (gps.available(gpsSerial)) {
      gps_data = gps.read();
      if (gps_data.valid.location && gps_data.valid.status && gps_data.status >= gps_fix::STATUS_STD) {
        valid++;
      }
      if (gps_data.valid.satellites) {
        Serial.print(F("Satellites: "));
        Serial.println(gps_data.satellites);
      }
      Serial.print("Number of valid reads: ");
      Serial.println(valid);
      Serial.print("Timeout left: ");
      Serial.println(millis() - startTime);
    }
  }

  if (gps.statistics.ok == 0)
    Serial.println(F("No GPS data received, check wiring"));
}


