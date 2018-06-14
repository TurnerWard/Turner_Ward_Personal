#include "Laser.h"

Laser redlaser(5); // Initiates a red laser in the 5th arduino pin.
//Laser greenlaser(3); // Initiates a green laser in the 3rd arduino pin.

unsigned long currentMillis; // Can run for ~50 days.
unsigned long nextEvent; // Can run for ~50 days.

void setup() {
  
  redlaser.init(); // Initiates the laser which also initiates the dac.
  initiateLaserForDetectorDisplay(); // Initates the laser settings for the detector.
}

void loop() {

  displayDetector(); // Displays the detector.
  
  currentMillis = millis(); // A timer.
  if(nextEvent < currentMillis) {
    //electronLineTrack();   
    electronDiskTrack();
    nextEvent = millis() + random(500, 3000);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// HELPER FUNCTIONS ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

/* void electronLineTrack()
 * 
 * Displays an electron track in the line style within the projected detector.
 * 
 */
void electronLineTrack() {
  int rStrongElectricField = 100; // The radius for which the electrons get pulled directly into the center of the detector. Default is 100.
  int rStartLowerBounds = 1028; // The closest value for which electrons can appear to the middle of the detector. Default is 1028.
  int rStartUpperBounds = 2048; // The furthest value for which electrons can appear to the middle of the detector. Default is 2048 which is the maximum value.
  int rMovementLowerBounds = 100; // The smallest step an electron can move after appearing. Default is 100.
  int rMovementUpperBounds = 500; // The largest step an electron can move after appearing. Default is 500.
  int thetaMovementBounds = 5; // The maximum angle in degrees for which the electron can move in one step. Default is 5.

  const int maxSINCOSvalue = 16384; // The maximum value that SIN and COS can return. This value is used for scaling purposes. It shouldnt be changed. If it is for
                                    // some reason the default value is 16384.
  
  redlaser.off(); // Makes sure the laser is off.
  randomSeed(0); // Randomizes the seed.
  
  int rCurrent = random(rStartLowerBounds,rStartUpperBounds); // Randomly returns the radius value for the electron to start at between 1028 and 2048.
  int thetaCurrent = random(0,360); // Randomly returns the theta value for the electron to start at.

  redlaser.sendto(rCurrent*COS(thetaCurrent)/maxSINCOSvalue, rCurrent*SIN(thetaCurrent)/maxSINCOSvalue); // Converts from polar to cartesian and moves the laser to the start position.
  redlaser.on(); // Turns the laser on.

  while(rCurrent > rStrongElectricField) { // While outside the inner radius where the electric field is weaker.                
    int rMovement = random(rMovementLowerBounds,rMovementUpperBounds); // Generates a random value between the range declared above for the r distance that the electron will 
                                                                       // move in this step. 
    int thetaMovement = random(-thetaMovementBounds,thetaMovementBounds); // Generates a random value between -5 and 5 for the theta direction that the electron will move in this step.
    rCurrent = rCurrent - rMovement; // Updates the current r value.
    thetaCurrent = thetaCurrent + thetaMovement; // Updates the current theta value.
    redlaser.sendto(rCurrent*COS(thetaCurrent)/maxSINCOSvalue, rCurrent*SIN(thetaCurrent)/maxSINCOSvalue); // Converts from polar to cartesian and moves the laser to the newly updates 
                                                                                                        // position.
  }
  redlaser.sendto(0, 0); // If the electron is within 100 pixels of the center of the detector the electric field value is so strong it will be pulled directily towards the center.
  redlaser.off(); // Turns off the laser as the pathing is now complete.
}

/* void electronDiskTrack()
 * 
 * Displays an electron track in the disk style within the projected detector. As the energy of the electron decreases the disk size of the electron decreases.
 * 
 */
void electronDiskTrack() {
  int rStrongElectricField = 100; // The radius for which the electrons get pulled directly into the center of the detector. Default is 100.
  int rStartLowerBounds = 1028; // The closest value for which electrons can appear to the middle of the detector. Default is 1028.
  int rStartUpperBounds = 2048; // The furthest value for which electrons can appear to the middle of the detector. Default is 2048 which is the maximum value.
  int rMovementLowerBounds = 10; // The smallest step an electron can move after appearing. Default is 100.
  int rMovementUpperBounds = 50; // The largest step an electron can move after appearing. Default is 500.
  int thetaMovementBounds = 5; // The maximum angle in degrees for which the electron can move in one step. Default is 5.
  int energyLowerBounds = 70; // The minimum energy for which an electron can be generated in keV. Default is 70.
  int energyUpperBounds = 200; // The maximum energy for which an electron can be generated in keV. Default is 200.
  int energyChangeLowerBounds = 1; // The minimum energy that an electron can lose in 1 interaction in keV. Default is 1.
  int energyChangeUpperBounds = 5; // The maximum energy that an electron can lose in 1 interaction in keV. Default is 5.

  const int maxSINCOSvalue = 16384; // The maximum value that SIN and COS can return. This value is used for scaling purposes. It shouldnt be changed. If it is for
                                    // some reason the default value is 16384.
                              
  redlaser.off(); // Makes sure the laser is off.
  randomSeed(0); // Randomizes the seed.
  
  int rCurrent = random(rStartLowerBounds, rStartUpperBounds); // Randomly returns the radius value for the electron to start at between 1028 and 2048.
  int thetaCurrent = random(0, 360); // Randomly returns the theta value for the electron to start at.
  int energyCurrent = random(energyLowerBounds,energyUpperBounds);
 
  simulateTrack(energyCurrent, rCurrent*COS(thetaCurrent)/maxSINCOSvalue, rCurrent*SIN(thetaCurrent)/maxSINCOSvalue); // Converts from polar to cartesian and creates the electron at the start 
                                                                                                              // position.
  redlaser.on(); // Turns the laser on.

  while(rCurrent > rStrongElectricField && energyCurrent > 0) { // While outside the inner radius where the electric field is weaker and the electron still has energy.
    displayDetector(); // Keeps the detector displayed as depending on the step size the detector can disappear when transversing within this function.
    int rMovement = random(rMovementLowerBounds,rMovementUpperBounds); // Generates a random value between the declared values for the r distance that the electron will move in 
                                                                       // this step. 
    int thetaMovement = random(-thetaMovementBounds,thetaMovementBounds); // Generates a random value between the declared values for the theta direction that the electron will 
                                                                          // move in this step.
    int energyChange = random(energyChangeLowerBounds,energyChangeUpperBounds); // Generates a random value between the declared values for the energy the electron loses in an 
                                                                                // interaction
    rCurrent = rCurrent - rMovement; // Updates the current radius value.
    thetaCurrent = thetaCurrent + thetaMovement; // Updates the current theta value.
    energyCurrent = energyCurrent - energyChange; // Updates the current energy value.
    simulateTrack(energyCurrent, rCurrent*COS(thetaCurrent)/maxSINCOSvalue, rCurrent*SIN(thetaCurrent)/maxSINCOSvalue); // Converts from polar to cartesian and creates the electron at 
                                                                                                                        // the start position.
  }

  while (rCurrent <= rStrongElectricField && 0 < rCurrent && energyCurrent > 0) { // While the electron is within the strong electric field range, the radius is larger then 0 and
                                                                                  // the electron has energy. 
    displayDetector(); // Keeps the detector displayed as depending on the step size the detector can disappear when transversing within this function.
    int rMovement = random(rMovementLowerBounds,rMovementUpperBounds); // Generates a random value between the declared values for the r distance that the electron will move in 
                                                                       // this step.
    int energyChange = random(energyChangeLowerBounds,energyChangeUpperBounds); // Generates a random value between the declared values for the energy the electron loses in an 
                                                                                // interaction
    rCurrent = rCurrent - rMovement; // Updates the current radius value.
    energyCurrent = energyCurrent - energyChange; // Updates the current energy value.
    simulateTrack(energyCurrent, rCurrent*COS(thetaCurrent)/maxSINCOSvalue, rCurrent*SIN(thetaCurrent)/maxSINCOSvalue); // If the electron is within 100 pixels of the center of the 
                                                                                                              // detector the electric field value is so strong it will be pulled 
                                                                                                              // directily towards the center.
  }
  redlaser.off(); // Turns off the laser as the pathing is now complete.
}

/* void displayDetector()
 * 
 * Displays the detector using a circle and a rod with the maximum resolution.
 * 
 */
void displayDetector() {
  int circleStepSize = 15; // Changes the step size as the for loop passes through the circle. Smaller values create more perfect circles. Default is 15.
  
  redlaser.off(); // Makes sure the laser is off. This was needed to avoid fencing at this point.
  const int maxSINCOSvalue = 8; // The value needed to convert from the larger scale of max value being 16384 to the smaller more appropriate scale of 2048.
  redlaser.sendto(SIN(0)/maxSINCOSvalue, COS(0)/maxSINCOSvalue); // Moves the laser to the correct starting location.
  redlaser.on(); // Now since we are in the correct location we can turn the laser on.
  
  for (int r = 0; r <= 360; r += circleStepSize) // Rotates through the angles of the circle with the provided step size.
  {    
    redlaser.sendto(SIN(r)/maxSINCOSvalue, COS(r)/maxSINCOSvalue); // Displays the circle.
  }
  
  redlaser.off(); // After we have displayed the laser we can turn off the laser.
  redlaser.sendto(0, -2048); // Moves to the bottom portion of the rod.
  redlaser.on();  // Turns on the laser.
  redlaser.sendto(0,0); // Moves to the center of the circle .
  redlaser.off(); // Turns the laser off.
}

/* void simulateTrack(int energy, int xMiddlePoint, int yMiddlePoint)
 * 
 * Simulates an electron track using a disk where the energy is represented as the size of the disk and the middle points of the disk can be specified.
 * 
 */
void simulateTrack(int energy, int xMiddlePoint, int yMiddlePoint) {
  redlaser.sendto(SIN(0)*energy/16384 + xMiddlePoint, COS(0)*energy/16384 + yMiddlePoint);
  redlaser.on();
  for (int r = 0;r<=360;r+=45) { 
    redlaser.sendto(SIN(r)*energy/16384 + xMiddlePoint, COS(r)*energy/16384 + yMiddlePoint);
  }
  redlaser.off();
}

/* initiateLaserForDetectorDisplay()
 * 
 * Initiates all the laser settings needed for scalled and offsets.
 * 
 */
void initiateLaserForDetectorDisplay() {
  redlaser.setScale(1); // Sets the scaling to be normal (no multiplication factor applied to the image) for the red laser.
  redlaser.setOffset(2048,2048); // Sets the offset for the laser so the circles center corresponds to (0,0) for the red laser.

  //greenlaser.setScale(1); // Sets the scaling to be normal (no multiplication factor applied to the image) for the green laser.
  //greenlaser.setOffset(2048,2048); // Sets the offset for the laser so the circles center corresponds to (0,0) for the green laser.
}
