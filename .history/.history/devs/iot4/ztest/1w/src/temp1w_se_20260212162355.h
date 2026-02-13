#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>


struct Config {
  uint8_t   gpio;        // sensor/actuator id
};

struct Multi_Config {
  uint8_t   sa;        // sensor/actuator id
  float     threshold;
  const char* name;     // Optional: Label for logging
  bool     rec;
};