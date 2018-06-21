
#ifndef NEWSG_ALPHAFUNCTIONS_H
#define NEWSG_ALPHAFUNCTIONS_H

#include "NEWSG_CommonFunctions.h"
#include "NEWSG_CosmicRayFunctions.h"
#include "NEWSG_ElectronFunctions.h"
#include "NEWSG_XRayFunctions.h"

Electron alphaElectrons[10]; // Creates an array of 6 electrons. The value within the array needs to be equal to that of the numElectronLocationInArray variable.

// Creates an Alpha struct. An alpha is made up of a x location, a y location, an energy, and a constant value for the movement in both the x direction and y direction as well as
// a total distance it can travel and a varible to track its distance.
typedef struct Alpha {
  int xLocation;
  int yLocation;
  int energy;
  int movementPath[20];
  int movementLocation;
} Alpha;

Alpha alpha1;

// An array containing 6 different movement possibilities for quadrant 1 in the x direction.
int xMovementPathPossibilitiesForQuadrant1[6][11] = {
  {283,146,1,-120,-220,-306,-392,-480,-566,-634,-690},
  {720,810,920,1024,1098,1022,941,862,750,670,600},
  {1970,1752,1544,1332,1141,910,704,528,401,329,276},
  {1972,1791,1578,1352,1153,931,752,579,401,258,100},
  {1870,1730,1560,1420,1280,1160,1110,1030,970,900,850},
  {1370,1320,1240,1200,1160,1090,1050,1000,950,930,900}
};

int yMovementPathPossibilitiesForQuadrant1[6][11] = {
  {2000,1864,1745,1636,1540,1458,1370,1293,1227,1165,1120},
  {1910,1690,1480,1248,1026,869,738,634,510,410,280},
  {240,363,468,603,651,682,669,723,842,986,1121},
  {246,98,-62,-200,-333,-456,-561,-663,-728,-792,-871},
  {760,790,790,780,780,770,750,760,760,760,755},
  {1490,1370,1260,1170,1110,1040,940,880,810,790,770}
};

bool checkElectronDist() {
  for(int loc = 0; loc < numElectronLocationsInArray; loc++) {
    if(alphaElectrons[loc].rLocation > 20){
      Serial.print("Over value: ");
      Serial.println(alphaElectrons[loc].rLocation);
      return false;
    }
  }
  return true;
}

bool checkAlphaDirection() {
  
}

/* Alpha createNewAlpha()

   Creates a new Alpha particle with random properties.

*/
Alpha createNewAlpha() {
  int rStartLowerBounds = 0; // The minimum radius value for which an alpha can be generated. Default is 2000.
  int rStartUpperBounds = 1900; // The maximum radius value for which an alpha can be generated. Default is 2048.
  int energyLowerBounds = 150; // The minimum energy for which an alpha can be generated in keV. Default is 150.
  int energyUpperBounds = 250; // The maximum energy for which an alpha can be generated in keV. Default is 250.
  int movementBounds = 75; // The largest step an alpha can move after appearing. Default is 25.
  int lowestSpeed = 75; // The lowest speed at which an alpha can travel. Default is 20.
  int lowestTotalMovementDistance = 1000;
  int highestTotalMovementDistance = 2000;

  const int maxSINCOSvalue = 16384; // The largest value that can be returned from the SIN and COS functions as declared in Basics.cpp. This should remain 16384.

  randomSeed(0); // Randomizes the seed. This in theory adds another layer of random to the code.

  int rCurrent = random(rStartLowerBounds, rStartUpperBounds); // Randomly returns the radius value for the alpha to start at between 1028 and 2048.
  int thetaCurrent = random(0, 360); // Randomly returns the theta value for the alpha to start at.
  int xCurrent = rCurrent * COS(thetaCurrent) / maxSINCOSvalue; // Converts from polar to cartesian where the movement of alpha particles are more easily replicated.
  int yCurrent = rCurrent * SIN(thetaCurrent) / maxSINCOSvalue; // Converts from polar to cartesian where the movement of alpha particles are more easily replicated.
  int energyCurrent = random(energyLowerBounds, energyUpperBounds); // Generates the starting energy value of the alpha.
  int xMovement = random(-movementBounds, movementBounds); // Determines the initial values for the x and y movement.
  int yMovement = random(-movementBounds, movementBounds);
  int totalMovementDistance = random(lowestTotalMovementDistance, highestTotalMovementDistance);

  while (sqrt(pow(xMovement, 2) + pow(yMovement, 2)) < lowestSpeed ) { // Checks the speed of the alpha.
    xMovement = random(-movementBounds, movementBounds); // Generates a random value for x between the bounds.
    yMovement = random(-movementBounds, movementBounds); // Generates a random value for y between the bounds.
  }

  Alpha newAlpha = {xCurrent, yCurrent, energyCurrent, trackPath , 0}; // Creates the new alpha with the new values.
  return newAlpha; // Returns this new alpha.
}

