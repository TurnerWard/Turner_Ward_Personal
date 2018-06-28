#ifndef ALPHAFUNCTIONS_H
#define ALPHAFUNCTIONS_H

// Include files.
#include "CommonFunctions.h"
#include "ElectronFunctions.h"

// Creates an Alpha struct. An alpha is made up of an array of x locations, an array of y locations, an energy, and a variable to track where in the movement path the particle is.
typedef struct Alpha {
  int xMovementPath[11];
  int yMovementPath[11];
  int energy;
  int movementLocation;
} Alpha;

// Variable declaration.
Electron Po210AlphaElectrons[11]; // Creates an array of 11 Po 210 electrons. The value within the array needs to be equal to that of the numElectronLocationInArray variable.
Electron Rn222AlphaElectrons[11]; // Creates an array of 11 Rn 222 electrons. The value within the array needs to be equal to that of the numElectronLocationInArray variable.

// Alpha declaration.
Alpha po210alpha1; // Two different Alpha particles - one is from Po 210, one is from Rn 222.
Alpha rn222alpha1;

// An array containing 6 different movement possibilities for quadrant 1 in the x direction for the alpha particles produced from Po210.
const int xMPPFQ1Po210[6][11] PROGMEM = { // Note: This array is stored in flash memory which allows for more dynamic memory to be free.
  {283, 146, 1, -120, -220, -306, -392, -480, -566, -634, -690}, // 0
  {720, 810, 920, 1024, 1098, 1022, 941, 862, 750, 670, 600}, // 1
  {1970, 1752, 1544, 1332, 1141, 910, 704, 528, 401, 329, 276}, // 2
  {1972, 1791, 1578, 1352, 1153, 931, 752, 579, 401, 258, 100}, // 3
  {1870, 1730, 1560, 1420, 1280, 1160, 1110, 1030, 970, 900, 850}, // 4
  {1370, 1320, 1240, 1200, 1160, 1090, 1050, 1000, 950, 930, 900} // 5
};

// An array containing 6 different movement possibilities for quadrant 1 in the y direction for the alpha particles produced from Po210.
const int yMPPFQ1Po210[6][11] PROGMEM = { // Note: This array is stored in flash memory which allows for more dynamic memory to be free.
  {2000, 1864, 1745, 1636, 1540, 1458, 1370, 1293, 1227, 1165, 1120}, // 0
  {1910, 1690, 1480, 1248, 1026, 869, 738, 634, 510, 410, 280}, // 1
  {240, 363, 468, 603, 651, 682, 669, 723, 842, 986, 1121}, // 2
  {246, 98, -62, -200, -333, -456, -561, -663, -728, -792, -871}, // 3
  {760, 790, 790, 780, 780, 770, 750, 760, 760, 760, 755}, // 4
  {1490, 1370, 1260, 1170, 1110, 1040, 940, 880, 810, 790, 770} // 5
};

// An array containing 6 different movement possibilities for quadrant 1 in the x direction for the alpha particles produced from Rn222.
const int xMPPFQ1Rn222[6][11] PROGMEM = { // Note: This array is stored in flash memory which allows for more dynamic memory to be free.
  {165, 220, 290, 354, 420, 466, 504, 523, 560, 603, 645}, // 0
  {550, 448, 335, 230, 123, -10, -126, -220, -286, -366, -446}, // 1
  {1337, 1313, 1266, 1220, 1153, 1083, 1017, 960, 910, 857, 805}, // 2
  {744, 777, 814, 860, 923, 1000, 1070, 1140, 1205, 1266, 1346}, // 3
  {810, 900, 960, 1000, 1010, 1030, 1050, 1140, 1233, 1330, 1402}, // 4
  {1510, 1402, 1300, 1195, 1115, 1026, 960, 930, 930, 923, 910} // 5
};

