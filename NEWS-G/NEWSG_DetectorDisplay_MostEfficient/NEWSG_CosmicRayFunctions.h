
#ifndef NEWSG_COSMICRAYFUNCTIONS_H
#define NEWSG_COSMICRAYFUNCTIONS_H

#include "NEWSG_CommonFunctions.h"
#include "NEWSG_ElectronFunctions.h"

Electron cosmicElectrons[6]; // Creates an array of 6 electrons. The value within the array needs to be equal to that of the numElectronLocationInArray variable.

// Creates an CosmicRay struct. A Cosmic Ray is made up of a x location, a y location, an energy, and a constant value for the movement in both the x direction and y direction.
typedef struct CosmicRay {
  int xLocation;
  int yLocation;
  int energy;
  int xMovement;
  int yMovement;
} CosmicRay;

CosmicRay cosmicray1;

CosmicRay createNewCosmicRay() {
  int rStartLowerBounds = 2000; // The minimum radius value for which a cosmic ray can be generated. Default is 2000.
  int rStartUpperBounds = 2048; // The maximum radius value for which a cosmic raycan be generated. Default is 2048.
  int energyLowerBounds = 200; // The minimum energy for which a cosmic ray can be generated in keV. Default is 150.
  int energyUpperBounds = 250; // The maximum energy for which a cosmic ray can be generated in keV. Default is 250.
  int movementBounds = 50; // The largest step a cosmic ray can move after appearing. Default is 25.
  int lowestSpeed = 50; // The lowest speed at which a cosmic ray can travel. Default is 20.

  const int maxSINCOSvalue = 16384; // The largest value that can be returned from the SIN and COS functions as declared in Basics.cpp. This should remain 16384.

  randomSeed(0); // Randomizes the seed. This in theory adds another layer of random to the code.

  int rCurrent = random(rStartLowerBounds, rStartUpperBounds); // Randomly returns the radius value for the cosmic ray to start at between 1028 and 2048.
  int thetaCurrent = random(0, 360); // Randomly returns the theta value for the cosmic ray to start at.
  int xCurrent = rCurrent * COS(thetaCurrent) / maxSINCOSvalue; // Converts from polar to cartesian where the movement of cosmic ray particles are more easily replicated.
  int yCurrent = rCurrent * SIN(thetaCurrent) / maxSINCOSvalue; // Converts from polar to cartesian where the movement of cosmic ray particles are more easily replicated.
  int energyCurrent = random(energyLowerBounds, energyUpperBounds); // Generates the starting energy value of the alpha.
  int xMovement = random(-movementBounds, movementBounds); // Determines the initial values for the x and y movement.
  int yMovement = random(-movementBounds, movementBounds);

  while (sqrt(pow(xMovement, 2) + pow(yMovement, 2)) < lowestSpeed) { // Computes the speed of the cosmic ray from the velocity vectors. This speed must be faster then the minumum.
    xMovement = random(-movementBounds, movementBounds); // Generates a random value for x between the bounds.
    yMovement = random(-movementBounds, movementBounds); // Generates a random value for y between the bounds.
  }

  CosmicRay newCosmicRay = {xCurrent, yCurrent, energyCurrent, xMovement, yMovement}; // Creates the new cosmic ray with the new values.
  return newCosmicRay; // Returns this new cosmic ray.
}

CosmicRay computeNextCosmicRayLocation(CosmicRay cosmicray) {
  const int maximumRadius = 2000; // Defines the maxmimum radius value an alpha can reach before it gets obliterated. Default is 2000.
  int energyChangeLowerBounds = 30; // The smallest energy value the cosmic ray can "lose" in one step to an electron. Default is 60 keV.
  int energyChangeUpperBounds = 60; // The largest energy value the cosmic ray can "lose" in one step to an electron. Default is 100 keV.
  int cosmicrayEnergyChangeDivider = 40; // The divider that controls the ratio of energy for which the cosmic ray loses in one step. Default is 4.
  int percentLikelihoodForElectron = 5; // The percent likelihood for an electron to be producted in each movement of the cosmic ray.

  randomSeed(0); // Randomizes the seed.

  int xCurrent = cosmicray.xLocation + cosmicray.xMovement; // Saves the passed in xLocation, yLocation, and energy values.
  int yCurrent = cosmicray.yLocation + cosmicray.yMovement;
  int energyCurrent = cosmicray.energy;

  if (sqrt(pow(xCurrent, 2) + pow(yCurrent, 2)) < maximumRadius && energyCurrent > 0) { // If the cosmic ray can exist.
    int energyChange = random(energyChangeLowerBounds, energyChangeUpperBounds); // Calculates the energy change that the electron will gain if created in keV.
    if (random(0, 101) > (100 - percentLikelihoodForElectron)) { // Results in the stated percent chance to generate an electron with each step.
      cosmicElectrons[cosmicrayElectronLocation] = generateElectron(xCurrent, yCurrent, energyChange); // Generates an electron and saves it.
      energyCurrent = energyCurrent - energyChange / cosmicrayEnergyChangeDivider; // Lowers the energy of the cosmic ray.
      cosmicrayElectronLocation++; // Increases the count for which the next electron will be added into the array.
      if (cosmicrayElectronLocation == numElectronLocationsInArray) { // If the array is filled rotate around and start filling it again.
        cosmicrayElectronLocation = 0; // Resets the array position counter to 0.
      }
    }
    else {
      energyCurrent = energyCurrent - energyChange / cosmicrayEnergyChangeDivider;
    }

    for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For every position in the array...
      cosmicElectrons[loc] = computeNextElectronLocation(cosmicElectrons[loc]); // Computes and moves the electon through its current step.
    }

    simulateTrack(energyCurrent, xCurrent, yCurrent); // Updates the alphas position.
    CosmicRay newCosmicRay = {xCurrent, yCurrent, energyCurrent, cosmicray.xMovement}; // Creates the new cosmic ray with the new values.
    return newCosmicRay; // Returns this new cosmic ray.
  }
  else { // If the cosmic ray has left the detector or has no more energy...
    cosmicrayDone = true;
    lastCosmicRayEvent = millis();
    nextCosmicRayEvent = random(500, 2000);
    CosmicRay newCosmicRay = createNewCosmicRay(); // Create a new cosmic ray.

    while (cosmicElectrons[0].rLocation >= 20 or cosmicElectrons[1].rLocation >= 20 or cosmicElectrons[2].rLocation >= 20 or cosmicElectrons[3].rLocation >= 20  \
           or cosmicElectrons[4].rLocation >= 20 or cosmicElectrons[5].rLocation >= 20) {
      displayDetector();
      if (cosmicrayDone == false)
        cosmicray1 = computeNextCosmicRayLocation(cosmicray1);
      for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For every position in the array...
        cosmicElectrons[loc] = computeNextElectronLocation(cosmicElectrons[loc]); // Computes and moves the electon through its current step.
      }
    }
    return newCosmicRay; // Returns the new alpha so that the infinite loop can be continued.
  }
}

#endif
