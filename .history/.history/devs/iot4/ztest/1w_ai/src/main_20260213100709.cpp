#include <Arduino.h>
#include <vector>
#include "MqttManager.h"
#include "connWIFI.h" // Reuse existing WiFi wrapper
#include "Config.h"
#include "gadget.h"
#include "factory.h"

// Vector to hold all gadgets - populated by factory
std::vector<Gadget*> gadgets;


// --- Global Infrastructure ---
WiFiClient espClient;
PubSubClient client(espClient);
MqttManager mqtt(client, DEV_ID, MQTT_USER, MQTT_PASS);


// --- Callbacks ---

// 1. The Shim for PubSubClient
void globalMqttCallback(char* topic, byte* payload, unsigned int length) {
    mqtt.onMessage(topic, payload, length);
}

// 2. The App Logic / Router
void appMqttCallback(const String& topic, const String& payload) {
    Serial.printf("Pkt: -> %s %s\n", topic.c_str(), payload.c_str());

    // Iteration 1: Catch the Time Response
    if (topic == MSG_TIME_TOPIC) {
         Serial.println(">> Time Sync Received!");
         Serial.println(payload);
         return;
    }

    // Pass to gadgets
    for (auto& g : gadgets) {
        if (g->handleMqttMessage(topic, payload)) return;
    }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

      // 1. Connect WiFi
  if (!setupWIFI()) {
      Serial.println("WiFi Failed");
      // ESP.restart(); // Optional
  }

  // 2. Connect MQTT
  mqtt.begin(MQTT_SERVER, MQTT_PORT);
  mqtt.setCallback(appMqttCallback);
  client.setCallback(globalMqttCallback);
  mqtt.loop()
  delay(2000);
  Serial.println("Waiting for time sync...");
  // Configure all gadgets from factory (config-driven)
  configureGadgets(gadgets);
  
  // Call setup() on each gadget
  for (auto& g : gadgets) {
    g->setup();
  }
  Serial.println("Setup Complete, entering loop...");
  Serial.printf("Total Gadgets: %d\n", gadgets.size());  
}

void loop() {
   mqtt.loop();
  // Call loop() on each gadget
  for (auto& g : gadgets) {
    g->loop();
  }
}