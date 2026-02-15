#pragma once
#include <Arduino.h>

// --- Device Identity ---
// These match your specific request
#define DEV_ID          "CYURD130"
#define MQTT_SERVER     "sitebuilt.net"
#define MQTT_PORT       1884
#define MQTT_USER       "tim@sitebuilt.net"
#define MQTT_PASS       "geniot"

// --- Initial Connection Message ---
#define MSG_TIME_TOPIC   "time"
#define MSG_TIME_PAYLOAD "in mq.reconn->devid/time, <-/prg&/devtime"

// GADGET CONFIGURATION
#define SA_COUNT 2
/// ----temp1w_se gadget configuration ----
#define TW1_READ_INTERVAL 2000
#define TW1_COUNT 2



//----data structures for config and state
struct T1w_Config {
  uint8_t   gpio;
  uint8_t   sa;        // sensor/actuator id
  float     threshold;
  const char* name;    
  const char* val_of; // temp(F), current(A), setpt, relay 
  bool      rec;
  const char* pwd; // available to everybody, available by pwd
};

struct T1w_State {     
  uint8_t sa;
  float lastValue;
};

//----config ------
//{gpio, sa, threshold, name, rec, pwd }
// Using inline to allow definition in header (C++17)
inline const T1w_Config t1w_config[TW1_COUNT] = {
  {4, 0, 0.5, "Outside", "temp(F)", true, ""},
  {4, 1, 0.5, "Ari_room", "temp(F)", true, "duck"}
};


//-----(initial) state ------
//{sa, lastValue}
// Using inline to allow definition in header (C++17)
inline T1w_State t1w_state[TW1_COUNT] = {
  {0,  0.0 },
  {1,  0.0 }
};

