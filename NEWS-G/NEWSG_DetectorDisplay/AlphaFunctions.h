#ifndef ALPHAFUNCTIONS_H
#define ALPHAFUNCTIONS_H

#include "CommonFunctions.h"
#include "CosmicRayFunctions.h"
#include "ElectronFunctions.h"
#include "XRayFunctions.h"

Electron Po210AlphaElectrons[11]; // Creates an array of 11 Po210 electrons. The value within the array needs to be equal to that of the numElectronLocationInArray variable.
Electron Rn222AlphaElectrons[11]; // Creates an array of 11 Rn222 electrons. The value within the array needs to be equal to that of the numElectronLocationInArray variable.

// Creates an Alpha struct. An alpha is made up of two array, one for the x movement locations and one for the y movement locations, an energy value, and a movement location
// variable to keep track of the current location at which the particle is at in the movement arrays.
typedef struct Alpha {
  int xMovementPath[11];
  int yMovementPath[11];
  int energy;
  int movementLocation;
} Alpha;

Alpha po210alpha1; // Creates two different alphas - one is a Po210 alpha and the other is a Rn222 alpha.
Alpha rn222alpha1;

// An array containing 6 different movement possibilities for quadrant 1 in the x direction for the alpha particles produced from Po210.
int xMPPFQ1Po210[6][11] = {
  {283, 146, 1, -120, -220, -306, -392, -480, -566, -634, -690},
  {720, 810, 920, 1024, 1098, 1022, 941, 862, 750, 670, 600},
  {1970, 1752, 1544, 1332, 1141, 910, 704, 528, 401, 329, 276},
  {1972, 1791, 1578, 1352, 1153, 931, 752, 579, 401, 258, 100},
  {1870, 1730, 1560, 1420, 1280, 1160, 1110, 1030, 970, 900, 850},
  {1370, 1320, 1240, 1200, 1160, 1090, 1050, 1000, 950, 930, 900}
};

// An array containing 6 different movement possibilities for quadrant 1 in the y direction for the alpha particles produced from Po210.
int yMPPFQ1Po210[6][11] = {
  {2000, 1864, 1745, 1636, 1540, 1458, 1370, 1293, 1227, 1165, 1120},
  {1910, 1690, 1480, 1248, 1026, 869, 738, 634, 510, 410, 280},
  {240, 363, 468, 603, 651, 682, 669, 723, 842, 986, 1121},
  {246, 98, -62, -200, -333, -456, -561, -663, -728, -792, -871},
  {760, 790, 790, 780, 780, 770, 750, 760, 760, 760, 755},
  {1490, 1370, 1260, 1170, 1110, 1040, 940, 880, 810, 790, 770}
};

// An array containing 6 different movement possibilities for quadrant 1 in the x direction for the alpha particles produced from Rn222.
int xMPPFQ1Rn222[6][11] = {
  {165, 220, 290, 354, 420, 466, 504, 523, 560, 603, 645},
  {550, 448, 335, 230, 123, -10, -126, -220, -286, -366, -446},
  {1337, 1313, 1266, 1220, 1153, 1083, 1017, 960, 910, 857, 805},
  {744, 777, 814, 860, 923, 1000, 1070, 1140, 1205, 1266, 1346},
  {810, 900, 960, 1000, 1010, 1030, 1050, 1140, 1233, 1330, 1402},
  {1510, 1402, 1300, 1195, 1115, 1026, 960, 930, 930, 923, 910}
};

// An array containing 6 different movement possibilities for quadrant 1 in the y direction for the alpha particles produced from Rn222.
int yMPPFQ1Rn222[6][11] = {
  {566, 665, 773, 886, 1000, 1110, 1220, 1300, 1356, 1430, 1483},
  {1590, 1507, 1417, 1366, 1310, 1234, 1150, 1093, 1055, 1020, 990},
  {434, 550, 674, 790, 895, 1000, 1017, 1178, 1240, 1300, 1356},
  {627, 514, 400, 290, 185, 86, -17, -97, -150, -200, -240},
  {1676, 1563, 1464, 1350, 1225, 1107, 985, 905, 905, 933, 960},
  {160, 230, 303, 397, 463, 530, 604, 693, 782, 867, 938}
};

/* bool checkPo210AlphaElectronDist()

    Returns false if the Po210 electrons have a distance greater then the specified distance away from the center of the detector. If all the electrons are within the specified
    distance from the center of the detector return true.

*/
bool checkPo210AlphaElectronDist() {
  for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For each variable in the electron array.
    if (Po210AlphaElectrons[loc].rLocation > 20) { // Check to see if the radial location is greater then 20.
      return false; // If one of the radial distances is over 20 return false and keep the electrons drifting towards the center of the circle.
    }
  }
  return true; // If all electrons are within a radial distance of 20 then return true and stop the electrons from drifting within the detector.
}

