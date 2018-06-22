#ifndef NEWSG_COSMICRAYFUNCTIONS_H
#define NEWSG_COSMICRAYFUNCTIONS_H

#include "NEWSG_CommonFunctions.h"
#include "NEWSG_ElectronFunctions.h"

Electron cosmicElectrons[11]; // Creates an array of 6 electrons. The value within the array needs to be equal to that of the numElectronLocationInArray variable.

// Creates an CosmicRay struct. A Cosmic Ray is made up of a x movement path, a y movement path, an energy, and a location marker for the location within the path.
typedef struct CosmicRay {
  int xMovementPath[11];
  int yMovementPath[11];
  int energy;
  int movementLocation;
} CosmicRay;

CosmicRay cosmicray1;

/* bool checkCosmicElectronDist()

    Returns false if the electrons have a distance greater then the specified distance away from the center of the detector. If all the electrons are within the specified distance
    from the center of the detector return true.

*/
bool checkCosmicElectronDist() {
  for (int loc = 0; loc < numElectronLocationsInArray; loc++) {
    if (cosmicElectrons[loc].rLocation > 20) {
      return false;
    }
  }
  return true;
}

CosmicRay createNewCosmicRay() {
  const int maxSINCOSvalue = 16384; // The largest value that can be returned from the SIN and COS functions as declared in Basics.cpp. This should remain 16384.

  randomSeed(0); // Randomizes the seed. This in theory adds another layer of random to the code.
  int pathNumber = random(0, 6); // Picks a random number from 0 to 5.
  int halfNumber = random(1, 3); // Picks a random number between 1 and 2 for the half of the detector that is displayed.
  int cosmicrayEnergy = 5300; // Should be 5300. In keV.
  int arrayStartLocation = 0;

  CosmicRay newCosmicRay;

  int xMPPFQ1Muon[6][11] {
  {320, 70, -190, -464, -720, -940, -1170, -1366, -1596, -1790, -2010}, // 11
  {240, 120, -1, -130, -260,  -380,  -464,  -560, -640, -720,  -890},
  {374,450,520,610,674,756,840,885,960,1040,1110},
  {1350,1310,1260,1220,1186,1150,1110,1050,1030,990,1010},
  {2020,1880,1720,1553,1350,1176,966,760,534,290,55},
  {1030,1146,1260,1370,1470,1553,1643,1730,1805,1890,1967}
};

int yMPPFQ1Muon[6][11] {
  {1980, 1740, 1500, 1283, 1060, 870, 665, 480, 284, 106, -70}, // 11
  {2020, 1474, 895,494, 106, -220, -500, -835,  -1163,  -1440, -1840},
  {2000,1585,1210,850,500,120,-280,-630,-990,-1350,-1694},
  {1520,1200,854,520,210,-110,-470,-780,-1110,-1410,-1700},
  {350,77,-163,-390,-630,-846,-1086,-1326,-1566,-1800,-2030},
  {1713,1455,1250,1040,826,610,390,170,-40,-253,-480}
};

  if (halfNumber ==  1) {
    for (int loc = 0; loc < sizeof (xMPPFQ1Muon[0]) / sizeof (xMPPFQ1Muon[0][0]); loc++) {
      newCosmicRay.xMovementPath[loc] = xMPPFQ1Muon[pathNumber][loc]; // Fills the movement arrays.
      newCosmicRay.yMovementPath[loc] = yMPPFQ1Muon[pathNumber][loc];
    }
    newCosmicRay.energy = cosmicrayEnergy;
    newCosmicRay.movementLocation = 0; // Creates the new cosmic ray with the new values.
  }
  else if (halfNumber ==  2) {
    for (int loc = 0; loc < sizeof (xMPPFQ1Muon[0]) / sizeof (xMPPFQ1Muon[0][0]); loc++) {
      newCosmicRay.xMovementPath[loc] = -1 * xMPPFQ1Muon[pathNumber][loc]; // Fills the movement arrays.
      newCosmicRay.yMovementPath[loc] = yMPPFQ1Muon[pathNumber][loc];
    }
    newCosmicRay.energy = cosmicrayEnergy;
    newCosmicRay.movementLocation = 0; // Creates the new cosmic ray with the new values.
  }
  return newCosmicRay; // Returns this new cosmic ray.
}

CosmicRay computeNextCosmicRayLocation(CosmicRay cosmicray) {
  int energyChangeLowerBounds = 300;
  int energyChangeUpperBounds = 400;

  randomSeed(0); // Randomizes the seed.

  int xCurrent = cosmicray.xMovementPath[cosmicray.movementLocation]; // Saves the passed in xLocation, yLocation, and energy values.
  int yCurrent = cosmicray.yMovementPath[cosmicray.movementLocation];
  int energyCurrent = cosmicray.energy;

  if (cosmicray.movementLocation < sizeof (cosmicray.xMovementPath) / sizeof (cosmicray.xMovementPath[0])) { // If the cosmic ray can exist.
    int energyChange = random(energyChangeLowerBounds, energyChangeUpperBounds); // Calculates the energy change that the electron will gain if created in keV.
    if (cosmicray.movementLocation % 2 == 0) { // Results in the stated percent chance to generate an electron with each step.
      cosmicElectrons[cosmicrayElectronLocation] = generateElectron(xCurrent, yCurrent, energyChange); // Generates an electron and saves it.
      energyCurrent = energyCurrent - energyChange; // Lowers the energy of the cosmic ray.
      cosmicrayElectronLocation++; // Increases the count for which the next electron will be added into the array.

      if (cosmicrayElectronLocation == numElectronLocationsInArray) { // If the array is filled rotate around and start filling it again.
        cosmicrayElectronLocation = 0; // Resets the array position counter to 0.
      }
    }
    else {
      energyCurrent = energyCurrent - energyChange;
    }

    for (int loc = 0; loc < numElectronLocationsInArray; loc++) // For every position in the array...
      cosmicElectrons[loc] = computeNextElectronLocation(cosmicElectrons[loc]); // Computes and moves the electon through its current step.

    simulateTrack(energyCurrent, xCurrent, yCurrent); // Updates the cosmic rays position.
    cosmicray.energy = energyCurrent;
    cosmicray.movementLocation = cosmicray.movementLocation + 1; // Creates the new alpha with the new values.
    return cosmicray; // Returns this new cosmic ray.
  }
  else { // If the cosmic ray has left the detector or has no more energy...
    cosmicrayDone = true;
    CosmicRay newCosmicRay = createNewCosmicRay(); // Create a new cosmic ray.

    while (checkCosmicElectronDist() == false) {
      displayDetector();
      for (int loc = 0; loc < numElectronLocationsInArray; loc++) // For every position in the array...
        cosmicElectrons[loc] = computeNextElectronLocation(cosmicElectrons[loc]); // Computes and moves the electon through its current step.
    }
    return newCosmicRay; // Returns the new alpha so that the infinite loop can be continued.
  }
}

#endif
