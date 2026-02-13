#pragma once
#include <Arduino.h>
#include <vector>
#include "Config.h"
#include "MqttManager.h"
#include "Gadget.h"


inline void configureGadgets(std::vector<Gadget*>& gadgets, MqttManager* mqtt) {
// create an array of gadgets (so fat this project has one gadget, but this scales)
  gadgets.push_back(new T1w_Sensor());
}