/* Alpha computeNextAlphaLocation(Alpha alpha)

   Determines the next location for which a given alpha will move along with determining if an electron should appear and controlling said electrons.

*/
Alpha computeNextAlphaLocation(Alpha alpha) {
  const int maximumRadius = 2000; // Defines the maxmimum radius value an alpha can reach before it gets obliterated. Default is 2000.
  int energyChangeLowerBounds = 30; // The smallest energy value the alpha can "lose" in one step. This is the minimum energy that can be transfered to an electron. Default is 60 keV.
  int energyChangeUpperBounds = 60; // The largest energy value the alpha can "lose" in one step. This is the maxium energy that can be transfered to an electron. Default is 100 keV.
  int alphaEnergyChangeDivider = 40; // The divider that controls the ratio of energy for which the alpha loses in one step. Default is 4.
  int percentLikelihoodForElectron = 50; // The percent likelihood for an electron to be producted in each movement of the alpha.

  randomSeed(0); // Randomizes the seed.

  int xCurrent = alpha.xLocation + alpha.xMovement; // Saves the passed in xLocation, yLocation, and energy values.
  int yCurrent = alpha.yLocation + alpha.yMovement;
  int energyCurrent = alpha.energy;
  int moveDist = alpha.currentMovementDistance + sqrt(pow(alpha.xMovement, 2) + pow(alpha.yMovement, 2));

  if (sqrt(pow(xCurrent, 2) + pow(yCurrent, 2)) < maximumRadius && energyCurrent > 0 && moveDist < alpha.totalMovementDistance) { // If the alpha can exist.
    int energyChange = random(energyChangeLowerBounds, energyChangeUpperBounds); // Calculates the energy change that the electron will gain if created in keV.
    if (random(0, 101) > (100 - percentLikelihoodForElectron)) { // Results in the stated percent chance to generate an electron with each step.
      alphaElectrons[alphaElectronLocation] = generateElectron(xCurrent, yCurrent, energyChange); // Generates an electron and saves it.
      energyCurrent = energyCurrent - energyChange / alphaEnergyChangeDivider; // Lowers the energy of the alpha.
      alphaElectronLocation++; // Increases the count for which the next electron will be added into the array.
      if (alphaElectronLocation == numElectronLocationsInArray) { // If the array is filled rotate around and start filling it again.
        alphaElectronLocation = 0; // Resets the array position counter to 0.
      }
    }
    else {
      energyCurrent = energyCurrent - energyChange / alphaEnergyChangeDivider;
    }

    for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For every position in the array...
      alphaElectrons[loc] = computeNextElectronLocation(alphaElectrons[loc]); // Computes and moves the electon through its current step.
    }
    //simulateTrack(energyCurrent, xCurrent, yCurrent); // Updates the alphas position.
    Alpha newAlpha = {xCurrent, yCurrent, energyCurrent, alpha.xMovement, alpha.yMovement, moveDist, alpha.movementLocation++}; // Creates the new alpha with the new values.
    return newAlpha; // Returns this new electron.
  }
  else { // If the alpha has left the detector or has no more energy...
    alphaDone = true;
    lastAlphaEvent = millis();
    nextAlphaEvent = random(1000, 2000);
    Alpha newAlpha = createNewAlpha(); // Create a new alpha.

    while(checkElectronDist() == false) {
      displayDetector();
      if (xrayDone == false)
        //xray1 = computeNextXRayLocation(xray1);
      if (cosmicrayDone == false) 
        //cosmicray1 = computeNextCosmicRayLocation(cosmicray1);
      for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For every position in the array...
        alphaElectrons[loc] = computeNextElectronLocation(alphaElectrons[loc]); // Computes and moves the electon through its current step.
      } 
    }
    return newAlpha; // Returns the new alpha so that the infinite loop can be continued.
  }
}

#endif
