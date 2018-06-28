#ifndef COSMICRAYFUNCTIONS_H
#define COSMICRAYFUNCTIONS_H

// Include files.
#include "CommonFunctions.h"
#include "ElectronFunctions.h"

Electron cosmicElectrons[11]; // Creates an array of 11 cosmic electrons. The number of array values needs to be equal to that of the numElectronLocationInArray variable.

// Creates an CosmicRay struct. A Cosmic Ray is made up of a x movement path, a y movement path, an energy, and a location marker for the location within the path array.
typedef struct CosmicRay {
  int xMovementPath[11];
  int yMovementPath[11];
  int energy;
  int movementLocation;
} CosmicRay;

CosmicRay cosmicray1; // Creates a cosmic ray.

// An array containing 6 different movement possibilities for quadrant 1 in the x direction for the cosmic ray particles.
const int xMPPFQ1Muon[6][11] PROGMEM = { // Note: This array is stored in flash memory which allows for more dynamic memory to be free!
  {320, 70, -190, -464, -720, -940, -1170, -1366, -1596, -1790, -2010},
  {240, 120, -1, -130, -260,  -380,  -464,  -560, -640, -720,  -890},
  {374, 450, 520, 610, 674, 756, 840, 885, 960, 1040, 1110},
  {1350, 1310, 1260, 1220, 1186, 1150, 1110, 1050, 1030, 990, 1010},
  {2020, 1880, 1720, 1553, 1350, 1176, 966, 760, 534, 290, 55},
  {1030, 1146, 1260, 1370, 1470, 1553, 1643, 1730, 1805, 1890, 1967}
};

// An array containing 6 different movement possibilities for quadrant 1 in the y direction for the cosmic ray particles.
const int yMPPFQ1Muon[6][11] PROGMEM = { // Note: This array is stored in flash memory which allows for more dynamic memory to be free!
  {1980, 1740, 1500, 1283, 1060, 870, 665, 480, 284, 106, -70},
  {2020, 1474, 895, 494, 106, -220, -500, -835,  -1163,  -1440, -1840},
  {2000, 1585, 1210, 850, 500, 120, -280, -630, -990, -1350, -1694},
  {1520, 1200, 854, 520, 210, -110, -470, -780, -1110, -1410, -1700},
  {350, 77, -163, -390, -630, -846, -1086, -1326, -1566, -1800, -2030},
  {1713, 1455, 1250, 1040, 826, 610, 390, 170, -40, -253, -480}
};

/* bool checkCosmicElectronDist()

    Returns false if the electrons have a distance greater then the specified distance away from the center of the detector. If all the electrons are within the specified distance
    from the center of the detector return true.

*/
bool checkCosmicElectronDist() {
  for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For each variable in the electron array.
    if (cosmicElectrons[loc].rLocation < maxDisplayValue) // Check to see if the radial location is greater then 2048.
      return false; // If one of the radial distances is under 2048 return false and keep the electrons drifting towards the center of the circle.
  }
  return true; // If all electrons are over a radial distance of 2048 then return true and stop the electrons from drifting within the detector.
}

/* CosmicRay createNewCosmicRay()

    Creates a new cosmic ray based on the libraries declared above. This new cosmic ray is returned to allow for its track and electrons/ions to be simulated
    and displayed.

*/
CosmicRay createNewCosmicRay() {
  const int maxSINCOSvalue = 16384; // The largest value that can be returned from the SIN and COS functions as declared in Basics.cpp. This should remain 16384.

  randomSeed(0); // Randomizes the seed. This in theory adds another layer of random to the code.
  int pathNumber = random(0, 6); // Picks a random number from 0 to 5 for the path.
  int halfNumber = random(1, 3); // Picks a random number between 1 and 2 for the half of the detector that the particle is displayed in.
  int cosmicrayEnergy = 5300; // Each Cosmic Ray is generated with 5300 keV.
  int arrayStartLocation = 0; // Keeps track of the arrays start location (ie. 0).

  // Serial.print("Cosmic Ray -> Path #: "); Serial.print(pathNumber); Serial.print("\t Half #: "); Serial.println(halfNumber); // Used for debugging.

  CosmicRay newCosmicRay; // Creates a new cosmic ray.

  if (halfNumber ==  1) { // If in the first half.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For each step for the particle.
      newCosmicRay.xMovementPath[loc] = pgm_read_word(&(xMPPFQ1Muon[pathNumber][loc])); // Fills the x movement array from PROGMEM.
      newCosmicRay.yMovementPath[loc] = pgm_read_word(&(yMPPFQ1Muon[pathNumber][loc])); // Fills the y movement array from PROGMEM.
    }
    newCosmicRay.energy = cosmicrayEnergy; // Enters the cosmic rays energy.
    newCosmicRay.movementLocation = arrayStartLocation; // Sets the arrays start location.
  }
  else if (halfNumber ==  2) { // If in the second half.
    for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For each step for the particle.
      newCosmicRay.xMovementPath[loc] = -1 * pgm_read_word(&(xMPPFQ1Muon[pathNumber][loc])); // Flips and fills the x movement array from PROGMEM.
      newCosmicRay.yMovementPath[loc] = pgm_read_word(&(yMPPFQ1Muon[pathNumber][loc])); // Fills the y movement array from PROGMEM.
    }
    newCosmicRay.energy = cosmicrayEnergy; // Enters the cosmic rays energy.
    newCosmicRay.movementLocation = arrayStartLocation; // Sets the arrays start location.
  }
  return newCosmicRay; // Returns this new cosmic ray.
}

