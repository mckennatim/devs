#pragma once
#include <Arduino.h>

class Gadget {
public:
    virtual ~Gadget() {}
    virtual void setup() = 0;
    virtual void loop() = 0;
    virtual bool handleMqttMessage(const String& subtopic, const String& payload) {
        return false; 
    }
    virtual void load() {
      //For loading into a factory or registry
    }
};