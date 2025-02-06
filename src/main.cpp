#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <WiFi.h>
#define BMP085_ADDRESS 0x76
#include <SPI.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

const char* ssid = "Redmi Note 13 Pro 5G MAX";
const char* password = "dw7zwujfdy8kvcv";


Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi network
  // WiFi.begin(ssid, password);
  
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }

  // Print the IP address of the board
  // Serial.print("IP address: ");
  // Serial.println(WiFi.localIP());


  // Initialize the BMP180 sensor
  if (!bmp.begin(BMP085_ADDRESS)) {
      Serial.println("Could not find a valid BMP085 sensor, check wiring!");
      return;
  }
}

void loop() {
    // if (WiFi.status() == WL_CONNECTED) {
    //     HTTPClient http;

    //     // http.begin(serverName);
    //     http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    //     String postData = "sensor=ESP32&location=Salon&value1=22.5&value2=45.7&value3=1013.2";
    //     int httpResponseCode = http.POST(postData);

    //     if (httpResponseCode > 0) {
    //         String response = http.getString();
    //         Serial.println("Réponse serveur : " + response);
    //     } else {
    //         Serial.println("Erreur d'envoi HTTP");
    //         Serial.println(httpResponseCode);
    //     }

    //     http.end();
    // }

  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F;

  Serial.print("Temperature = ");
  Serial.print(temperature, 1);
  Serial.println(" °C");
  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");

  delay(1000);
}