/* bool checkRn222AlphaElectronDist()

    Returns false if the Rn222 electrons have a distance greater then the specified distance away from the center of the detector. If all the electrons are within the specified
    distance from the center of the detector return true.

*/
bool checkRn222AlphaElectronDist() {
  for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For each variable in the electron array.
    if (Rn222AlphaElectrons[loc].rLocation > 20) { // Check to see if the radial location is greater then 20.
      return false; // If one of the radial distances is over 20 return false and keep the electrons drifting towards the center of the circle.
    }
  }
  return true; // If all electrons are within a radial distance of 20 then return true and stop the electrons from drifting within the detector.
}

/* Alpha createNewPo210Alpha()

   Creates a new Po210 Alpha particle with random properties.

*/
Alpha createNewPo210Alpha() {

  const int maxSINCOSvalue = 16384; // The largest value that can be returned from the SIN and COS functions as declared in Basics.cpp. This should remain 16384.

  randomSeed(0); // Randomizes the seed. This in theory adds another layer of random to the code.
  int pathNumber = random(0, 6); // Picks a random number from 0 to 5 for the path number.
  int quadrantNumber = random(1, 5); // Picks a random number between 1 to 4 for the quadrant for the particle to start tracking in.
  int Po210alphaEnergy = 5300; // Each Po210 generates with 5300 keV.
  int arrayStartLocation = 0; // The starting array location.

  Serial.print("Po 210: "); Serial.print(pathNumber); Serial.print("\t"); Serial.println(quadrantNumber); // Displays the quadrant and track type that is going to be displayed.

  Alpha newPo210Alpha;

  if (quadrantNumber ==  1) { // If the partcle will appear in quadrant one.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For each location that the particle will move.
      newPo210Alpha.xMovementPath[loc] = xMPPFQ1Po210[pathNumber][loc]; // Fills the movement arrays for the x positions.
      newPo210Alpha.yMovementPath[loc] = yMPPFQ1Po210[pathNumber][loc]; // Fills the movement arrays for the y positions.
    }
    newPo210Alpha.energy = Po210alphaEnergy; // Sets the particles energy location.
    newPo210Alpha.movementLocation = arrayStartLocation; // Sets the particles movement location to 0.
  }
  else if (quadrantNumber ==  2) { // If the partcle will appear in quadrant two.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For each location that the particle will move.
      newPo210Alpha.xMovementPath[loc] = -1 * xMPPFQ1Po210[pathNumber][loc]; // Fills the movement arrays for the x positions.
      newPo210Alpha.yMovementPath[loc] = yMPPFQ1Po210[pathNumber][loc]; // Fills the movement arrays for the y positions.
    }
    newPo210Alpha.energy = Po210alphaEnergy; // Sets the particles energy location.
    newPo210Alpha.movementLocation = arrayStartLocation; // Sets the particles movement location to 0.
  }
  else if (quadrantNumber ==  3) { // If the partcle will appear in quadrant three.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For each location that the particle will move.
      newPo210Alpha.xMovementPath[loc] = -1 * xMPPFQ1Po210[pathNumber][loc]; // Fills the movement arrays for the x positions.
      newPo210Alpha.yMovementPath[loc] = -1 * yMPPFQ1Po210[pathNumber][loc]; // Fills the movement arrays for the y positions.
    }
    newPo210Alpha.energy = Po210alphaEnergy; // Sets the particles energy location.
    newPo210Alpha.movementLocation = arrayStartLocation; // Sets the particles movement location to 0.
  }
  else if (quadrantNumber ==  4) { // If the partcle will appear in quadrant four.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For each location that the particle will move.
      newPo210Alpha.xMovementPath[loc] = xMPPFQ1Po210[pathNumber][loc]; // Fills the movement arrays for the x positions.
      newPo210Alpha.yMovementPath[loc] = -1 * yMPPFQ1Po210[pathNumber][loc]; // Fills the movement arrays for the y positions.
    }
    newPo210Alpha.energy = Po210alphaEnergy; // Sets the particles energy location.
    newPo210Alpha.movementLocation = arrayStartLocation; // Sets the particles movement location to 0.
  }
  return newPo210Alpha; // Returns this new alpha with the correct values.
}