// An array containing 6 different movement possibilities for quadrant 1 in the y direction for the alpha particles produced from Rn222.
const int yMPPFQ1Rn222[6][11] PROGMEM = { // Note: This array is stored in flash memory which allows for more dynamic memory to be free.
  {566, 665, 773, 886, 1000, 1110, 1220, 1300, 1356, 1430, 1483}, // 0
  {1590, 1507, 1417, 1366, 1310, 1234, 1150, 1093, 1055, 1020, 990}, // 1
  {434, 550, 674, 790, 895, 1000, 1017, 1178, 1240, 1300, 1356}, // 2
  {627, 514, 400, 290, 185, 86, -17, -97, -150, -200, -240}, // 3
  {1676, 1563, 1464, 1350, 1225, 1107, 985, 905, 905, 933, 960}, // 4
  {160, 230, 303, 397, 463, 530, 604, 693, 782, 867, 938} // 5
};

/* bool checkPo210AlphaElectronDist()

    Returns false if the electrons have a distance smaler then the specified distance away from the center of the detector. This continues to be monitored when the electrons
    reach the middle of the circle and become ions. When all these ions reach the outside of the detector then the function returns true.

*/
bool checkPo210AlphaElectronDist() {
  for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For each electron in the array.
    if (Po210AlphaElectrons[loc].rLocation < maxDisplayValue) // Check to see if each one is within the detector.
      return false; // If at least one electron is within the detector then return false.
  }
  return true; // If every electron is outside the detector then return true.
}

/* bool checkRn222AlphaElectronDist()

    Returns false if the electrons have a distance smaler then the specified distance away from the center of the detector. This continues to be monitored when the electrons
    reach the middle of the circle and become ions. When all these ions reach the outside of the detector then the function returns true.

*/
bool checkRn222AlphaElectronDist() {
  for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For each electron in the array.
    if (Rn222AlphaElectrons[loc].rLocation < maxDisplayValue) // Check to see if each one is within the detector.
      return false; // If at least one electron is within the detector then return false.
  }
  return true; // If every electron is outside the detector then return true.
}

/* Alpha createNewPo210Alpha()

   Creates a new Po210 Alpha particle with "random" properties.

*/
Alpha createNewPo210Alpha() {
  randomSeed(0); // Randomizes the seed. This in theory adds another layer of random to the code.
  int pathNumber = random(0, 6); // Picks a random number from 0 to 5.
  int quadrantNumber = random(1, 5); // Picks a random number between 1 to 4.
  int Po210alphaEnergy = 5300; // The energy of the Po 210 alpha, in keV.
  int arrayStartLocation = 0; // The array start location.
  const int maxSINCOSvalue = 16384; // The largest value that can be returned from the SIN and COS functions as declared in Basics.cpp. This should remain 16384.

  // Serial.print("Po 210 -> Path #: "); Serial.print(pathNumber); Serial.print("\t Quadrant #: "); Serial.println(quadrantNumber); // For debugging purposes.

  Alpha newPo210Alpha; // Initiates a new Po 210 alpha so that it can be filled based on quadrant number and such.

  if (quadrantNumber ==  1) { // If in the first quadrant.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For all the steps in the particle.
      newPo210Alpha.xMovementPath[loc] = pgm_read_word(&(xMPPFQ1Po210[pathNumber][loc])); // Fills the x movement array from PROGMEM.
      newPo210Alpha.yMovementPath[loc] = pgm_read_word(&(yMPPFQ1Po210[pathNumber][loc])); // Fills the y movement array from PROGMEM.
    }
    newPo210Alpha.energy = Po210alphaEnergy; // Sets the energy value.
    newPo210Alpha.movementLocation = arrayStartLocation; // Sets the start location for the movement path.
  }
  else if (quadrantNumber ==  2) { // If in the second quadrant.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For all the steps in the particle.
      newPo210Alpha.xMovementPath[loc] = -1 * pgm_read_word(&(xMPPFQ1Po210[pathNumber][loc])); // Flips and fills the x movement array from PROGMEM.
      newPo210Alpha.yMovementPath[loc] = pgm_read_word(&(yMPPFQ1Po210[pathNumber][loc])); // Fills the y movement array from PROGMEM.
    }
    newPo210Alpha.energy = Po210alphaEnergy; // Sets the energy value.
    newPo210Alpha.movementLocation = arrayStartLocation; // Sets the start location for the movement path.
  }
  else if (quadrantNumber ==  3) { // If in the third quadrant.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For all the steps in the particle.
      newPo210Alpha.xMovementPath[loc] = -1 * pgm_read_word(&(xMPPFQ1Po210[pathNumber][loc])); // Flips and fills the x movement array from PROGMEM.
      newPo210Alpha.yMovementPath[loc] = -1 * pgm_read_word(&(yMPPFQ1Po210[pathNumber][loc])); // Flips and fills the y movement array from PROGMEM.
    }
    newPo210Alpha.energy = Po210alphaEnergy; // Sets the energy value.
    newPo210Alpha.movementLocation = arrayStartLocation; // Sets the start location for the movement path.
  }
  else if (quadrantNumber ==  4) { // If in the fourth quadrant.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For all the steps in the particle.
      newPo210Alpha.xMovementPath[loc] = pgm_read_word(&(xMPPFQ1Po210[pathNumber][loc])); // Fills the x movement array from PROGMEM.
      newPo210Alpha.yMovementPath[loc] = -1 * pgm_read_word(&(yMPPFQ1Po210[pathNumber][loc])); // Flips and fills the y movement array from PROGMEM.
    }
    newPo210Alpha.energy = Po210alphaEnergy; // Sets the energy value.
    newPo210Alpha.movementLocation = arrayStartLocation; // Sets the start location for the movement path.
  }
  return newPo210Alpha; // Returns this new Po 210 alpha.
}

