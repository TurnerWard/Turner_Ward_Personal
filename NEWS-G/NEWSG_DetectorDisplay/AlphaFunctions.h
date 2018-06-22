
#ifndef ALPHAFUNCTIONS_H
#define ALPHAFUNCTIONS_H

#include "CommonFunctions.h"
#include "CosmicRayFunctions.h"
#include "ElectronFunctions.h"
#include "XRayFunctions.h"

Electron alphaElectrons[11]; // Creates an array of 6 electrons. The value within the array needs to be equal to that of the numElectronLocationInArray variable.

// Creates an Alpha struct. An alpha is made up of a x location, a y location, an energy, and a constant value for the movement in both the x direction and y direction as well as
// a total distance it can travel and a varible to track its distance.
typedef struct Alpha {
  int xMovementPath[11];
  int yMovementPath[11];
  int energy;
  int movementLocation;
} Alpha;

Alpha po210alpha1;
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

/* bool checkAlphaElectronDist()

    Returns false if the electrons have a distance greater then the specified distance away from the center of the detector. If all the electrons are within the specified distance
    from the center of the detector return true.

*/
bool checkAlphaElectronDist() {
  for (int loc = 0; loc < numElectronLocationsInArray; loc++) {
    if (alphaElectrons[loc].rLocation > 20) {
      return false;
    }
  }
  return true;
}

/* Alpha createNewPo210Alpha()

   Creates a new Po210 Alpha particle with random properties.

*/
Alpha createNewPo210Alpha() {

  const int maxSINCOSvalue = 16384; // The largest value that can be returned from the SIN and COS functions as declared in Basics.cpp. This should remain 16384.

  randomSeed(0); // Randomizes the seed. This in theory adds another layer of random to the code.
  int pathNumber = random(0, 6); // Picks a random number from 0 to 5.
  int quadrantNumber = random(1, 5); // Picks a random number between 1 to 4.
  int Po210alphaEnergy = 5300; // Should be 5300. In keV.
  int arrayStartLocation = 0;

  Serial.print("Po 210: "); Serial.print(pathNumber); Serial.print("\t"); Serial.println(quadrantNumber);

  Alpha newPo210Alpha;

  for (int loc = 0; loc < 11; loc++) {
    if (quadrantNumber ==  1) {
      for (int loc = 0; loc < 11; loc++) {
        newPo210Alpha.xMovementPath[loc] = xMPPFQ1Po210[pathNumber][loc]; // Fills the movement arrays.
        newPo210Alpha.yMovementPath[loc] = yMPPFQ1Po210[pathNumber][loc];
      }
      newPo210Alpha.energy = Po210alphaEnergy;
      newPo210Alpha.movementLocation = 0; // Creates the new cosmic ray with the new values.
    }
    else if (quadrantNumber ==  2) {
      for (int loc = 0; loc < 11; loc++) {
        newPo210Alpha.xMovementPath[loc] = -1 * xMPPFQ1Po210[pathNumber][loc]; // Fills the movement arrays.
        newPo210Alpha.yMovementPath[loc] = yMPPFQ1Po210[pathNumber][loc];
      }
      newPo210Alpha.energy = Po210alphaEnergy;
      newPo210Alpha.movementLocation = 0; // Creates the new cosmic ray with the new values.
    }
    else if (quadrantNumber ==  3) {
      for (int loc = 0; loc < 11; loc++) {
        newPo210Alpha.xMovementPath[loc] = -1 * xMPPFQ1Po210[pathNumber][loc]; // Fills the movement arrays.
        newPo210Alpha.yMovementPath[loc] = -1 * yMPPFQ1Po210[pathNumber][loc];
      }
      newPo210Alpha.energy = Po210alphaEnergy;
      newPo210Alpha.movementLocation = 0; // Creates the new cosmic ray with the new values.
    }
    else if (quadrantNumber ==  4) {
      for (int loc = 0; loc < 11; loc++) {
        newPo210Alpha.xMovementPath[loc] = xMPPFQ1Po210[pathNumber][loc]; // Fills the movement arrays.
        newPo210Alpha.yMovementPath[loc] = -1 * yMPPFQ1Po210[pathNumber][loc];
      }
      newPo210Alpha.energy = Po210alphaEnergy;
      newPo210Alpha.movementLocation = 0; // Creates the new cosmic ray with the new values.
    }
  }
  return newPo210Alpha; // Returns this new alpha.
}

