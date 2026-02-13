#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

struct Config {
  uint8_t   gpio;
  uint8_t   sa;        // sensor/actuator id
  float     threshold;
  const char* name;// Optional: Label for logging
  bool     rec;
  const char* pwd;

struct State {     
  uint8_t sa;
  const char* name;
  float lastValue;
};