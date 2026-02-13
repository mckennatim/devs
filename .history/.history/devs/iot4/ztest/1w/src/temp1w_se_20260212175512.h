#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//----data structures for config and state
struct T1w_Config {
  uint8_t   gpio;
  uint8_t   sa;        // sensor/actuator id
  float     threshold;
  const char* name;// Optional: Label for logging
  bool     rec;
  const char* pwd;
};

struct T1w_State {     
  uint8_t sa;
  const char* name;
  float lastValue;
};

//-----class ------
class T1w_Sensor {
private:
  OneWire* _oneWire;
  DallasTemperature* _sensors;
  T1w_Config _config;
  T1w_State _state;

void setup(){
  Serial.println("\n\nDS18B20 Temperature Monitor");
  Serial.println("=====================================");
}
