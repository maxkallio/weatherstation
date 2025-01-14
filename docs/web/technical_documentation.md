# API Reference

This document provides detailed information about the REST API endpoints available in the Weather Station project. Each endpoint is described with its URL, request method, expected input, and output.

## Endpoints

### GET /sensors
- **Description**: Retrieves all sensor data.
- **Request Method**: GET
- **Response**:
  - **Status Code**: 200 OK
  - **Body**: JSON array of sensor objects
  - **Example**:
    ```json
    [
      {
        "sensor_id": 1,
        "sensor_name": "Temperature Sensor",
        "sensor_type": "temperature"
      },
      {
        "sensor_id": 2,
        "sensor_name": "Humidity Sensor",
        "sensor_type": "humidity"
      }
    ]
    ```
- **Response Image**: ![Devices Table](/assets/getsens.png)

### POST /sensors
- **Description**: Adds new sensor data.
- **Request Method**: POST
- **Request Body**:
  - **Content-Type**: application/json
  - **Example**:
    ```json
    {
      "sensor_name": "Light Sensor",
      "sensor_type": "light"
    }
    ```
- **Response**:
  - **Status Code**: 201 Created
  - **Body**: JSON object with success message and sensor ID
  - **Example**:
    ```json
    {
      "success": "Sensor successfully added.",
      "sensor_id": 3
    }
    ```
- **Request Image**: ![Devices Table](/assets/postsens.png)
- **Response Image**: ![Devices Table](/assets/resp.png)

### GET /sensor/{id}
- **Description**: Retrieves data for a specific sensor by ID.
- **Request Method**: GET
- **Parameters**:
  - `id`: The ID of the sensor to retrieve.
- **Response**:
  - **Status Code**: 200 OK
  - **Body**: JSON object of the sensor data
  - **Example**:
    ```json
    {
      "sensor_id": 1,
      "sensor_name": "Temperature Sensor",
      "sensor_type": "temperature"
    }
    ```
- **Response Image**: ![Devices Table](/assets/getsensid.png)

### PUT /sensor/{id}
- **Description**: Updates data for a specific sensor by ID.
- **Request Method**: PUT
- **Parameters**:
  - `id`: The ID of the sensor to update.
- **Request Body**:
  - **Content-Type**: application/json
  - **Example**:
    ```json
    {
      "sensor_name": "Updated Sensor Name",
      "sensor_type": "updated_type"
    }
    ```
- **Response**:
  - **Status Code**: 200 OK
  - **Body**: JSON object with success message
  - **Example**:
    ```json
    {
      "success": "Sensor data successfully updated."
    }
    ```
- **Request Image**: ![Devices Table](/assets/putsensid.png)
- **Response Image**: ![Devices Table](/assets/resp1.png)

### DELETE /sensor/{id}
- **Description**: Deletes sensor data by ID.
- **Request Method**: DELETE
- **Parameters**:
  - `id`: The ID of the sensor to delete.
- **Response**:
  - **Status Code**: 200 OK
  - **Body**: JSON object with success message
  - **Example**:
    ```json
    {
      "success": "Sensor data successfully deleted."
    }
    ```
- **Response Image**: ![Devices Table](/assets/deletesens.png)

## Technology Overview

This project uses a combination of technologies to design, build, and deploy the Weather Station web application:

- **Backend**: PHP is used for server-side scripting, handling API requests, and interacting with the MySQL database.
- **Database**: MySQL (MariaDB) is used to store sensor data. The database is managed through Docker, ensuring a consistent environment across different setups.
- **Frontend**: HTML, CSS, and JavaScript are used to create the user interface, allowing users to view sensor data in real-time.
- **Deployment**: Docker is used to containerize the application, making it easy to deploy and manage.

## Design Considerations

The design of the Weather Station web application takes into account the following:

- **User Experience**: The interface is designed to be intuitive and easy to navigate, providing users with real-time updates on sensor data.
- **Scalability**: The application is built to handle an increasing number of sensors and data points, ensuring it can grow with user needs.
- **Security**: Measures are in place to protect user data and ensure secure communication between the client and server.

This documentation aims to provide a comprehensive overview of the API and the technologies used in the project, making it easier for developers to understand and contribute to the project.