#include <Arduino.h>
#include conf.h
#include gadget.h 

//code to create gadgets that are specified don conf.h and sensors as needed, and factories to load them
  // 3. Setup Gadgets (Factory)
configureGadgets(gadgets, &mqtt); 

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Only call setup() on the created objects
  for (auto& g : gadgets) g->setup();
}

void loop() {
  // Only call loop() on the created objects
  for (auto& g : gadgets) g->loop();
}