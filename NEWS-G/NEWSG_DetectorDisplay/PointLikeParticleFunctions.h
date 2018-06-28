#ifndef POINTLIKEPARTICLEFUNCTIONS_H
#define POINTLIKEPARTICLEFUNCTIONS_H

// Include files.
#include "CommonFunctions.h"

// Variable declaration.
Electron pointlikeparticlesElectrons[11];

// Creates an PointLikeParticle struct. A PointLikeParticle is made up of an x movement path, a y movement path, an energy, and a movement location variable to keep track of what
typedef struct PointLikeParticle {    // step the electron is in.
  int xMovementPath[11];
  int yMovementPath[11];
  int energy;
  int movementLocation;
} PointLikeParticle;

PointLikeParticle pointlikeparticle1; // Initiates a point like particle variable.

// An array containing 7 different movement possibilities for quadrant 1 in the x direction for the alpha particles produced from Po210.
const int xMPPFQ1PointLikeParticle[7][11] PROGMEM = { // Note: This array is stored in flash memory which allows for more dynamic memory to be free!
  {445, 384, 306, 240, 164, 100, 20, -64, -135, -210, -300}, // 0
  {773, 750, 734, 712, 698, 684, 660, 643, 626, 605, 587}, // 1
  {2020, 1940, 1876, 1810, 1747, 1680, 1623, 1570, 1511, 1460, 1400}, // 2
  {1310, 1360, 1415, 1447, 1504, 1560, 1600, 1660, 1720, 1760, 1850}, // 3
  {1610, 1467, 1340, 1182, 1040, 900, 745, 590, 415, 276, 106}, // 4
  {1953, 1871, 1803, 1730, 1667, 1606, 1544, 1487, 1420, 1364, 1307}, // 5
  {1950, 1843, 1720, 1597, 1490, 1384, 1266, 1150, 1036, 920, 810} // 6
};

// An array containing 7 different movement possibilities for quadrant 1 in the y direction for the alpha particles produced from Po210.
const int yMPPFQ1PointLikeParticle[7][11] PROGMEM = { // Note: This array is stored in flash memory which allows for more dynamic memory to be free!
  {1980, 1880, 1796, 1680, 1590, 1500, 1405, 1310, 1230, 1150, 1084}, // 0
  {1894, 1840, 1794, 1758, 1715, 1675, 1640, 1613, 1570, 1542, 1510}, // 1
  {300, 346, 388, 420, 440, 480, 514, 547, 590, 630, 670}, // 2
  {1554, 1384, 1175, 1074, 920, 776, 630, 490, 346, 180, 36}, // 3
  {1263, 1210, 1180, 1116, 1109, 1080, 1055, 1017, 987, 960, 915}, // 4
  {586, 620, 643, 666, 690, 714, 740, 767, 800, 824, 860}, // 5
  {570, 510, 450, 395, 333, 280, 227, 165, 103, 25, -40} // 6
};

// An array containing 7 different energies that corresponds to the different paths displayed above.
const int PointLikeParticleEnergy[7] PROGMEM = {2200, 800, 1000, 1800, 2000, 1600, 1200};

/* bool checkPointLikeParticleElectronDist()

    Returns false if the electrons have a distance greater then the specified distance away from the center of the detector. If all the electrons are within the specified distance
    from the center of the detector return true.

*/
bool checkPointLikeParticleElectronDist() {
  for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For each variable in the electron array.
    if (pointlikeparticlesElectrons[loc].rLocation < 2048) // Check to see if the radial location is smaller then 2048.
      return false; // If one of the radial distances is smaller then 2048 then return false and keep the electrons drifting towards the center of the circle or ions outwards.
  }
  return true; // If all electrons are outside the detector or jabe a radial distance over 2048 then return true and stop the electrons and ions from drifting within the detector.
}