/* Alpha createNewRn222Alpha()

   Creates a new Rn 222 Alpha particle with random properties.

*/
Alpha createNewRn222Alpha() {
  randomSeed(0); // Randomizes the seed. This in theory adds another layer of random to the code.
  int pathNumber = random(0, 6); // Picks a random number from 0 to 5.
  int quadrantNumber = random(1, 5); // Picks a random number between 1 to 4.
  int Rn222alphaEnergy = 5500; // The start energy of the alpha, in keV.
  int arrayStartLocation = 0; // The array start location.
  const int maxSINCOSvalue = 16384; // The largest value that can be returned from the SIN and COS functions as declared in Basics.cpp. This should remain 16384.

  // Serial.print("Rn 222 -> Path #: "); Serial.print(pathNumber); Serial.print("\t Quadrant #: "); Serial.println(quadrantNumber); // For debugging purposes.

  Alpha newRn222Alpha; // Initiates a new Rn 222 alpha to be filled based on the quadrant.

  if (quadrantNumber ==  1) { // If in the first quadrant.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For all the steps in the particle.
      newRn222Alpha.xMovementPath[loc] = pgm_read_word(&(xMPPFQ1Rn222[pathNumber][loc])); // Fills the x movement array from PROGMEM.
      newRn222Alpha.yMovementPath[loc] = pgm_read_word(&(yMPPFQ1Rn222[pathNumber][loc])); // Fills the y movement array from PROGMEM.
    }
    newRn222Alpha.energy = Rn222alphaEnergy; // Sets the energy value.
    newRn222Alpha.movementLocation = arrayStartLocation; // Sets the start location for the movement path.
  }
  else if (quadrantNumber ==  2) { // If in the second quadrant.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For all the steps in the particle.
      newRn222Alpha.xMovementPath[loc] = -1 * pgm_read_word(&(xMPPFQ1Rn222[pathNumber][loc])); // Flips and fills the x movement array from PROGMEM.
      newRn222Alpha.yMovementPath[loc] = pgm_read_word(&(yMPPFQ1Rn222[pathNumber][loc])); // Fills the y movement array from PROGMEM.
    }
    newRn222Alpha.energy = Rn222alphaEnergy; // Sets the energy value.
    newRn222Alpha.movementLocation = arrayStartLocation; // Sets the start location for the movement path.
  }
  else if (quadrantNumber ==  3) { // If in the third quadrant.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For all the steps in the particle.
      newRn222Alpha.xMovementPath[loc] = -1 * pgm_read_word(&(xMPPFQ1Rn222[pathNumber][loc])); // Flips and fills the x movement array from PROGMEM.
      newRn222Alpha.yMovementPath[loc] = -1 * pgm_read_word(&(yMPPFQ1Rn222[pathNumber][loc])); // Flips and fills the y movement array from PROGMEM.
    }
    newRn222Alpha.energy = Rn222alphaEnergy; // Sets the energy value.
    newRn222Alpha.movementLocation = arrayStartLocation; // Sets the start location for the movement path.
  }
  else if (quadrantNumber ==  4) { // If in the fourth quadrant.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For all the steps in the particle.
      newRn222Alpha.xMovementPath[loc] = pgm_read_word(&(xMPPFQ1Rn222[pathNumber][loc])); // Fills the x movement array from PROGMEM.
      newRn222Alpha.yMovementPath[loc] = -1 * pgm_read_word(&(yMPPFQ1Rn222[pathNumber][loc])); // Flips and fills the y movement array from PROGMEM.
    }
    newRn222Alpha.energy = Rn222alphaEnergy; // Sets the energy value.
    newRn222Alpha.movementLocation = arrayStartLocation; // Sets the start location for the movement path.
  }
  return newRn222Alpha; // Returns this new Rn 222 alpha.
}

