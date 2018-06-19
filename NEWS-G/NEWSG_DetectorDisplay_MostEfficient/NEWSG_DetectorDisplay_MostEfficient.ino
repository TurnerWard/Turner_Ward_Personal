#include "Laser.h"

Laser redlaser(5); // Initiates a red laser in the 5th arduino pin.

typedef struct Electron { // Creates an Electron struct.
  int rLocation;
  int thetaLocation;
  int energy;
};

typedef struct Alpha { // Creates an Alpha struct.
  int xLocation;
  int yLocation;
  int energy;
  int xMovement;
  int yMovement;
};

int numElectronLocationsInArray = 6;
Electron alphaElectrons[6]; // Creates an array of 6 electrons.
int alphaElectronLocation = 0;

Alpha alpha1; // Defines the alphas that will be moving within the detector.
Alpha alpha2;

void setup() {
  redlaser.init(); // Initiates the laser which also initiates the dac.
  initiateLaserForDetectorDisplay(); // Initates the laser settings for the detector.
  alpha1 = createNewAlpha(); // Initiates the alphas.
  alpha2 = createNewAlpha();
}

void loop() { 
  displayDetector(); // Displays the detector.

  alpha1 = computeNextAlphaLocation(alpha1); // Updates the alphas next locations.
  alpha2 = computeNextAlphaLocation(alpha2);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// HELPER FUNCTIONS ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

/* Electron generateElectron(int xLocation, int yLocation, int energyDeposited)

   Creates a new electron given the location and energy level you wish it to contain.

*/
Electron generateElectron(int xLocation, int yLocation, int energyDeposited) {
  Electron newElectron; // Creates a new electron using the electron struct.
  if(yLocation >= 0) // If in the upper two quadrants.
    newElectron = {sqrt(pow(xLocation, 2) + pow(yLocation, 2)), round( atan2 (yLocation, xLocation) * 180 / 3.14159265 ), energyDeposited}; // Can compute normally.
  else if(xLocation <=0 && yLocation <=0) // If in the bottom left quadrant.
    newElectron = {sqrt(pow(xLocation, 2) + pow(yLocation, 2)), 180+round( atan2 (abs(yLocation), abs(xLocation)) * 180 / 3.14159265 ), energyDeposited}; // Need to change computation.
  else // Otherwise in the bottom right quadrant.
    newElectron = {sqrt(pow(xLocation, 2) + pow(yLocation, 2)), 180+round( atan2 (-1*yLocation, -1*xLocation) * 180 / 3.14159265 ), energyDeposited}; // Need to change computation.
  
  return newElectron; // Returns the electron struct.
}

/* Alpha createNewAlpha()

   Creates a new Alpha particle with random properties.

*/
Alpha createNewAlpha() {
  int rStartLowerBounds = 2000; // The minimum radius value for which an alpha can be generated. Default is 2000.
  int rStartUpperBounds = 2048; // The maximum radius value for which an alpha can be generated. Default is 2048.
  int energyLowerBounds = 150; // The minimum energy for which an alpha can be generated in keV. Default is 150.
  int energyUpperBounds = 250; // The maximum energy for which an alpha can be generated in keV. Default is 250.
  int movementBounds = 25; // The largest step an alpha can move after appearing. Default is 25.
  int lowestSpeed = 20; // The lowest speed at which an alpha can travel. Default is 20.

  const int maxSINCOSvalue = 16384;

  randomSeed(0); // Randomizes the seed.

  int rCurrent = random(rStartLowerBounds, rStartUpperBounds); // Randomly returns the radius value for the alpha to start at between 1028 and 2048.
  int thetaCurrent = random(0, 360); // Randomly returns the theta value for the alpha to start at.
  int xCurrent = rCurrent * COS(thetaCurrent) / maxSINCOSvalue; // Converts from polar to cartesian where the movement of alpha particles are more easily replicated.
  int yCurrent = rCurrent * SIN(thetaCurrent) / maxSINCOSvalue; // Converts from polar to cartesian where the movement of alpha particles are more easily replicated.
  int energyCurrent = random(energyLowerBounds, energyUpperBounds); // Generates the starting energy value of the alpha.
  int xMovement = random(-movementBounds, movementBounds);;
  int yMovement = random(-movementBounds, movementBounds);;

  while (sqrt(pow(xMovement, 2) + pow(yMovement, 2)) < lowestSpeed) {
    xMovement = random(-movementBounds, movementBounds); // Generates a random value for x between the bounds.
    yMovement = random(-movementBounds, movementBounds); // Generates a random value for y between the bounds.
  }

  Alpha newAlpha = {xCurrent, yCurrent, energyCurrent, xMovement, yMovement}; // Creates the new alpha with the new values.
  return newAlpha; // Returns this new alpha.
}

/* Electron computeNextElectronLocation(Electron electron)

   Determines the next location for which a given electron will move depending on its current location.

*/
Electron computeNextElectronLocation(Electron electron) {
  int rStrongElectricField = 100; // The radius for which the electrons get pulled directly into the center of the detector. Default is 100.
  int rMovementLowerBounds = 40; // The smallest step an electron can move after appearing. Default is 10.
  int rMovementUpperBounds = 60; // The largest step an electron can move after appearing. Default is 50.
  int thetaMovementBounds = 5; // The maximum angle in degrees for which the electron can move in one step. Default is 5.
  int energyChangeLowerBounds = 1; // The minimum energy that an electron can lose in 1 interaction in keV. Default is 1.
  int energyChangeUpperBounds = 5; // The maximum energy that an electron can lose in 1 interaction in keV. Default is 5.

  const int maxSINCOSvalue = 16384;

  randomSeed(0); // Randomizes the seed.
  int rCurrent = electron.rLocation; // Saves the passed in rLocation, thetaLocation, and energy values that are pointed to from the electron pointer.
  int thetaCurrent = electron.thetaLocation;
  int energyCurrent = electron.energy;
  
  if (rCurrent > 0 && energyCurrent > 0) {
    if (rCurrent > rStrongElectricField && energyCurrent > 0) { // While outside the inner radius where the electric field is weaker and the electron still has energy.
      int rMovement = random(rMovementLowerBounds, rMovementUpperBounds); // Generates a random value between the declared values for the r change.
      int thetaMovement = random(-thetaMovementBounds, thetaMovementBounds); // Generates a random value between the declared values for the theta change.
      int energyChange = random(energyChangeLowerBounds, energyChangeUpperBounds); // Generates a random value between the declared values for the energy change.
      rCurrent = rCurrent - rMovement; // Updates the current radius value.
      thetaCurrent = thetaCurrent + thetaMovement; // Updates the current theta value.
      energyCurrent = energyCurrent - energyChange; // Updates the current energy value.

      simulateTrack(energyCurrent, rCurrent * COS(thetaCurrent) / maxSINCOSvalue, rCurrent * SIN(thetaCurrent) / maxSINCOSvalue); // Displays the electron.
      Electron newElectron = {rCurrent, thetaCurrent, energyCurrent}; // Creates the new elecron with the new values.
      return newElectron; // Returns this new electron.
    }
    else if (rCurrent <= rStrongElectricField && 0 < rCurrent && energyCurrent > 0) { // While the electron is within the strong electric field range and has energy.
      int rMovement = random(rMovementLowerBounds, rMovementUpperBounds); // Generates a random value between the declared values for the r change.
      int energyChange = random(energyChangeLowerBounds, energyChangeUpperBounds); // Generates a random value between the declared values for the energy change.
      rCurrent = rCurrent - rMovement; // Updates the current radius value.
      energyCurrent = energyCurrent - energyChange; // Updates the current energy value.

      simulateTrack(energyCurrent, rCurrent * COS(thetaCurrent) / maxSINCOSvalue, rCurrent * SIN(thetaCurrent) / maxSINCOSvalue); // Displays the electron.
      Electron newElectron = {rCurrent, thetaCurrent, energyCurrent}; // Creates the new elecron with the new values.
      return newElectron; // Returns this new electron.
    }
  }
  else {
    Electron newElectron = {0, 0, 0}; // Effectively destroys the electron and holds it at (0,0) with no energy.
    //Electron newElectron = createNewElectron();
    return newElectron;
  }
}

/* Alpha computeNextAlphaLocation(Alpha alpha)

   Determines the next location for which a given alpha will move along with determining if an electron should appear and controlling said electrons.

*/
Alpha computeNextAlphaLocation(Alpha alpha) {
  const int maximumRadius = 2000;
  int energyChangeLowerBounds = 60;
  int energyChangeUpperBounds = 100;

  randomSeed(0); // Randomizes the seed.

  int xCurrent = alpha.xLocation + alpha.xMovement; // Saves the passed in xLocation, yLocation, and energy values.
  int yCurrent = alpha.yLocation + alpha.yMovement;
  int energyCurrent = alpha.energy;

  if (sqrt(pow(xCurrent, 2) + pow(yCurrent, 2)) < maximumRadius && energyCurrent > 0) {
    int energyChange = random(energyChangeLowerBounds, energyChangeUpperBounds);
    if (random(0, 101) > 95) { // Results in a 5% chance to generate an electron with each step.
      alphaElectrons[alphaElectronLocation] = generateElectron(xCurrent, yCurrent, energyChange);
      energyCurrent = energyCurrent - energyChange / 4; // Lowers the energy of the alpha.
      alphaElectronLocation++;
      if (alphaElectronLocation == numElectronLocationsInArray) { // If the array is filled rotate around and start filling it again.
        alphaElectronLocation = 0;
      }
    }

    for(int loc = 0; loc < numElectronLocationsInArray; loc++) {
      alphaElectrons[loc] = computeNextElectronLocation(alphaElectrons[loc]); // Computes and moves the electon through its step.
    }
    
    simulateTrack(energyCurrent, xCurrent, yCurrent); // Updates the alphas position.
    Alpha newAlpha = {xCurrent, yCurrent, energyCurrent, alpha.xMovement, alpha.yMovement}; // Creates the new alpha with the new values.
    return newAlpha; // Returns this new electron.
  }
  else {
    Alpha newAlpha = createNewAlpha();
    return newAlpha;
  }
}

/* void displayDetector()

   Displays the detector using a circle and a rod with the maximum resolution.

*/
void displayDetector() {
  int circleStepSize = 20; // Changes the step size as the for loop passes through the circle. Smaller values create more perfect circles. Default is 15.

  redlaser.off(); // Makes sure the laser is off. This was needed to avoid fencing at this point.
  const int smallestSINCOSvalue = 8; // The value needed to convert from the larger scale of max value being 16384 to the smaller more appropriate scale of 2048.
  redlaser.sendto(SIN(0) / smallestSINCOSvalue, COS(0) / smallestSINCOSvalue); // Moves the laser to the correct starting location.
  redlaser.on(); // Now since we are in the correct location we can turn the laser on.

  for (int r = 0; r <= 360; r += circleStepSize) // Rotates through the angles of the circle with the provided step size.
  {
    redlaser.sendto(SIN(r) / smallestSINCOSvalue, COS(r) / smallestSINCOSvalue); // Displays the circle.
  }

  redlaser.off(); // After we have displayed the laser we can turn off the laser.
  redlaser.sendto(0, -2048); // Moves to the bottom portion of the rod.
  redlaser.on();  // Turns on the laser.
  redlaser.sendto(0, 0); // Moves to the center of the circle .
  redlaser.off(); // Turns the laser off.
}

/* void simulateTrack(int energy, int xMiddlePoint, int yMiddlePoint)

   Simulates an electron track using a disk where the energy is represented as the size of the disk and the middle points of the disk can be specified.

*/
void simulateTrack(int energy, int xMiddlePoint, int yMiddlePoint) {
  redlaser.sendto(SIN(0)*energy / 16384 + xMiddlePoint, COS(0)*energy / 16384 + yMiddlePoint);
  redlaser.on();
  for (int r = 0; r <= 360; r += 60) {
    redlaser.sendto(SIN(r)*energy / 16384 + xMiddlePoint, COS(r)*energy / 16384 + yMiddlePoint);
  }
  redlaser.off();
}

/* initiateLaserForDetectorDisplay()

   Initiates all the laser settings needed for scalled and offsets.

*/
void initiateLaserForDetectorDisplay() {
  redlaser.setScale(1); // Sets the scaling to be normal (no multiplication factor applied to the image) for the red laser.
  redlaser.setOffset(2048, 2048); // Sets the offset for the laser so the circles center corresponds to (0,0) for the red laser.
}