/* PointLikeParticle createNewPointLikeParticle()

    Creates a new point like particle based on the libraries declared above. This new point like particle is returned to allow for its track and electrons/ions to be simulated
    and displayed.

*/
PointLikeParticle createNewPointLikeParticle() {
  const int maxSINCOSvalue = 16384; // The largest value that can be returned from the SIN and COS functions as declared in Basics.cpp. This should remain 16384.

  randomSeed(0); // Randomizes the seed. This in theory adds another layer of random to the code.
  int pathNumber = random(0, 7); // Picks a random number from 0 to 6 for the path.
  int quadrantNumber = random(1, 5); // Picks a random number between 1 and 4 for the quarter of the detector that the particle is displayed in.
  int arrayStartLocation = 0; // Keeps track of the arrays start location (ie. 0).

  // Serial.print("Point Like Particle -> Path #: "); Serial.print(pathNumber); Serial.print("\t Quadrant #: "); Serial.println(quadrantNumber); // Used for debugging.

  PointLikeParticle newPointLikeParticle; // Creates a new cosmic ray.

  if (quadrantNumber ==  1) { // If in quadrant 1.
    for (int loc = 0; loc < numberOfParticleSteps; loc++) { // For each step for the particle.
      newPointLikeParticle.xMovementPath[loc] = pgm_read_word(&(xMPPFQ1PointLikeParticle[pathNumber][loc])); // Fills the x movement array from PROGMEM.
      newPointLikeParticle.yMovementPath[loc] = pgm_read_word(&(yMPPFQ1PointLikeParticle[pathNumber][loc])); // Fills the y movement array from PROGMEM.
    }
    newPointLikeParticle.energy = pgm_read_word(&(PointLikeParticleEnergy[pathNumber])); // Enters the cosmic rays energy.
    newPointLikeParticle.movementLocation = arrayStartLocation; // Sets the arrays start location.
  }
  else if (quadrantNumber ==  2) { // If in quadrant 2.
    for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For each step for the particle.
      newPointLikeParticle.xMovementPath[loc] = -1 * pgm_read_word(&(xMPPFQ1PointLikeParticle[pathNumber][loc])); // Flips and fills the x movement array from PROGMEM.
      newPointLikeParticle.yMovementPath[loc] = pgm_read_word(&(yMPPFQ1PointLikeParticle[pathNumber][loc])); // Fills the y movement array from PROGMEM.
    }
    newPointLikeParticle.energy = pgm_read_word(&(PointLikeParticleEnergy[pathNumber])); // Enters the cosmic rays energy.
    newPointLikeParticle.movementLocation = arrayStartLocation; // Sets the arrays start location.
  }
  else if (quadrantNumber ==  3) { // If in quadrant 3.
    for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For each step for the particle.
      newPointLikeParticle.xMovementPath[loc] = -1 * pgm_read_word(&(xMPPFQ1PointLikeParticle[pathNumber][loc])); // Flips and fills the x movement array from PROGMEM.
      newPointLikeParticle.yMovementPath[loc] = -1 * pgm_read_word(&(yMPPFQ1PointLikeParticle[pathNumber][loc])); // Flips and fills the y movement array from PROGMEM.
    }
    newPointLikeParticle.energy = pgm_read_word(&(PointLikeParticleEnergy[pathNumber])); // Enters the cosmic rays energy.
    newPointLikeParticle.movementLocation = arrayStartLocation; // Sets the arrays start location.
  }
  else if (quadrantNumber ==  4) { // If in quadrant 4.
    for (int loc = 0; loc < numElectronLocationsInArray; loc++) { // For each step for the particle.
      newPointLikeParticle.xMovementPath[loc] = pgm_read_word(&(xMPPFQ1PointLikeParticle[pathNumber][loc])); // Fills the x movement array from PROGMEM.
      newPointLikeParticle.yMovementPath[loc] = -1 * pgm_read_word(&(yMPPFQ1PointLikeParticle[pathNumber][loc])); // Flips and fills the y movement array from PROGMEM.
    }
    newPointLikeParticle.energy = pgm_read_word(&(PointLikeParticleEnergy[pathNumber])); // Enters the cosmic rays energy.
    newPointLikeParticle.movementLocation = arrayStartLocation; // Sets the arrays start location.
  }
  return newPointLikeParticle; // Returns this new cosmic ray.
}

