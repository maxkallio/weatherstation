# System Architecture Overview

The following System Architecture Diagram provides an overview of the entire IoT weather station system, detailing each hardware and software component, their subsystems, hierarchical relationships, and communication protocols. This model facilitates understanding the system’s structure and interactions for maintainability and potential extension.

## 1. Embedded System (WeMos D1 Mini)
- **Hardware Components**: 
  - WeMos D1 Mini
  - Sensors: DHT11 (temperature/humidity), Photoresistor (light)
- **Software Components**: 
  - Arduino C/C++ code with libraries (WiFi, DHT)
- **Communication Protocols**: 
  - I2C (internal sensor data)
  - HTTP (for sending data to the server)

## 2. Webserver
- **PHP Module**: 
  - API endpoints and logic for processing incoming data
- **Communication Protocols**: 
  - HTTP over TCP/IP Port 80 for web communication

## 3. Frontend Subsystem
- **Components**: 
  - HTML, CSS, JavaScript files
  - Frontend PHP files
  - Frontend libraries
- **Communication Protocols**: 
  - HTTP (web content delivery to clients)

## 4. Backend Subsystem
- **Components**: 
  - API PHP files for data handling
  - Backend libraries
- **Communication Protocols**: 
  - HTTP
  - MySQL (data storage access)

## 5. Database System
- **Database**: 
  - MySQL database instance for storing sensor data
- **Communication Protocols**: 
  - MySQL on TCP/IP Port 3306

## 6. Docker Registry
- **Docker Images**: 
  - Stored Docker images for application deployment
- **External System**: 
  - Not hosted locally, used for version control and deployment

## 7. Docker Host
- **Components**: 
  - Docker containers running services
  - Docker network for virtual connections
- **Virtual Hardware Components**: 
  - Network and containerized applications
- **Communication Protocols**: 
  - Docker bridge network

## 8. Host System (Laptop/Server)
- **Components**: 
  - Docker containers

## 9. Mobile Device
- **Components**: 
  - Browser for frontend access
- **Communication Protocols**: 
  - HTTP/HTTPS for secure web access

## 10. Network Access Point
- **Role**: 
  - Provides Wi-Fi access for embedded device communication
- **Communication Protocols**: 
  - TCP/IP

## 11. GitLab Repository
- **Components**: 
  - Code repository for version control
  - Docker images

## 12. Internet/Intranet
- **Role**: 
  - Enables remote access to webserver and data

## 13. SSH-Tunnel
- **Role**: 
  - Secures remote management and debugging

## Diagram
![System Architecture](/assets/systemarch3.png)
## Legend
- **Arrows**: Indicate communication flow
- **Solid Lines**: Represent direct connections
## URL
[System Architecture on GitLab](https://xiinuuweepee24-iot-2024-2025-semester-1-individu-5c7dedc32e89e4.dev.hihva.nl/system_architecture/)

