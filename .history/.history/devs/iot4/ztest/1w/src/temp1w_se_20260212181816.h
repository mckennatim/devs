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
// set up a oneWire instances to communicate with any OneWire devices
// pass oneWire references to DallasTemperature library
// create arrays to hold device addresses

public:
  T1w_Sensor() {
    // Constructor can be used to initialize members if needed
  }

  void setup(){
    Serial.println("\n\nDS18B20 Temperature Monitor");
    Serial.println("=====================================");
    // start up the library for each onewire instance
  }

  void loop() {
    // Main logic to read sensors and publish MQTT messages
  }

  void handleMqttMessage(const String& subtopic, const String& payload) {
    // Handle incoming MQTT messages if needed
  } 

  void load()
};

