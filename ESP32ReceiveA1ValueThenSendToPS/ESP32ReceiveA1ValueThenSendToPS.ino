#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


const char *ssid = "ADT";
const char *password = "adt@12345";
const char *server_address = "192.168.1.2";  // Replace with your Python server's IP address
const int serverPort = 5000;  // Replace with the port on which your Python server is listening
WiFiServer server(80);


void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 18, 19);  // Initialize Serial2

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    delay(2000);
    Serial.println("test 1 passed");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (Serial2.available() > 0) {
    String receivedData = Serial2.readStringUntil('\n');
        Serial.println("test 2 passed");
            Serial.println(receivedData);


      if (receivedData.startsWith("Analog Value")) {
        int sensorValue = receivedData.substring(20).toInt();
        Serial.println("Sensor Value: " + String(sensorValue));

        // Send the sensor value to the HTTP server
        sendSensorValueToHTTPServer(sensorValue);

        // Send the sensor value over WiFi
        sendSensorValueOverWiFi(sensorValue);

      
        delay(1000);
      }
  
   }
}

void sendSensorValueToHTTPServer(int sensorValue) {
  HTTPClient http;
  String url = "/update";
  String postData = "value=" + String(sensorValue);

  http.begin(server_address, serverPort, url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST(postData);

  if (httpCode == 200) {
        Serial.println("TESTING 3.. POST Sensor METHOD REQ");
    Serial.println("HTTP POST request successful");
    Serial.println(http.getString());
  } else {
    Serial.println("HTTP POST request failed");
    Serial.println("HTTP Code: " + String(httpCode));
  }


  http.end();
  delay(1000);
}

void sendSensorValueOverWiFi(int value) {
  WiFiClient client;
  String url = "/update?value=" + String(value);

  if (client.connect(server_address, serverPort)) {
        Serial.println("TESTING 4.. GET Sensor METHOD REQ ");
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + server_address + "\r\n" +
                 "Connection: close\r\n\r\n");

    Serial.println("GET " + url + " HTTP/1.1\r\n" +
                   "Host: " + server_address + "\r\n" +
                   "Connection: close\r\n\r\n");

    delay(1000);

    Serial.println("Request sent");

    while (client.connected()) {
      String line = client.readStringUntil('\n');
      Serial.println(line);
    }

    client.stop();
    Serial.println("Server disconnected");
  } else {
    Serial.println("Connection to server failed");
  }
}


