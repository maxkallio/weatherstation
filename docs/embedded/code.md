# Embedded code

Weather Station Code
This program is designed for an embedded weather station that utilizes a DHT11 sensor to measure temperature and humidity. The data collected is displayed on an LCD screen and on website.

General Overview
The code is structured to perform the following main tasks:

Sensor Initialization: The program initializes the DHT11 sensor for temperature and humidity readings, the LCD for display purposes, and an NTP client to fetch the current time.

Wi-Fi Connection: It connects to a specified Wi-Fi network to enable communication with the backend server.

Data Collection and Display: In the main loop, the program continuously reads data from the DHT11 sensor and the LDR. Based on the button press, it either displays the temperature and humidity or the current time on the LCD.

Data Transmission: When valid sensor data is available, the program constructs a JSON object with the sensor readings and sends it to a specified server endpoint using an HTTP POST request.

Detailed Breakdown
Pin Definitions: The code begins with defining constants for various pins used in the project. For example, BUTTON_PIN, DHT_PIN, and PHOTORESISTOR_PIN are defined for better readability and maintainability.

Sensor Setup: The DHT sensor is initialized with its type and pin, allowing for accurate readings of temperature and humidity.

LCD and NTP Client Initialization: The LCD is set up to provide a user interface, while the NTP client is initialized to retrieve the current time from an internet time server.

Main Loop:

The loop continuously checks for button presses. If the button is pressed, it displays the temperature and humidity on the LCD.
If the button is not pressed, it shows the current time.
The temperature is adjusted based on the light level detected by the LDR, simulating environmental changes.
Data Transmission: The sendDataToServer function is responsible for constructing a JSON object with the sensor readings and sending it to the backend server. It handles the HTTP connection and ensures that the data is formatted correctly for transmission.

Conclusion
This program effectively integrates various components to create a functional weather station. It demonstrates the ability to read sensor data, display it on an LCD, and communicate with a server, all of which are essential for IoT applications.

