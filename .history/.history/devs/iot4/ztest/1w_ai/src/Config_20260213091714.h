#pragma once
#include <Arduino.h>

//----data structures for config and state
struct T1w_Config {
  uint8_t   gpio;
  uint8_t   sa;        // sensor/actuator id
  float     threshold;
  const char* name;    // Optional: Label for logging
  bool      rec;
  const char* pwd;
};

struct T1w_State {     
  uint8_t sa;
  const char* name;
  float lastValue;
};

//----config ------
//{gpio, sa, threshold, name, rec, pwd }
// Using inline to allow definition in header (C++17)
inline const T1w_Config t1w_config[2] = {
  {4, 0, 1.5, "temp_out", true, ""},
  {4, 1, 1.5, "temp_ari", true, "duck"}
};

//-----(initial) state ------
//{sa, name, lastValue}
// Using inline to allow definition in header (C++17)
inline T1w_State t1w_state[2] = {
  {0, "temp_out", 0.0 },
  {1, "temp_ari", 0.0 }
};