/* Alpha computeNextPo210AlphaLocation(Alpha Po210Alpha)

   Determines the next location for which a given alpha will move along with determining if an electron should appear and controlling said electrons.

*/
Alpha computeNextPo210AlphaLocation(Alpha Po210Alpha) {
  int energyChangeLowerBounds = 300; // The smallest energy value the alpha can "lose" to an electron. Default is 300 keV.
  int energyChangeUpperBounds = 400; // The largest energy value the alpha can "lose" to an electron. Default is 400 keV.

  randomSeed(0); // Randomizes the seed. This is supposed to add another level of random.
  int xCurrent = Po210Alpha.xMovementPath[Po210Alpha.movementLocation]; // Saves the passed in xLocation, yLocation, and energy values.
  int yCurrent = Po210Alpha.yMovementPath[Po210Alpha.movementLocation];
  int energyCurrent = Po210Alpha.energy;

  if (Po210Alpha.movementLocation < numberOfParticleSteps) { // If the Po 210 alpha still has movement locations left.
    int energyChange = random(energyChangeLowerBounds, energyChangeUpperBounds); // Calculates the energy change of the alpha.
    Po210AlphaElectrons[Po210AlphaElectronLocation] = generateElectron(xCurrent, yCurrent, energyChange); // Generates an electron and saves it.
    energyCurrent = energyCurrent - energyChange; // Lowers the energy of the Po 210 alpha.
    Po210AlphaElectronLocation++; // Increases the count for where the next electron will be added into the array.

    if (Po210AlphaElectronLocation == numElectronLocationsInArray) // If the array is completely filled, rotate around and start filling it again.
      Po210AlphaElectronLocation = 0; // Resets the array position counter to 0.

    for (int loc = 0; loc < numElectronLocationsInArray; loc++)  // For every position in the array...
      Po210AlphaElectrons[loc] = computeNextElectronLocation(Po210AlphaElectrons[loc]); // Computes and moves the electon through its current step.

    if (delayTime != 0 ) {
      int currentTime = millis(); int enteredTime = millis();
      while (currentTime < enteredTime + delayTime) {
        currentTime = millis();
        simulateTrack(energyCurrent, xCurrent, yCurrent); // Updates the Po 210 alphas position.
        displayDetector(displayEnergyLevel);
      }
    }
    else
      simulateTrack(energyCurrent, xCurrent, yCurrent); // Updates the Po 210 alphas position.

    Po210Alpha.energy = energyCurrent; // Updates the alphas energy.
    Po210Alpha.movementLocation = Po210Alpha.movementLocation + 1; // Increases the alphas movemement location by 1 as we are now at the next location.
    return Po210Alpha; // Returns this new Po 210 alpha.
  }
  else { // If the alpha has left the detector or has no more energy...
    if (checkPo210AlphaElectronDist() == false) { // If all the electrons and ions are still within the displayed detector.
      displayDetector(displayEnergyLevel); // Displays the detector.
      int numIons = 0;
      for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For every position in the array...
        Po210AlphaElectrons[loc] = computeNextElectronLocation(Po210AlphaElectrons[loc]); // Computes and moves the electon through its current step.
        if (Po210AlphaElectrons[loc].rLocation < 2048)
          numIons = numIons + 1;
        Serial.println(numIons);
        displayCurrentMeasured(numIons);
      }
      return Po210Alpha; // Returns the Po 210 alpha which will continue to meet all the requirements to enter this section of the code as well.
    }
    else { // If all the electrons or ions are outside the displayed detector.
      Po210AlphaDone = true; // The Po 210 alpha boolean variable can be set to true as it is complete.
      Alpha newPo210Alpha = createNewPo210Alpha(); // Create a new Po 210 alpha as the ions and electrons have finished drifting.
      return newPo210Alpha; // Returns the new Po 210 alpha so that when the Po 210 button is pressed a new Po 210 alpha can be displayed.
    }
  }
}

