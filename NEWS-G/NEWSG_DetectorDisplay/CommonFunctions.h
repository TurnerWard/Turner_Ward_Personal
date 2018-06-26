#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

// Include files.
#include "Laser.h"

// Variable declaration.
Laser redlaser(5); // Initiates a red laser in the 5th arduino pin.
bool Po210AlphaDone = true, Rn222AlphaDone = true, cosmicrayDone = true, pointlikeparticleDone = true;
int numElectronLocationsInArray = 11; // The number of electrons that can be tracked.
int Po210AlphaElectronLocation = 0, Rn222AlphaElectronLocation = 0, cosmicrayElectronLocation = 0; // The current location for which an electron should be added in.
int numberOfParticleSteps = 11; // The number of electron steps that are contained within the particle.

/* void simulateTrack(int energy, int xMiddlePoint, int yMiddlePoint)

   Simulates an electron track using a disk where the energy is represented as the size of the disk and the middle points of the disk can be specified.

*/
void simulateTrack(int energy, int xMiddlePoint, int yMiddlePoint) {
  int energyScalingFactor = 10; // An energy scaling factor that allows for accurate energy values to be used but not be too large within the detector.
  energy = energy / energyScalingFactor; // Updates the energy value with the scaling factor above.
  redlaser.off(); // Turns off the red laser.
  redlaser.sendto(SIN(0)*energy / 16384 + xMiddlePoint, COS(0)*energy / 16384 + yMiddlePoint); // Moves the laser to the first location of the disk.
  redlaser.on(); // Turns the red laser on.
  for (int loc = 0; loc <= 360; loc += 60) // Flips through the circle degrees in steps of 60.
    redlaser.sendto(SIN(loc) * energy / 16384 + xMiddlePoint, COS(loc) * energy / 16384 + yMiddlePoint); // Moves the laser around the circle in steps of 60.
  redlaser.off(); // At the end turns off the laser.
}

/* void displayDetector()

   Displays the detector using a circle and a rod with the maximum resolution.

*/
void displayDetector() {
  int circleStepSize = 20; // Changes the step size as the for loop passes through the circle. Smaller values create more perfect circles. Default is 15.

  redlaser.off(); // Makes sure the laser is off. This was needed to avoid fencing at this point.
  const int smallestSINCOSvalue = 8; // The value needed to convert from the larger scale of max value being 16384 to the smaller more appropriate scale of 2048.
  redlaser.sendto(SIN(0) / smallestSINCOSvalue, COS(0) / smallestSINCOSvalue); // Moves the laser to the correct starting location.
  redlaser.on(); // Now since we are in the correct location we can turn the laser on.
  for (int loc = 0; loc <= 360; loc += circleStepSize) // Rotates through the angles of the circle with the provided step size.
    redlaser.sendto(SIN(loc) / smallestSINCOSvalue, COS(loc) / smallestSINCOSvalue); // Displays the circle.
  redlaser.off(); // After we have displayed the laser we can turn off the laser.
  redlaser.sendto(0, -2048); // Moves to the bottom portion of the rod.
  redlaser.on();  // Turns on the laser.
  redlaser.sendto(0, 0); // Moves to the center of the circle.
  redlaser.off(); // Turns the laser off.
}

#endif