/* Alpha createNewRn222Alpha()

   Creates a new Rn 222 Alpha particle with random properties.

*/
Alpha createNewRn222Alpha() {

  const int maxSINCOSvalue = 16384; // The largest value that can be returned from the SIN and COS functions as declared in Basics.cpp. This should remain 16384.

  randomSeed(0); // Randomizes the seed. This in theory adds another layer of random to the code.
  int pathNumber = random(0, 6); // Picks a random number from 0 to 5 for the path number.
  int quadrantNumber = random(1, 5); // Picks a random number between 1 to 4 for the quadrant for the particle to start tracking in.
  int Rn222alphaEnergy = 5500; // Each Rn 222 alpha generates with 5500 keV.
  int arrayStartLocation = 0; // The starting array location.

  Serial.print("Rn 222: "); Serial.print(pathNumber); Serial.print("\t"); Serial.println(quadrantNumber); // Displays the quadrant and track type that is going to be displayed.

  Alpha newRn222Alpha;

  if (quadrantNumber ==  1) { // If the partcle will appear in quadrant one.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For each location that the particle will move.
      newRn222Alpha.xMovementPath[loc] = xMPPFQ1Rn222[pathNumber][loc]; // Fills the movement arrays for the x positions.
      newRn222Alpha.yMovementPath[loc] = yMPPFQ1Rn222[pathNumber][loc]; // Fills the movement arrays for the y positions.
    }
    newRn222Alpha.energy = Rn222alphaEnergy; // Sets the particles energy location.
    newRn222Alpha.movementLocation = arrayStartLocation; // Sets the particles movement location to 0.
  }
  else if (quadrantNumber ==  2) { // If the partcle will appear in quadrant two.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For each location that the particle will move.
      newRn222Alpha.xMovementPath[loc] = -1 * xMPPFQ1Rn222[pathNumber][loc]; // Fills the movement arrays for the x positions.
      newRn222Alpha.yMovementPath[loc] = yMPPFQ1Rn222[pathNumber][loc]; // Fills the movement arrays for the y positions.
    }
    newRn222Alpha.energy = Rn222alphaEnergy; // Sets the particles energy location.
    newRn222Alpha.movementLocation = arrayStartLocation; // Sets the particles movement location to 0.
  }
  else if (quadrantNumber ==  3) { // If the partcle will appear in quadrant three.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For each location that the particle will move.
      newRn222Alpha.xMovementPath[loc] = -1 * xMPPFQ1Rn222[pathNumber][loc]; // Fills the movement arrays for the x positions.
      newRn222Alpha.yMovementPath[loc] = -1 * yMPPFQ1Rn222[pathNumber][loc]; // Fills the movement arrays for the y positions.
    }
    newRn222Alpha.energy = Rn222alphaEnergy; // Sets the particles energy location.
    newRn222Alpha.movementLocation = arrayStartLocation; // Sets the particles movement location to 0.
  }
  else if (quadrantNumber ==  4) { // If the partcle will appear in quadrant four.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For each location that the particle will move.
      newRn222Alpha.xMovementPath[loc] = xMPPFQ1Rn222[pathNumber][loc]; // Fills the movement arrays for the x positions.
      newRn222Alpha.yMovementPath[loc] = -1 * yMPPFQ1Rn222[pathNumber][loc]; // Fills the movement arrays for the y positions.
    }
    newRn222Alpha.energy = Rn222alphaEnergy; // Sets the particles energy location.
    newRn222Alpha.movementLocation = arrayStartLocation; // Sets the particles movement location to 0.
  }
  return newRn222Alpha; // Returns this new Rn 222 alpha.
}

