#pragma once
#include <Arduino.h>

// === Global Configuration ===
#define SA_COUNT 2              // Total sensors/actuators across ALL gadgets
#define TW1_READ_INTERVAL 2000  // How often to read (milliseconds)

// === T1w Gadget Configuration ===
#define TW1_GPIO_COUNT 1        // Number of OneWire busses
#define TW1_SENSOR_COUNT 2      // Total number of sensors

// GPIO pins for OneWire busses (one per bus)
// Example: {4} for single bus on GPIO 4
// Example: {4, 5} for two busses on GPIO 4 and 5
inline const uint8_t t1w_gpio_pins[TW1_GPIO_COUNT] = {4};

struct T1w_Config {
  uint8_t   bus_idx;    // Index into t1w_gpio_pins array (which bus)
  uint8_t   sa;         // Sensor/actuator ID
  float     threshold;  // Change threshold for reporting
  const char* name;    
  const char* val_of;   // "temp(F)", etc.
  bool      rec;        // Record this sensor?
  const char* pwd;      // Password protection
};

struct T1w_State {     
  uint8_t sa;
  float lastValue;
};

// Sensor configurations
inline const T1w_Config t1w_config[TW1_SENSOR_COUNT] = {
  // bus_idx, sa, threshold, name,       val_of,    rec,  pwd
  {0,        0,  0.5,       "Outside",   "temp(F)", true, ""},
  {0,        1,  0.5,       "Ari_room",  "temp(F)", true, "duck"}
};

// State array (indexed by sa)
inline T1w_State t1w_state[SA_COUNT] = {
  {0, 0.0},
  {1, 0.0}
};