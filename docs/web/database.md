# Weather Station Database

The database for the Weather Station project is designed to store sensor data, device states, and time logs. The structure supports multiple sensor types and is designed to be easily extendable for future sensor integrations. The database is normalized to eliminate redundancy and maintain data integrity.

## Database Schema

The schema for the database is created using MySQL Workbench and consists of the following tables:

- **Sensors**: Stores information about different sensors used in the weather station.
- **EnvironmentData**: Logs the readings from the sensors, including temperature, humidity, and light levels.
- **DeviceState**: Keeps track of the state of the device, including the status of LEDs and button presses.
- **TimeLogs**: Records formatted time for display purposes.
![Devices Table](/assets/db.png)
![Devices Table](/assets/db2.png)

