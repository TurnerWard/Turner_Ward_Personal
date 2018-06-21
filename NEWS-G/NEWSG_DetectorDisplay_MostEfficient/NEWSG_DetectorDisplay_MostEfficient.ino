////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//                NEWS-G Detector Display using a DAC and Thorlabs Galvo System                   //
//                                                                                                //
//  Made by: Turner Ward                                                                          //
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Laser.h"
#include "NEWSG_AlphaFunctions.h"
#include "NEWSG_CommonFunctions.h"
#include "NEWSG_CosmicRayFunctions.h"
#include "NEWSG_ElectronFunctions.h"
#include "NEWSG_XRayFunctions.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  redlaser.init(); // Initiates the red laser which also initiates the dac.
  initiateLaserForDetectorDisplay(); // Initates the laser settings for the detector.

  alpha1 = createNewAlpha(); // Initiates the particles.
  xray1 = createNewXRay();
  cosmicray1 = createNewCosmicRay();
}

void loop() {
  currentMillis = millis();
  displayDetector(); // Displays the detector.
  detectorBrain(); // Determines the particles that should be displayed and performs tasks.
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// HELPER FUNCTIONS ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////


/* void detectorBrain()
 
   The brain that controls the detectors display.

*/
void detectorBrain () { 
  if (alphaDone == false) { // If the alpha has not completed its path...
    alpha1 = computeNextAlphaLocation(alpha1); // Updates the alphas location.
  }
  else if (alphaDone == true and (currentMillis > lastAlphaEvent + nextAlphaEvent)) { // If the alpha is done and a reasonable amount of time has passed.
    alphaDone = false; // Allow for the alpha to be displayed once again.
  }

//  if (xrayDone == false) { // If the xray has not completed its path...
//    xray1 = computeNextXRayLocation(xray1); // Updates the xrays next locations.
//  }
//  else if (xrayDone == true and (currentMillis > lastXRayEvent + nextXRayEvent)) { // If the xray is done and a reasonable amount of time has passed.
//    xrayDone = false; // Allow for the xray to be displayed once again.
//  }
//
//  if (cosmicrayDone == false) { // If the cosmic ray has not completed its path...
//    cosmicray1 = computeNextCosmicRayLocation(cosmicray1); // Updates the cosmic ray next locations.
//  }
//  else if (cosmicrayDone == true and (currentMillis > lastXRayEvent + nextXRayEvent)) { // If the cosmic ray is done and a reasonable amount of time has passed.
//    cosmicrayDone = false; // Allow for the cosmic ray to be displayed once again.
//  }
}