/* PointLikeParticle computeNextPointLikeParticleLocation(PointLikeParticle pointlikeparticle)

    When a previously generated point like particle has been generated and passed into the function this function determined when to generate an electron, how the particle will path,
    and how the electrons and ions will drift within the detector.

*/
PointLikeParticle computeNextPointLikeParticleLocation(PointLikeParticle pointlikeparticle) {
  int energyChangeLowerBounds = 300; // The smallest energy value the alpha can "lose" in one step to an electron or in general. Default is 300 keV.
  int energyChangeUpperBounds = 400; // The largest energy value the alpha can "lose" in one step to an electron or in general. Default is 400 keV.
  
  randomSeed(0); // Randomizes the seed.
  int xCurrent = pointlikeparticle.xMovementPath[pointlikeparticle.movementLocation]; // Saves the passed in xLocation, yLocation, and energy values.
  int yCurrent = pointlikeparticle.yMovementPath[pointlikeparticle.movementLocation];
  int energyCurrent = pointlikeparticle.energy;

  if (pointlikeparticle.movementLocation == numberOfParticleSteps - 1) { // If the particle has reached its last step location.
    int xFinal = pointlikeparticle.xMovementPath[pointlikeparticle.movementLocation - 1]; //Saves the last passed in locations.
    int yFinal = pointlikeparticle.yMovementPath[pointlikeparticle.movementLocation - 1];
    for (int loc = 0; loc < pointlikeparticle.energy / 200; loc++) // Creates a number of electrons based on the energy of the point like particle.
      pointlikeparticlesElectrons[loc] = generateElectron(xFinal, yFinal, pointlikeparticle.energy / 5); // Generates an electron and saves it.
  }

  if (pointlikeparticle.movementLocation < numberOfParticleSteps) { // If the cosmic ray can exist.
     if (delayTime != 0 ) {
      int currentTime = millis(); int enteredTime = millis();
      while (currentTime < enteredTime + delayTime) {
        currentTime = millis();
        simulateTrack(energyCurrent, xCurrent, yCurrent); // Updates the point like particles position.
        displayDetector();
      }
    }
    else
      simulateTrack(energyCurrent, xCurrent, yCurrent); // Updates the point like particles position.
      
    pointlikeparticle.energy = energyCurrent; // Updates the point like particles energy.
    pointlikeparticle.movementLocation = pointlikeparticle.movementLocation + 1; // Updates the point like particles movement location by increasing it by 1.
    return pointlikeparticle; // Returns this new point like particle.
  }
  else { // If the cosmic ray has left the detector or has no more energy...
    if (checkPointLikeParticleElectronDist() == false) { // If the electrons or ions are still within the detector.
      displayDetector(); // Displays the detector.
      for (int loc = 0; loc < numElectronLocationsInArray; loc++) // For every position in the array...
        pointlikeparticlesElectrons[loc] = computeNextElectronLocation(pointlikeparticlesElectrons[loc]); // Computes and moves the electon through its current step.
      return pointlikeparticle; // Returns a nonupdated point like particle resulting in this segment of the code being called again until the electrons or ions have left the detector.
    }
    else { // The electrons or ions have left the detector.
      pointlikeparticleDone = true; // Sets the point like particle boolean to true as the electrons have finished pathing.
      PointLikeParticle newPointLikeParticle = createNewPointLikeParticle(); // Create a new cosmic ray.
      return newPointLikeParticle; // Returns the new alpha so that the infinite loop can be continued.
    }
  }
}

#endif
