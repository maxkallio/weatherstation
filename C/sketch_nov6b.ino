// Author: Max
// Purpose: This program captures data from a DHT11 sensor, displays temperature, humidity, and time on an LCD,
// simulates temperature variations based on light readings from a photoresistor, and sends this data to a backend server.
// License: MIT

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// Pin definitions
const int BUTTON_PIN = D4;
const int DHT_SENSOR_PIN = D5;
const int LDR_PIN = A0;
const int LED_RED_PIN = D7;
const int LED_BLUE_PIN = D3;

// DHT sensor initialization
#define DHT_SENSOR_TYPE DHT11
DHT dhtSensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

// LCD initialization
LiquidCrystal_I2C lcdDisplay(0x27, 16, 2);

// NTP client setup
WiFiUDP ntpUDPClient;
NTPClient ntpTimeClient(ntpUDPClient, "pool.ntp.org", 3600, 60000);

// WiFi credentials
const char* wifiSSID = "iotroam";
const char* wifiPassword = "dMOE4fnBKv7";

// Server address for data transmission
const char* serverAddress = "10.21.51.75";

void setup() {
    Serial.begin(9600); // Start serial communication for debugging
    WiFi.begin(wifiSSID, wifiPassword); // Connect to WiFi network

    // Wait until connected to WiFi
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("WiFi connected successfully.");

    dhtSensor.begin(); // Initialize DHT sensor
    lcdDisplay.init(); // Initialize the LCD
    lcdDisplay.backlight(); // Activate LCD backlight

    ntpTimeClient.begin(); // Start NTP client to fetch current time
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Configure button pin with internal pull-up
    pinMode(LED_RED_PIN, OUTPUT); // Set RED LED pin as output
    pinMode(LED_BLUE_PIN, OUTPUT); // Set BLUE LED pin as output
}

void loop() {
    // Update time from NTP server
    ntpTimeClient.update();
    String currentTime = ntpTimeClient.getFormattedTime();

    // Retrieve temperature and humidity from DHT sensor
    float measuredTemperature = dhtSensor.readTemperature();
    float measuredHumidity = dhtSensor.readHumidity();

    // Adjust temperature based on light level from LDR
    int lightLevel = analogRead(LDR_PIN);
    if (lightLevel > 700) { // High light indicates warmth
        measuredTemperature += 5;
    } else if (lightLevel < 300) { // Low light indicates cold
        measuredTemperature -= 5;
    }

    // Check button press status
    if (digitalRead(BUTTON_PIN) == LOW) {
        // Show temperature and humidity on LCD when button is pressed
        lcdDisplay.clear();
        lcdDisplay.setCursor(0, 0);
        lcdDisplay.print("Temp: ");
        lcdDisplay.print(measuredTemperature);
        lcdDisplay.print(" C");

        lcdDisplay.setCursor(0, 1);
        lcdDisplay.print("Humidity: ");
        lcdDisplay.print(measuredHumidity);
        lcdDisplay.print(" %");

        // Send data to server if values are valid
        if (!isnan(measuredTemperature) && !isnan(measuredHumidity)) {
            transmitDataToServer(measuredTemperature, measuredHumidity, lightLevel, currentTime);
        }
    } else {
        // Display current time when button is not pressed
        lcdDisplay.clear();
        lcdDisplay.setCursor(0, 0);
        lcdDisplay.print("Time:");
        lcdDisplay.setCursor(0, 1);
        lcdDisplay.print(currentTime);
    }

    // Control LED indicators based on temperature
    if (!isnan(measuredTemperature)) {
        if (measuredTemperature > 0) {
            digitalWrite(LED_RED_PIN, HIGH);  // Turn on RED LED for positive temperature
            digitalWrite(LED_BLUE_PIN, LOW);   // Turn off BLUE LED
        } else {
            digitalWrite(LED_RED_PIN, LOW);    // Turn off RED LED
            digitalWrite(LED_BLUE_PIN, HIGH);  // Turn on BLUE LED for negative temperature
        }
    }

    delay(100); // Short delay for stability
}

// Function to transmit sensor data to the server
// Parameters: temperature, humidity, light level, current time
void transmitDataToServer(float temperature, float humidity, int lightLevel, String currentTime) {
    WiFiClient client;

    Serial.println("Connecting to server...");

    if (client.connect(serverAddress, 80)) {
        // JSON object for data transmission
        StaticJsonDocument<200> jsonDocument;
        jsonDocument["sensor_name"] = "DHT11"; // Sensor identification
        jsonDocument["temperature"] = temperature;
        jsonDocument["humidity"] = humidity;
        jsonDocument["light_level"] = lightLevel;
        jsonDocument["formatted_time"] = currentTime;

        // Create Convert JSON object to String
        String jsonData;
        serializeJson(jsonDocument, jsonData);

        // Send HTTP POST request with sensor data
        client.println("POST /data_handler.php HTTP/1.1");
        client.println("Host: 10.21.50.164"); // Update with your server's IP
        client.println("Content-Type: application/json");
        client.print("Content-Length: ");
        client.println(jsonData.length());
        client.println();
        client.println(jsonData);

        Serial.println("Data transmitted: " + jsonData);

        // Read server response
        while (client.available()) {
            String responseLine = client.readStringUntil('\n');
            Serial.println(responseLine);
        }

        client.stop(); // Close the connection
    } else {
        Serial.println("Failed to connect to server.");
    }
}