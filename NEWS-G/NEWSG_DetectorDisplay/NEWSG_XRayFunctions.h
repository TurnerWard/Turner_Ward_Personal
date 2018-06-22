
#ifndef NEWSG_XRAYFUNCTIONS_H
#define NEWSG_XRAYFUNCTIONS_H

#include "NEWSG_CommonFunctions.h"

// Creates an XRay struct. An xray is made up of a radial location, and angular location, and an energy.
typedef struct XRay {
  int rLocation;
  int thetaLocation;
  int energy;
} XRay;

XRay xray1;

XRay createNewXRay() {
  int rStartLowerBounds = 2000; // The closest value for which xrays can appear to the middle of the detector. Default is 2000.
  int rStartUpperBounds = 2048; // The furthest value for which xrays can appear to the middle of the detector. Default is 2048 which is the maximum value.
  int energyLowerBounds = 70; // The minimum energy for which an xray can be generated in keV. Default is 70.
  int energyUpperBounds = 125; // The maximum energy for which an xray can be generated in keV. Default is 125.

  randomSeed(0); // Randomizes the seed.
  int rCurrent = random(rStartLowerBounds, rStartUpperBounds); // Randomly returns the radius value for the xray to start at between 1028 and 2048.
  int thetaCurrent = random(0, 360); // Randomly returns the theta value for the electron to start at.
  int energyCurrent = random(energyLowerBounds, energyUpperBounds);

  XRay newXRay = {rCurrent, thetaCurrent, energyCurrent}; // Creates the new elecron with the new values.
  return newXRay; // Returns this new electron.
}

XRay computeNextXRayLocation(XRay xray) {
  int rStrongElectricField = 50; // The radius for which the xrays get pulled directly into the center of the detector. Default is 100.
  int rMovementLowerBounds = 20; // The smallest step an xrays can move after appearing. Default is 20.
  int rMovementUpperBounds = 40; // The largest step an xrays can move after appearing. Default is 40.
  int thetaMovementBounds = 5; // The maximum angle in degrees for which the xrays can move in one step. Default is 5.
  int energyChangeLowerBounds = 0; // The minimum energy that an xray can lose in 1 interaction in keV. Default is 1.
  int energyChangeUpperBounds = 1; // The maximum energy that an xray can lose in 1 interaction in keV. Default is 5.

  const int maxSINCOSvalue = 16384; // The largest value that can be returned from the SIN and COS functions as declared in Basics.cpp. This should remain 16384.

  randomSeed(0); // Randomizes the seed. This in theory adds another layer of random to the code.

  int rCurrent = xray.rLocation; // Saves the passed in rLocation, thetaLocation, and energy values that are pointed to from the xray struct.
  int thetaCurrent = xray.thetaLocation;
  int energyCurrent = xray.energy;

  if (rCurrent > 0 && energyCurrent > 0) { // If the xray exists (ie. has a radius that is not at the center of the detector and has a positive energy).
    if (rCurrent > rStrongElectricField && energyCurrent > 0) { // While outside the inner radius where the electric field is weaker and the xray still has energy.
      int rMovement = random(rMovementLowerBounds, rMovementUpperBounds); // Generates a random value between the declared values for the r change.
      int thetaMovement = random(-thetaMovementBounds, thetaMovementBounds); // Generates a random value between the declared values for the theta change.
      int energyChange = random(energyChangeLowerBounds, energyChangeUpperBounds); // Generates a random value between the declared values for the energy change.
      rCurrent = rCurrent - rMovement; // Updates the current radius value.
      thetaCurrent = thetaCurrent + thetaMovement; // Updates the current theta value.
      energyCurrent = energyCurrent - energyChange; // Updates the current energy value.

      simulateTrack(energyCurrent, rCurrent * COS(thetaCurrent) / maxSINCOSvalue, rCurrent * SIN(thetaCurrent) / maxSINCOSvalue); // Displays the xray.
      XRay newXRay = {rCurrent, thetaCurrent, energyCurrent}; // Creates the new xray with the new values.
      return newXRay; // Returns this new xray.
    }
    else if (rCurrent <= rStrongElectricField && 0 < rCurrent && energyCurrent > 0) { // While the xray is within the strong electric field range and has energy.
      int rMovement = random(rMovementLowerBounds, rMovementUpperBounds); // Generates a random value between the declared values for the r change.
      int energyChange = random(energyChangeLowerBounds, energyChangeUpperBounds); // Generates a random value between the declared values for the energy change.
      rCurrent = rCurrent - rMovement; // Updates the current radius value.
      energyCurrent = energyCurrent - energyChange; // Updates the current energy value.

      simulateTrack(energyCurrent, rCurrent * COS(thetaCurrent) / maxSINCOSvalue, rCurrent * SIN(thetaCurrent) / maxSINCOSvalue); // Displays the xray.
      XRay newXRay = {rCurrent, thetaCurrent, energyCurrent}; // Creates the new xray with the new values.
      return newXRay; // Returns this new xray.
    }
  }
  else {
    xrayDone = true;
    XRay newXRay = createNewXRay(); // Creates a new XRay.
    return newXRay;
  }
}

#endif
