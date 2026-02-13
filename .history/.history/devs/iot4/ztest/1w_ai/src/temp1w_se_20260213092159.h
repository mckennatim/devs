#pragma once
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Gadget.h"
#include "Config.h"  // Get type definitions and config arrays

//-----class ------
class T1w_Sensor : public Gadget {
private:
  OneWire oneWire;
  DallasTemperature sensors;
  DeviceAddress deviceAddresses[2];
  unsigned long lastReadTime;
  const unsigned long readInterval = 2000; // Read every 2 seconds
  
  const T1w_Config* config;
  T1w_State* state;
  int sensorCount;

public:
  T1w_Sensor() : oneWire(4), sensors(&oneWire), lastReadTime(0) {
    // Constructor
  }

  void setup() override {
    Serial.println("\n\nDS18B20 Temperature Monitor");
    Serial.println("=====================================");
    
    // Access config and state from Config.h
    config = t1w_config;
    state = t1w_state;
    sensorCount = 2; // From config array size
    
    // Start the DallasTemperature library
    sensors.begin();
    
    // Discover devices
    int deviceCount = sensors.getDeviceCount();
    Serial.print("Found ");
    Serial.print(deviceCount);
    Serial.println(" devices.");
    
    // Get addresses for each device
    for (int i = 0; i < deviceCount && i < sensorCount; i++) {
      if (sensors.getAddress(deviceAddresses[i], i)) {
        Serial.print("Device ");
        Serial.print(i);
        Serial.print(" (");
        Serial.print(config[i].name);
        Serial.print(") Address: ");
        for (uint8_t j = 0; j < 8; j++) {
          if (deviceAddresses[i][j] < 16) Serial.print("0");
          Serial.print(deviceAddresses[i][j], HEX);
        }
        Serial.println();
      }
    }
    Serial.println("Setup complete.");
  }

  void loop() override {
    unsigned long currentTime = millis();
    
    // Read sensors at specified interval
    if (currentTime - lastReadTime >= readInterval) {
      lastReadTime = currentTime;
      
      sensors.requestTemperatures();
      
      for (int i = 0; i < sensorCount; i++) {
        float tempC = sensors.getTempF(deviceAddresses[i]);
        
        if (tempC != DEVICE_DISCONNECTED_C) {
          float delta = abs(tempC - state[i].lastValue);
          
          // Only log if change exceeds threshold
          if (delta >= config[i].threshold) {
            Serial.print(config[i].name);
            Serial.print(": ");
            Serial.print(tempC);
            Serial.print("°C (delta: ");
            Serial.print(delta);
            Serial.println("°C)");
            
            state[i].lastValue = tempC;
          }
        } else {
          Serial.print(config[i].name);
          Serial.println(": Error reading temperature");
        }
      }
    }
  }

  // No MQTT handling - using base class default (returns false)
};