/* Alpha computeNextPo210AlphaLocation(Alpha Po210Alpha)

   Determines the next location for which a given Po210 Alpha will move along with determining if an electron should appear and controlling said electrons.

*/
Alpha computeNextPo210AlphaLocation(Alpha Po210Alpha) {
  int energyChangeLowerBounds = 300; // The smallest energy value the alpha can "lose" in one step to an electron. Default is 300 keV.
  int energyChangeUpperBounds = 400; // The largest energy value the alpha can "lose" in one step to an electron. Default is 400 keV.

  randomSeed(0); // Randomizes the seed.

  int xCurrent = Po210Alpha.xMovementPath[Po210Alpha.movementLocation]; // Saves the passed in xLocation, yLocation, and energy values.
  int yCurrent = Po210Alpha.yMovementPath[Po210Alpha.movementLocation];
  int energyCurrent = Po210Alpha.energy;

  if (Po210Alpha.movementLocation < numberOfParticleSteps) { // If the alpha can exist.
    int energyChange = random(energyChangeLowerBounds, energyChangeUpperBounds); // Calculates the energy change that the electron will gain if created in keV.
    Po210AlphaElectrons[alphaElectronLocation] = generateElectron(xCurrent, yCurrent, energyChange); // Generates an electron and saves it.
    energyCurrent = energyCurrent - energyChange; // Lowers the energy of the alpha.
    alphaElectronLocation++; // Increases the count for which the next electron will be added into the array.

    if (alphaElectronLocation == numElectronLocationsInArray) // If the array is filled rotate around and start filling it again.
      alphaElectronLocation = 0; // Resets the array position counter to 0.

    for (int loc = 0; loc < numElectronLocationsInArray; loc++)  // For every position in the array...
      Po210AlphaElectrons[loc] = computeNextElectronLocation(Po210AlphaElectrons[loc]); // Computes and moves the electon through its current step.

    simulateTrack(energyCurrent, xCurrent, yCurrent); // Displays the alphas position.
    Po210Alpha.energy = energyCurrent; // Updates the current energy of the particle.
    Po210Alpha.movementLocation = Po210Alpha.movementLocation + 1; // Increases the movement location variable by 1.
    return Po210Alpha; // Returns this new Alpha.
  }
  else { // If the alpha has finished its set path.
    Po210AlphaDone = true;
    Alpha newPo210Alpha = createNewPo210Alpha(); // Create a new alpha.
    while (checkPo210AlphaElectronDist() == false) { // While the electrons have not drifted towards the center of the detector.
      displayDetector(); // Display the detector.
      for (int loc = 0; loc < numElectronLocationsInArray; loc++) // For every position in the array...
        Po210AlphaElectrons[loc] = computeNextElectronLocation(Po210AlphaElectrons[loc]); // Computes and moves the electon through its current step.
    }
    return newPo210Alpha; // Returns the new Po210 alpha so that the infinite loop can be continued.
  }
}

/* Alpha computeNextRn222AlphaLocation(Alpha Rn222Alpha)

   Determines the next location for which a given Rn 222 alpha will move along with determining if an electron should appear and controlling said electrons.

*/
Alpha computeNextRn222AlphaLocation(Alpha Rn222Alpha) {
  int energyChangeLowerBounds = 300; // The smallest energy value the alpha can "lose" in one step. This is the minimum energy that can be transfered to an electron. Default is 60 keV.
  int energyChangeUpperBounds = 400; // The largest energy value the alpha can "lose" in one step. This is the maxium energy that can be transfered to an electron. Default is 100 keV.

  randomSeed(0); // Randomizes the seed.

  int xCurrent = Rn222Alpha.xMovementPath[Rn222Alpha.movementLocation]; // Saves the passed in xLocation, yLocation, and energy values.
  int yCurrent = Rn222Alpha.yMovementPath[Rn222Alpha.movementLocation];
  int energyCurrent = Rn222Alpha.energy;

  if (Rn222Alpha.movementLocation < numberOfParticleSteps) { // If the alpha can exist.
    int energyChange = random(energyChangeLowerBounds, energyChangeUpperBounds); // Calculates the energy change that the electron will gain if created in keV.
    Rn222AlphaElectrons[alphaElectronLocation] = generateElectron(xCurrent, yCurrent, energyChange); // Generates an electron and saves it.
    energyCurrent = energyCurrent - energyChange; // Lowers the energy of the alpha.
    alphaElectronLocation++; // Increases the count for which the next electron will be added into the array.

    if (alphaElectronLocation == numElectronLocationsInArray) // If the array is filled rotate around and start filling it again.
      alphaElectronLocation = 0; // Resets the array position counter to 0.

    for (int loc = 0; loc < numElectronLocationsInArray; loc++)  // For every position in the array...
      Rn222AlphaElectrons[loc] = computeNextElectronLocation(Rn222AlphaElectrons[loc]); // Computes and moves the electon through its current step.

    simulateTrack(energyCurrent, xCurrent, yCurrent); // Displays the alphas position.
    Rn222Alpha.energy = energyCurrent; // Updates the energy variable.
    Rn222Alpha.movementLocation = Rn222Alpha.movementLocation + 1; // Updated the movement location varaible by increasing it by one.
    return Rn222Alpha; // Returns this new Alpha.
  }
  else { // If the alpha has finished its set path.
    Rn222AlphaDone = true;
    Alpha newRn222Alpha = createNewRn222Alpha(); // Create a new alpha.

    while (checkRn222AlphaElectronDist() == false) { // If the Rn 222 electrons haven't reached the middle of the detector yet. 
      displayDetector(); // Displays the detector.
      for (int loc = 0; loc < numElectronLocationsInArray; loc++) // For every position in the array...
        Rn222AlphaElectrons[loc] = computeNextElectronLocation(Rn222AlphaElectrons[loc]); // Computes and moves the electon through its current step.
    }
    return newRn222Alpha; // Returns the new Rn222 alpha so that the infinite loop can be continued.
  }
}

#endif
