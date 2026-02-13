#pragma once
#include <Arduino.h>
#include <vector>
#include "Gadget.h"
#include "Config.h"
#include "temp1w_se.h"

// Factory function to create all gadgets
// Fully config-driven - main.cpp has no knowledge of specific gadget types
inline void configureGadgets(std::vector<Gadget*>& gadgets) {
  // Create gadgets based on config
  // This scales - just add more gadgets as needed
  gadgets.push_back(new T1w_Sensor());
}