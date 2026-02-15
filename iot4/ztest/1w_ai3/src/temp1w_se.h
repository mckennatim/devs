#pragma once
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Gadget.h"
#include "Config.h"

#define MAX_SENSORS_PER_BUS 8  // Safety limit per bus

struct T1w_Bus {
  OneWire wire;
  DallasTemperature sensors;
  DeviceAddress addresses[MAX_SENSORS_PER_BUS];  // Fixed max per bus
  uint8_t count;  // Actual discovered sensors on this bus
  
  T1w_Bus(uint8_t gpio) : wire(gpio), sensors(&wire), count(0) {}
};

class T1w_Sensor : public Gadget {
private:
  T1w_Bus* busses[TW1_GPIO_COUNT];
  unsigned long lastReadTime;

public:
  T1w_Sensor() : lastReadTime(0) {
    for (uint8_t i = 0; i < TW1_GPIO_COUNT; i++) {
      busses[i] = new T1w_Bus(t1w_gpio_pins[i]);
    }
  }

  ~T1w_Sensor() {
    for (uint8_t i = 0; i < TW1_GPIO_COUNT; i++) {
      delete busses[i];
    }
  }

  void setup() override {
    Serial.println("\nDS18B20 Temperature Monitor");
    Serial.println("=====================================");
    
    // Discover actual devices on each bus
    for (uint8_t b = 0; b < TW1_GPIO_COUNT; b++) {
      busses[b]->sensors.begin();
      uint8_t found = busses[b]->sensors.getDeviceCount();
      
      Serial.printf("Bus %d (GPIO %d): Found %d devices\n", 
                    b, t1w_gpio_pins[b], found);
      
      // Store addresses of discovered devices
      for (uint8_t j = 0; j < found && j < MAX_SENSORS_PER_BUS; j++) {
        if (busses[b]->sensors.getAddress(busses[b]->addresses[j], j)) {
          busses[b]->count++;
        }
      }
      Serial.printf("  -> Registered %d devices\n", busses[b]->count);
    }
    
    // Validate config matches discovered sensors
    for (uint8_t i = 0; i < TW1_SENSOR_COUNT; i++) {
      uint8_t b = t1w_config[i].bus_idx;
      if (b >= TW1_GPIO_COUNT) {
        Serial.printf("ERROR: Sensor %s references invalid bus %d\n", 
                     t1w_config[i].name, b);
      }
    }
    Serial.println("Setup complete.");
  }

  void loop() override {
    unsigned long currentTime = millis();
    if (currentTime - lastReadTime < TW1_READ_INTERVAL) return;
    lastReadTime = currentTime;

    // Read all configured sensors
    for (uint8_t b = 0; b < TW1_GPIO_COUNT; b++) {
      if (busses[b]->count == 0) continue;  // Skip empty busses
      
      busses[b]->sensors.requestTemperatures();
      
      // Match config sensors to their physical device on this bus
      uint8_t busDeviceIdx = 0;
      for (uint8_t i = 0; i < TW1_SENSOR_COUNT; i++) {
        if (t1w_config[i].bus_idx != b) continue;
        
        // Critical: Don't read beyond discovered sensors
        if (busDeviceIdx >= busses[b]->count) {
          Serial.printf("WARNING: %s configured but device not found on bus %d\n",
                       t1w_config[i].name, b);
          continue;
        }
        
        float tempF = busses[b]->sensors.getTempF(busses[b]->addresses[busDeviceIdx]);
        busDeviceIdx++;
        
        if (tempF != DEVICE_DISCONNECTED_F) {
          float delta = abs(tempF - t1w_state[t1w_config[i].sa].lastValue);
          t1w_state[t1w_config[i].sa].lastValue = tempF;
          
          if (delta >= t1w_config[i].threshold) {
            Serial.printf("%s: %.2f°F (delta: %.2f)\n", 
                         t1w_config[i].name, tempF, delta);
            // TODO: MQTT publish here
          }
        } else {
          Serial.printf("%s: Error reading\n", t1w_config[i].name);
        }
      }
    }
  }
};