/* Alpha computeNextRn222AlphaLocation(Alpha Rn222Alpha)

   Determines the next location for which a given Rn 222 alpha will move along with determining if an electron should appear and controlling said electrons.

*/
Alpha computeNextRn222AlphaLocation(Alpha Rn222Alpha) {
  int energyChangeLowerBounds = 300; // The smallest energy value the alpha can "lose" to an electron. Default is 300 keV.
  int energyChangeUpperBounds = 400; // The largest energy value the alpha can "lose" to an electron. Default is 400 keV.

  randomSeed(0); // Randomizes the seed.
  int xCurrent = Rn222Alpha.xMovementPath[Rn222Alpha.movementLocation]; // Saves the passed in xLocation, yLocation, and energy values.
  int yCurrent = Rn222Alpha.yMovementPath[Rn222Alpha.movementLocation];
  int energyCurrent = Rn222Alpha.energy;

  if (Rn222Alpha.movementLocation < numberOfParticleSteps) { // If the alpha can exist.
    int energyChange = random(energyChangeLowerBounds, energyChangeUpperBounds); // Calculates the energy change that the electron will gain if created in keV.
    Rn222AlphaElectrons[Rn222AlphaElectronLocation] = generateElectron(xCurrent, yCurrent, energyChange); // Generates an electron and saves it.
    energyCurrent = energyCurrent - energyChange; // Lowers the energy of the alpha.
    Rn222AlphaElectronLocation++; // Increases the count for which the next electron will be added into the array.

    if (Rn222AlphaElectronLocation == numElectronLocationsInArray) // If the array is filled rotate around and start filling it again.
      Rn222AlphaElectronLocation = 0; // Resets the array position counter to 0.

    for (int loc = 0; loc < numElectronLocationsInArray; loc++)  // For every position in the array...
      Rn222AlphaElectrons[loc] = computeNextElectronLocation(Rn222AlphaElectrons[loc]); // Computes and moves the electon through its current step.

    if (delayTime != 0 ) {
      int currentTime = millis(); int enteredTime = millis();
      while (currentTime < enteredTime + delayTime) {
        currentTime = millis();
        simulateTrack(energyCurrent, xCurrent, yCurrent); // Updates the Rn 222 position.
        displayDetector(displayEnergyLevel);
      }
    }
    else
      simulateTrack(energyCurrent, xCurrent, yCurrent); // Updates the Rn 222 position.

    Rn222Alpha.energy = energyCurrent; // Updates the energy of the Rn 222 alpha.
    Rn222Alpha.movementLocation = Rn222Alpha.movementLocation + 1; // Increases the alphas movemement location by 1 as we are now at the next location.
    return Rn222Alpha; // Returns this new alpha.
  }
  else { // If the alpha has left the detector or has no more energy...
    if (checkRn222AlphaElectronDist() == false) { // If the electrons or ions are still within the detector then.
      displayDetector(displayEnergyLevel); // Displays the detector.
      int numIons = 0;
      for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For every position in the array...
        Rn222AlphaElectrons[loc] = computeNextElectronLocation(Rn222AlphaElectrons[loc]); // Computes and moves the electon through its current step.
        if (Rn222AlphaElectrons[loc].rLocation < 2048)
          numIons = numIons + 1;
        Serial.println(numIons);
        displayCurrentMeasured(numIons);
      }
      return Rn222Alpha; // Return the Rn 222 alpha as the alphas properties hasnt been changed and will continue to enter this segment of the code allowing for multiple
      // particles to be displayed at once.
    }
    else {
      Rn222AlphaDone = true; // Sets the boolean variable for Rn 222 to true meaning the particle has finished tracking.
      Alpha newRn222Alpha = createNewRn222Alpha(); // Create a new Rn 222.
      return newRn222Alpha; // Returns the new Rn 222 alpha so that the infinite loop can be continued.
    }
  }
}

#endif