/* Alpha createNewPo210Alpha()

   Creates a new Alpha particle with random properties.

*/
Alpha createNewRn222Alpha() {

  const int maxSINCOSvalue = 16384; // The largest value that can be returned from the SIN and COS functions as declared in Basics.cpp. This should remain 16384.

  randomSeed(0); // Randomizes the seed. This in theory adds another layer of random to the code.
  int pathNumber = random(0, 6); // Picks a random number from 0 to 5.
  int quadrantNumber = random(1, 5); // Picks a random number between 1 to 4.
  int Rn222alphaEnergy = 5500; // Should be 5500. Stated in keV.
  int arrayStartLocation = 0;

  Serial.print("Rn 222: "); Serial.print(pathNumber); Serial.print("\t"); Serial.println(quadrantNumber);

  Alpha newRn222Alpha;

  for (int loc = 0; loc < 11; loc++) {
    if (quadrantNumber ==  1) {
      newRn222Alpha = {{
          xMPPFQ1Rn222[pathNumber][0], xMPPFQ1Rn222[pathNumber][1], xMPPFQ1Rn222[pathNumber][2], xMPPFQ1Rn222[pathNumber][3], xMPPFQ1Rn222[pathNumber][4], xMPPFQ1Rn222[pathNumber][5],
          xMPPFQ1Rn222[pathNumber][6], xMPPFQ1Rn222[pathNumber][7], xMPPFQ1Rn222[pathNumber][8], xMPPFQ1Rn222[pathNumber][9], xMPPFQ1Rn222[pathNumber][10]
        },
        { yMPPFQ1Rn222[pathNumber][0], yMPPFQ1Rn222[pathNumber][1], yMPPFQ1Rn222[pathNumber][2], yMPPFQ1Rn222[pathNumber][3], yMPPFQ1Rn222[pathNumber][4], yMPPFQ1Rn222[pathNumber][5],
          yMPPFQ1Rn222[pathNumber][6], yMPPFQ1Rn222[pathNumber][7], yMPPFQ1Rn222[pathNumber][8], yMPPFQ1Rn222[pathNumber][9], yMPPFQ1Rn222[pathNumber][10]
        },
        Rn222alphaEnergy, arrayStartLocation
      }; // Creates the new Rn 222 alpha with the new values.
    }
    else if (quadrantNumber ==  2) {
      newRn222Alpha = {{
          -1 * xMPPFQ1Rn222[pathNumber][0], -1 * xMPPFQ1Rn222[pathNumber][1], -1 * xMPPFQ1Rn222[pathNumber][2], -1 * xMPPFQ1Rn222[pathNumber][3], -1 * xMPPFQ1Rn222[pathNumber][4],
          -1 * xMPPFQ1Rn222[pathNumber][5], -1 * xMPPFQ1Rn222[pathNumber][6], -1 * xMPPFQ1Rn222[pathNumber][7], -1 * xMPPFQ1Rn222[pathNumber][8], -1 * xMPPFQ1Rn222[pathNumber][9],
          -1 * xMPPFQ1Rn222[pathNumber][10]
        }, {
          yMPPFQ1Rn222[pathNumber][0], yMPPFQ1Rn222[pathNumber][1], yMPPFQ1Rn222[pathNumber][2], yMPPFQ1Rn222[pathNumber][3], yMPPFQ1Rn222[pathNumber][4], yMPPFQ1Rn222[pathNumber][5],
          yMPPFQ1Rn222[pathNumber][6], yMPPFQ1Rn222[pathNumber][7], yMPPFQ1Rn222[pathNumber][8], yMPPFQ1Rn222[pathNumber][9], yMPPFQ1Rn222[pathNumber][10]
        }, Rn222alphaEnergy, arrayStartLocation
      }; // Creates the new alpha with the new values.
    }
    else if (quadrantNumber ==  3) {
      newRn222Alpha = {{
          -1 * xMPPFQ1Rn222[pathNumber][0], -1 * xMPPFQ1Rn222[pathNumber][1], -1 * xMPPFQ1Rn222[pathNumber][2], -1 * xMPPFQ1Rn222[pathNumber][3], -1 * xMPPFQ1Rn222[pathNumber][4],
          -1 * xMPPFQ1Rn222[pathNumber][5], -1 * xMPPFQ1Rn222[pathNumber][6], -1 * xMPPFQ1Rn222[pathNumber][7], -1 * xMPPFQ1Rn222[pathNumber][8], -1 * xMPPFQ1Rn222[pathNumber][9],
          -1 * xMPPFQ1Rn222[pathNumber][10]
        },
        { -1 * yMPPFQ1Rn222[pathNumber][0], -1 * yMPPFQ1Rn222[pathNumber][1], -1 * yMPPFQ1Rn222[pathNumber][2], -1 * yMPPFQ1Rn222[pathNumber][3], -1 * yMPPFQ1Rn222[pathNumber][4],
          -1 * yMPPFQ1Rn222[pathNumber][5], -1 * yMPPFQ1Rn222[pathNumber][6], -1 * yMPPFQ1Rn222[pathNumber][7], -1 * yMPPFQ1Rn222[pathNumber][8], -1 * yMPPFQ1Rn222[pathNumber][9],
          -1 * yMPPFQ1Rn222[pathNumber][10]
        },
        Rn222alphaEnergy, arrayStartLocation
      }; // Creates the new alpha with the new values.
    }
    else if (quadrantNumber ==  4) {
      newRn222Alpha = {{
          xMPPFQ1Rn222[pathNumber][0], xMPPFQ1Rn222[pathNumber][1], xMPPFQ1Rn222[pathNumber][2], xMPPFQ1Rn222[pathNumber][3], xMPPFQ1Rn222[pathNumber][4], xMPPFQ1Rn222[pathNumber][5],
          xMPPFQ1Rn222[pathNumber][6], xMPPFQ1Rn222[pathNumber][7], xMPPFQ1Rn222[pathNumber][8], xMPPFQ1Rn222[pathNumber][9], xMPPFQ1Rn222[pathNumber][10]
        },
        { -1 * yMPPFQ1Rn222[pathNumber][0], -1 * yMPPFQ1Rn222[pathNumber][1], -1 * yMPPFQ1Rn222[pathNumber][2], -1 * yMPPFQ1Rn222[pathNumber][3], -1 * yMPPFQ1Rn222[pathNumber][4],
          -1 * yMPPFQ1Rn222[pathNumber][5], -1 * yMPPFQ1Rn222[pathNumber][6], -1 * yMPPFQ1Rn222[pathNumber][7], -1 * yMPPFQ1Rn222[pathNumber][8], -1 * yMPPFQ1Rn222[pathNumber][9],
          -1 * yMPPFQ1Rn222[pathNumber][10]
        },
        Rn222alphaEnergy, arrayStartLocation
      }; // Creates the new Rn 222 alpha with the new values.
    }
  }
  return newRn222Alpha; // Returns this new Rn 222 alpha.
}

