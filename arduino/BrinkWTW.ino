#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <LittleFS.h>
#ifndef WIFI_SSID
#define WIFI_SSID "your-ssid"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "your-password"
#endif
#ifdef USE_MQTT
#include <PubSubClient.h>

#ifndef MQTT_HOST
#define MQTT_HOST "localhost"
#endif

#ifndef MQTT_PORT
#define MQTT_PORT 1883
#endif

WiFiClient mqttWifiClient;
PubSubClient mqttClient(mqttWifiClient);
#endif

AsyncWebServer server(80);

#ifdef USE_MQTT
void initMqtt() {
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
}

void ensureMqtt() {
  if (!mqttClient.connected()) {
    mqttClient.connect("BrinkWTW");
  }
}
#endif

struct SwitchDef {
  const char *id;
  uint8_t pin;
};

SwitchDef switches[] = {
  {"relay9", 19},
  {"relay1", 27},
  {"relay2", 26},
  {"relay3", 33},
  {"relay4", 25},
  {"relay5", 14},
  {"relay6", 32},
  {"relay7", 23},
  {"relay8", 22},
};

void handleSwitch(AsyncWebServerRequest *request) {
  if (request->pathArg(0) == String()) {
    request->send(400, "text/plain", "No switch id");
    return;
  }
  String id = request->pathArg(0);
  if (!request->hasParam("turn")) {
    request->send(400, "text/plain", "No turn arg");
    return;
  }
  String turn = request->getParam("turn")->value();
  bool state = turn.equalsIgnoreCase("on") || turn == "1";
  for (auto &sw : switches) {
    if (id == sw.id) {
      digitalWrite(sw.pin, state ? HIGH : LOW);
#ifdef USE_MQTT
      ensureMqtt();
      String topic = String("brink/") + id;
      mqttClient.publish(topic.c_str(), state ? "1" : "0");
#endif
      request->send(200, "text/plain", "OK");
      return;
    }
  }
  request->send(404, "text/plain", "Switch not found");
}

void setup() {
  Serial.begin(115200);
  if (!LittleFS.begin()) {
    Serial.println("LittleFS mount failed");
  }

  // Setup GPIOs for switches
  for (auto &sw : switches) {
    pinMode(sw.pin, OUTPUT);
    digitalWrite(sw.pin, LOW);
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }
  Serial.println();
  Serial.println(WiFi.localIP());

#ifdef USE_MQTT
  initMqtt();
  ensureMqtt();
#endif

  server.on("/sensors", HTTP_GET, [](AsyncWebServerRequest *req){
    // Minimal stub response similar to ESPHome web_server
    String json = "{\"sensors\":[{\"name\":\"WiFi RSSI\",\"value\":" + String(WiFi.RSSI()) + "}]}";
    req->send(200, "application/json", json);
  });

  server.on("/network", HTTP_GET, [](AsyncWebServerRequest *req){
    IPAddress ip = WiFi.localIP();
    IPAddress gw = WiFi.gatewayIP();
    IPAddress subnet = WiFi.subnetMask();
    String json = "{\"ip\":\"" + ip.toString() + "\",\"gateway\":\"" + gw.toString() + "\",\"subnet\":\"" + subnet.toString() + "\"}";
    req->send(200, "application/json", json);
  });

  server.on("/network", HTTP_POST, [](AsyncWebServerRequest *req){
    req->send(200, "text/plain", "OK");
  });

  server.on("^/switch/([A-Za-z0-9_]+)$", HTTP_GET, handleSwitch);

  server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

  server.begin();
}

void loop() {
#ifdef USE_MQTT
  ensureMqtt();
  mqttClient.loop();
#endif
}
