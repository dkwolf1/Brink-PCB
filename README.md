# Brink-PCB
This PCB connects the Brink Renovent and Elan systems.
A web interface and MQTT support are under development.
This project integrates with ESPHome and works well—see [`Wtw.yaml`](Wtw.yaml) for configuration.

## Firmware options

You can either flash the device using ESPHome or compile the Arduino sketch
yourself. The ESPHome configuration is provided in [`Wtw.yaml`](Wtw.yaml). If you
prefer the Arduino IDE, follow the steps below to build the sketch in
[`arduino/BrinkWTW.ino`](arduino/BrinkWTW.ino).

## Compiling the Arduino sketch

1. Install the required libraries in the Arduino IDE using the Library Manager:
   - **ESPAsyncWebServer**
   - **AsyncTCP**
   - **PubSubClient** (only needed when MQTT is enabled)
2. Open `arduino/BrinkWTW.ino` in the Arduino IDE.
3. Select an ESP32 board (for example, **ESP32 Dev Module**) and upload the
   sketch to your device.

Before compiling, edit `BrinkWTW.ino` to set your WiFi credentials:

```cpp
#define WIFI_SSID "your-ssid"
#define WIFI_PASSWORD "your-password"
```
The sketch connects to this network at startup.

### Enabling MQTT

To compile the sketch with MQTT support, define the `USE_MQTT` flag. The
simplest way in the Arduino IDE is to add `#define USE_MQTT` near the top of
`BrinkWTW.ino` before compiling. When the flag is omitted, the sketch is built
without the MQTT client, and no additional libraries are required.

## Web interface

The `web` folder contains a small HTML interface. When using ESPHome, the
files can be uploaded via the dashboard. For the Arduino sketch, upload the
contents of the `web` directory to LittleFS using the [ESP32 LittleFS
plugin](https://github.com/lorol/LITTLEFS) before flashing. Once the ESP32
boots, browse to the device IP address to control the ventilation system.

![Schematic](Schematic.png)

![PCB](PCB.png)
