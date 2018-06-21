
#ifndef NEWSG_COMMONFUNCTIONS_H
#define NEWSG_COMMONFUNCTIONS_H

#include "Laser.h"


Laser redlaser(5); // Initiates a red laser in the 5th arduino pin.

bool alphaDone = false, xrayDone = false, cosmicrayDone = false;
unsigned long currentMillis, lastAlphaEvent, nextAlphaEvent, lastXRayEvent, nextXRayEvent, lastCosmicRayEvent, nextCosmicRayEvent;
int numElectronLocationsInArray = 10; // The number of electrons that can be tracked. 6 seems to be a reasonable value but can be increased if more then two alphas are wanted.
int alphaElectronLocation = 0, cosmicrayElectronLocation = 0; // The current location for which an electron should be added in.

/* void simulateTrack(int energy, int xMiddlePoint, int yMiddlePoint)

   Simulates an electron track using a disk where the energy is represented as the size of the disk and the middle points of the disk can be specified.

*/
void simulateTrack(int energy, int xMiddlePoint, int yMiddlePoint) {
  redlaser.sendto(SIN(0)*energy / 16384 + xMiddlePoint, COS(0)*energy / 16384 + yMiddlePoint); // Moves the laser to the first location of the disk.
  redlaser.on(); // Turns the laser on.
  for (int loc = 0; loc <= 360; loc += 60) { // Flips through the circle degrees in steps of 60.
    redlaser.sendto(SIN(loc)*energy / 16384 + xMiddlePoint, COS(loc)*energy / 16384 + yMiddlePoint); // Moves the laser around the circle in steps of 60.
  }
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
  {
    redlaser.sendto(SIN(loc) / smallestSINCOSvalue, COS(loc) / smallestSINCOSvalue); // Displays the circle.
  }

  redlaser.off(); // After we have displayed the laser we can turn off the laser.
  redlaser.sendto(0, -2048); // Moves to the bottom portion of the rod.
  redlaser.on();  // Turns on the laser.
  redlaser.sendto(0, 0); // Moves to the center of the circle.
  redlaser.off(); // Turns the laser off.
}

/* initiateLaserForDetectorDisplay()

   Initiates all the laser settings needed for scalled and offsets.

*/
void initiateLaserForDetectorDisplay() {
  redlaser.setScale(1); // Sets the scaling to be normal (no multiplication factor applied to the image) for the red laser.
  redlaser.setOffset(2048, 2048); // Sets the offset for the laser so the circles center corresponds to (0,0) for the red laser.
}

#endif
