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

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// HELPER FUNCTIONS ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

/* void 
 * 
 */
void electronLineTrack() {
  int rStrongElectricField = 100; // The radius for which the electrons get pulled directly into the center of the detector. Default is 100.
  int rStartLowerBounds = 1028; // The closest value for which electrons can appear to the middle of the detector. Default is 1028.
  int rStartUpperBounds = 2048; // The furthest value for which electrons can appear to the middle of the detector. Default is 2048 which is the maximum value.
  int rMovementLowerBounds = 100; // The smallest step an electron can move after appearing. Default is 100.
  int rMovementUpperBounds = 500; // The largest step an electron can move after appearing. Default is 500.
  int thetaMovementBounds = 5; // The maximum angle in degrees for which the electron can move in one step. Default is 5.

  int maxSINCOSvalue = 16384; // The maximum value that SIN and COS can return. This value is used for scaling purposes. It shouldnt be changed. If it is for
                              // some reason the default value is 16384.
  
  laser.off(); // Makes sure the laser is off.
  randomSeed(0); // Randomizes the seed.
  
  int rCurrent = random(rStartLowerBounds,rStartUpperBounds); // Randomly returns the radius value for the electron to start at between 1028 and 2048.
  int thetaCurrent = random(0,360); // Randomly returns the theta value for the electron to start at.

  laser.sendto(rCurrent*COS(thetaCurrent)/maxSINCOSvalue, rCurrent*SIN(thetaCurrent)/maxSINCOSvalue); // Converts from polar to cartesian and moves the laser to the start position.
  laser.on(); // Turns the laser on.

  while(rCurrent > rStrongElectricField) { // While outside the inner radius where the electric field is weaker.                
    int rMovement = random(rMovementLowerBounds,rMovementUpperBounds); // Generates a random value between 100 and 500 for the r distance that the electron will move in this step. 
    int thetaMovement = random(-thetaMovementBounds,thetaMovementBounds); // Generates a random value between -35 and 35 for the theta direction that the electron will move in this step.
    rCurrent = rCurrent - rMovement; // Updates the current r value.
    thetaCurrent = thetaCurrent + thetaMovement; // Updates the current theta value.
    laser.sendto(rCurrent*COS(thetaCurrent)/maxSINCOSvalue, rCurrent*SIN(thetaCurrent)/maxSINCOSvalue); // Converts from polar to cartesian and moves the laser to the newly updates position.
  }
  laser.sendto(0, 0); // If the electron is within 100 pixels of the center of the detector the electric field value is so strong it will be pulled directily towards the center.
  laser.off(); // Turns off the laser as the pathing is now complete.
}

void electronDiskTrack() {
  laser.off(); // Makes sure the laser is off.
  randomSeed(0); // Randomizes the seed.
  
  int rCurrent = random(1028, 2048); // Randomly returns the radius value for the electron to start at between 1028 and 2048.
  int thetaCurrent = random(0, 360); // Randomly returns the theta value for the electron to start at.

  simulateTrack(100, rStart*COS(thetaStart)/16384, rStart*SIN(thetaStart)/16384); // Converts from polar to cartesian and creates the electron at the start position.
  laser.on(); // Turns the laser on.

  while(rCurrent > 100) { // While outside the inner radius where the electric field is weaker.                         
    displayDetector();
    int rMovement = random(10,50); // Generates a random value between 100 and 500 for the r distance that the electron will move in this step. 
    int thetaMovement = random(-5,5); // Generates a random value between -35 and 35 for the theta direction that the electron will move in this step.
    rCurrent = rCurrent - rMovement; // Updates the current r value.
    thetaCurrent = thetaCurrent + thetaMovement; // Updates the current theta value.
    simulateTrack(100, rCurrent*COS(thetaCurrent)/16384, rCurrent*SIN(thetaCurrent)/16384); // Converts from polar to cartesian and creates the electron at the start position.
  }

  while (rCurrent <= 100 && 0 < rCurrent) {
    displayDetector();
    rCurrent = rCurrent - 20;
    simulateTrack(100, rCurrent*COS(thetaCurrent)/16384, rCurrent*SIN(thetaCurrent)/16384); // If the electron is within 100 pixels of the center of the detector the electric field value is so strong it will be pulled directily towards the center.
  }
  laser.off(); // Turns off the laser as the pathing is now complete.
}

void alphaTrack(int energy, int xStartLocation, int yStartLocation, int xEndLocation, int yEndLocation) {
  
}

void displayDetector() {
  laser.off();
  const int scale = 8; // The value needed to convert from the larger scale of max value being 16384 to the smaller more appropriate scale of 2048.
  laser.sendto(SIN(0)/scale, COS(0)/scale); // Moves the laser to the correct starting location.
  laser.on(); // Now since we are in the correct location we can turn the laser on.
  
  for (int r = 0;r<=360;r+=15) // Rotates through the angles of the circle with the provided step size.
  {    
    laser.sendto(SIN(r)/scale, COS(r)/scale); // Displays the circle.
  }
  laser.off(); // After we have displayed the laser we can turn off the laser.

  laser.sendto(0, -2048); laser.on(); laser.sendto(0,0); laser.off(); // Displays the rod.
}

void simulateTrack(int energy, int xMiddlePoint, int yMiddlePoint) {
  laser.sendto(SIN(0)*energy/16384 + xMiddlePoint, COS(0)*energy/16384 + yMiddlePoint);
  laser.on();
  for (int r = 0;r<=360;r+=45) { 
    laser.sendto(SIN(r)*energy/16384 + xMiddlePoint, COS(r)*energy/16384 + yMiddlePoint);
  }
  laser.off();
}

void initiateLaserForDetectorDisplay() {
  laser.setScale(1); // Sets the scaling to be normal (no multiplication factor applied to the image).
  laser.setOffset(2048,2048); // Sets the offset for the laser so the circles center corresponds to (0,0).
}