/* Alpha computeNextAlphaLocation(Alpha alpha)

   Determines the next location for which a given alpha will move along with determining if an electron should appear and controlling said electrons.

*/
Alpha computeNextPo210AlphaLocation(Alpha Po210Alpha) {
  int energyChangeLowerBounds = 300; // The smallest energy value the alpha can "lose" in one step. This is the minimum energy that can be transfered to an electron. Default is 60 keV.
  int energyChangeUpperBounds = 400; // The largest energy value the alpha can "lose" in one step. This is the maxium energy that can be transfered to an electron. Default is 100 keV.

  randomSeed(0); // Randomizes the seed.

  int xCurrent = Po210Alpha.xMovementPath[Po210Alpha.movementLocation]; // Saves the passed in xLocation, yLocation, and energy values.
  int yCurrent = Po210Alpha.yMovementPath[Po210Alpha.movementLocation];
  int energyCurrent = Po210Alpha.energy;

  if (Po210Alpha.movementLocation < 11) { // If the alpha can exist.
    int energyChange = random(energyChangeLowerBounds, energyChangeUpperBounds); // Calculates the energy change that the electron will gain if created in keV.
    alphaElectrons[alphaElectronLocation] = generateElectron(xCurrent, yCurrent, energyChange); // Generates an electron and saves it.
    energyCurrent = energyCurrent - energyChange; // Lowers the energy of the alpha.
    alphaElectronLocation++; // Increases the count for which the next electron will be added into the array.

    if (alphaElectronLocation == numElectronLocationsInArray) // If the array is filled rotate around and start filling it again.
      alphaElectronLocation = 0; // Resets the array position counter to 0.


    for (int loc = 0; loc < numElectronLocationsInArray; loc++)  // For every position in the array...
      alphaElectrons[loc] = computeNextElectronLocation(alphaElectrons[loc]); // Computes and moves the electon through its current step.

    simulateTrack(energyCurrent, xCurrent, yCurrent); // Updates the alphas position.
    Po210Alpha.energy = energyCurrent;
    Po210Alpha.movementLocation = Po210Alpha.movementLocation + 1; // Creates the new alpha with the new values.
    return Po210Alpha; // Returns this new electron.
  }
  else { // If the alpha has left the detector or has no more energy...
    Po210AlphaDone = true;
    Alpha newPo210Alpha = createNewPo210Alpha(); // Create a new alpha.
    while (checkAlphaElectronDist() == false) {
      displayDetector();
      for (int loc = 0; loc < numElectronLocationsInArray; loc++) // For every position in the array...
        alphaElectrons[loc] = computeNextElectronLocation(alphaElectrons[loc]); // Computes and moves the electon through its current step.
    }
    return newPo210Alpha; // Returns the new alpha so that the infinite loop can be continued.
  }
}

