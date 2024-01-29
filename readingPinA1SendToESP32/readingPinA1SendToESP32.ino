#include <SoftwareSerial.h>

SoftwareSerial Serial2(18, 19); // RX, TX
const int analogPin = A1;

void setup() {
  Serial.begin(9600); // ESP32 serial
  Serial2.begin(9600); // arduino serial 
  
}

void loop() {
  // Read the analog value from pin A1
  int sensorValue = analogRead(analogPin);

  // SENSOR VALUE ON ESP32 SERIAL 115200
  Serial.print("Analog Value on A1: ");
  Serial.println(sensorValue);

  // SENSOR VALUE ON ARDUINO SERIAL 9600
  Serial2.print("SensorValue");
  Serial2.println(sensorValue);

  delay(3000); // Add a delay if needed

   if (Serial.available() > 0) {
    String receivedData = Serial2.readStringUntil('\n');
    Serial2.println(receivedData);

    
    }
  }


