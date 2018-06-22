
#ifndef NEWSG_ELECTRONFUNCTIONS_H
#define NEWSG_ELECTRONFUNCTIONS_H

#include "NEWSG_CommonFunctions.h"

// Creates an Electron struct. An electron is made up of a radial location, and angular location, and an energy.
typedef struct Electron {
  int rLocation;
  int thetaLocation;
  int energy;
} Electron;

/* Electron generateElectron(int xLocation, int yLocation, int energyDeposited)

   Creates a new electron given the location and energy level you wish it to contain.

*/
Electron generateElectron(int xLocation, int yLocation, int energyDeposited) {
  Electron newElectron; // Creates a new electron using the electron struct.
  if (yLocation >= 0) // If in the upper two quadrants.
    newElectron = {int(sqrt(pow(xLocation, 2) + pow(yLocation, 2))), int(round( atan2 (yLocation, xLocation) * 180 / 3.14159265 )), energyDeposited}; // Can compute normally.
  else if (xLocation <= 0 && yLocation <= 0) // If in the bottom left quadrant.
    newElectron = {int(sqrt(pow(xLocation, 2) + pow(yLocation, 2))), int(180 + round( atan2 (abs(yLocation), abs(xLocation)) * 180 / 3.14159265 )), energyDeposited};
  else // Otherwise in the bottom right quadrant.
    newElectron = {int(sqrt(pow(xLocation, 2) + pow(yLocation, 2))), int(180 + round( atan2 (-1 * yLocation, -1 * xLocation) * 180 / 3.14159265 )), energyDeposited};

  return newElectron; // Returns the electron struct.
}

/* Electron computeNextElectronLocation(Electron electron)

   Determines the next location for which a given electron will move depending on its current location.

*/
Electron computeNextElectronLocation(Electron electron) {
  int rStrongElectricField = 800; // The radius for which the electrons get pulled directly into the center of the detector. Default is 100.
  int rMovementLowerBounds = 20; // The smallest step an electron can move after appearing. Default is 10.
  int rMovementUpperBounds = 40; // The largest step an electron can move after appearing. Default is 50.
  int thetaMovementBounds = 5; // The maximum angle in degrees for which the electron can move in one step. Default is 5.
  int energyChangeLowerBounds = 0; // The minimum energy that an electron can lose in 1 interaction in keV. Default is 1.
  int energyChangeUpperBounds = 0; // The maximum energy that an electron can lose in 1 interaction in keV. Default is 5.

  const int maxSINCOSvalue = 16384; // The largest value that can be returned from the SIN and COS functions as declared in Basics.cpp. This should remain 16384.

  randomSeed(0); // Randomizes the seed. This in theory adds another layer of random to the code.

  int rCurrent = electron.rLocation; // Saves the passed in rLocation, thetaLocation, and energy values that are pointed to from the electron struct.
  int thetaCurrent = electron.thetaLocation;
  int energyCurrent = electron.energy;

  if (rCurrent > 0 && energyCurrent > 0) { // If the electron exists (ie. has a radius that is not at the center of the detector and has a positive energy).
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
      int rMovement = random(rMovementLowerBounds, rMovementUpperBounds)*3; // Generates a random value between the declared values for the r change.
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
    return newElectron;
  }
}

#endif