/* CosmicRay computeNextCosmicRayLocation(CosmicRay cosmicray)

    When passed in a cosmic ray this function creates electrons when appropriate and allows for the cosmic ray to transition to the next position. This function is also responsible
    for drifting the electrons and ions. Each time this function it is called it loops back out until it is called again.

*/
CosmicRay computeNextCosmicRayLocation(CosmicRay cosmicray) {
  int energyChangeLowerBounds = 300; // The smallest energy value the cosmic ray can "lose" in one step to an electron or in general. Default is 300 keV.
  int energyChangeUpperBounds = 400; // The largest energy value the cosmic ray can "lose" in one step to an electron or in general. Default is 400 keV.

  randomSeed(0); // Randomizes the seed.
  int xCurrent = cosmicray.xMovementPath[cosmicray.movementLocation]; // Saves the passed in xLocation, yLocation, and energy values.
  int yCurrent = cosmicray.yMovementPath[cosmicray.movementLocation];
  int energyCurrent = cosmicray.energy;

  if (cosmicray.movementLocation < numberOfParticleSteps) { // If the cosmic ray still has path locations left within its array that havent yet been used.
    int energyChange = random(energyChangeLowerBounds, energyChangeUpperBounds); // Calculates the energy change that the electron will gain if created in keV.
    if (cosmicray.movementLocation % 2 == 0) { // Results in an electron being produced each second step.
      cosmicElectrons[cosmicrayElectronLocation] = generateElectron(xCurrent, yCurrent, energyChange); // Generates the electron and saves it.
      energyCurrent = energyCurrent - energyChange; // Lowers the energy of the cosmic ray.
      cosmicrayElectronLocation++; // Increases the count for which the next electron will be added into the array.

      if (cosmicrayElectronLocation == numElectronLocationsInArray) // If the array is filled reset the cosmic ray electron location variable and start filling it again.
        cosmicrayElectronLocation = 0; // Resets the array position counter to 0.
    }
    else {
      energyCurrent = energyCurrent - energyChange; // Even if an electron isnt produced decrease the energy of the cosmic ray by the determined amount.
    }

    for (int loc = 0; loc < numElectronLocationsInArray; loc++) // For every position in the array...
      cosmicElectrons[loc] = computeNextElectronLocation(cosmicElectrons[loc]); // Computes and moves the electon through its current step.

    if (delayTime != 0 ) {
      int currentTime = millis(); int enteredTime = millis();
      while (currentTime < enteredTime + delayTime) {
        currentTime = millis();
        simulateTrack(energyCurrent, xCurrent, yCurrent); // Updates the cosmic rays position.
        displayDetector(displayEnergyLevel);
      }
    }
    else
      simulateTrack(energyCurrent, xCurrent, yCurrent); // Updates the cosmic rays position.

    cosmicray.energy = energyCurrent; // Updates the cosmic rays energy.
    cosmicray.movementLocation = cosmicray.movementLocation + 1; // Updates the cosmic rays movement location by increasing it by 1.
    return cosmicray; // Returns this updated cosmic ray.
  }
  else { // If the cosmic ray has left the detector or has no more energy...
    if (checkCosmicElectronDist() == false) { // If all the electrons and ions are within the detector.
      displayDetector(displayEnergyLevel); // Displays the detector.
      int numIons = 0;
      for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For every position in the array...
        cosmicElectrons[loc] = computeNextElectronLocation(cosmicElectrons[loc]); // Computes and moves the electon through its current step.
        if (cosmicElectrons[loc].rLocation < 2048)
          numIons = numIons + 1;
        displayCurrentMeasured(numIons);
      }
      return cosmicray; // Returns a nonupdated cosmic ray which allows for this segment of the code to be accessed again immediatly afterwards unless all the electrons and
      // ions leave the detector.
    }
    else {
      cosmicrayDone = true; // Since the cosmic ray is now done set this boolean back to true.
      CosmicRay newCosmicRay = createNewCosmicRay(); // Create a new cosmic ray.
      return newCosmicRay; // Returns the new cosmic ray so that the infinite loop can be continued when a button is pressed.
    }
  }
}

#endif
