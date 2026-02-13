#include <Arduino.h>
#include <vector>
#include "gadget.h"
#include "factory.h"

// Vector to hold all gadgets - populated by factory
std::vector<Gadget*> gadgets;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Configure all gadgets from factory (config-driven)
  configureGadgets(gadgets);
  
  // Call setup() on each gadget
  for (auto& g : gadgets) {
    g->setup();
  }
}

void loop() {
  // Call loop() on each gadget
  for (auto& g : gadgets) {
    g->loop();
  }
}