/* Alpha computeNextAlphaLocation(Alpha alpha)

   Determines the next location for which a given alpha will move along with determining if an electron should appear and controlling said electrons.

*/
Alpha computeNextRn222AlphaLocation(Alpha Rn222Alpha) {
  int energyChangeLowerBounds = 300; // The smallest energy value the alpha can "lose" in one step. This is the minimum energy that can be transfered to an electron. Default is 60 keV.
  int energyChangeUpperBounds = 400; // The largest energy value the alpha can "lose" in one step. This is the maxium energy that can be transfered to an electron. Default is 100 keV.

  randomSeed(0); // Randomizes the seed.

  int xCurrent = Rn222Alpha.xMovementPath[Rn222Alpha.movementLocation]; // Saves the passed in xLocation, yLocation, and energy values.
  int yCurrent = Rn222Alpha.yMovementPath[Rn222Alpha.movementLocation];
  int energyCurrent = Rn222Alpha.energy;

  if (Rn222Alpha.movementLocation < 11) { // If the alpha can exist.
    int energyChange = random(energyChangeLowerBounds, energyChangeUpperBounds); // Calculates the energy change that the electron will gain if created in keV.
    alphaElectrons[alphaElectronLocation] = generateElectron(xCurrent, yCurrent, energyChange); // Generates an electron and saves it.
    energyCurrent = energyCurrent - energyChange; // Lowers the energy of the alpha.
    alphaElectronLocation++; // Increases the count for which the next electron will be added into the array.

    if (alphaElectronLocation == numElectronLocationsInArray) // If the array is filled rotate around and start filling it again.
      alphaElectronLocation = 0; // Resets the array position counter to 0.

    for (int loc = 0; loc < numElectronLocationsInArray; loc++)  // For every position in the array...
      alphaElectrons[loc] = computeNextElectronLocation(alphaElectrons[loc]); // Computes and moves the electon through its current step.

    simulateTrack(energyCurrent, xCurrent, yCurrent); // Updates the alphas position.
    Rn222Alpha.energy = energyCurrent;
    Rn222Alpha.movementLocation = Rn222Alpha.movementLocation + 1; // Creates the new alpha with the new values.
    return Rn222Alpha; // Returns this new electron.
  }
  else { // If the alpha has left the detector or has no more energy...
    Rn222AlphaDone = true;
    Alpha newRn222Alpha = createNewRn222Alpha(); // Create a new alpha.

    while (checkAlphaElectronDist() == false) {
      displayDetector();
      for (int loc = 0; loc < numElectronLocationsInArray; loc++) // For every position in the array...
        alphaElectrons[loc] = computeNextElectronLocation(alphaElectrons[loc]); // Computes and moves the electon through its current step.
    }
    return newRn222Alpha; // Returns the new alpha so that the infinite loop can be continued.
  }
}

#endif
