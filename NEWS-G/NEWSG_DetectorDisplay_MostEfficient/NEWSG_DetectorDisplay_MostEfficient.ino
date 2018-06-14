#include "Laser.h"

Laser laser(5);

unsigned long currentMillis; // Can run for ~50 days.
unsigned long nextEvent; // Can run for ~50 days.

void setup() {
  laser.init(); // Initiates the laser which also initiates the dac.
  initiateLaserForDetectorDisplay(); // Initates the laser settings for the detector.
}

void loop() {

  displayDetector();
  
  currentMillis = millis();
  if(nextEvent < currentMillis) {
    //electronLineTrack();   
    electronDiskTrack();
    nextEvent = millis() + random(500, 3000);
  }

}
