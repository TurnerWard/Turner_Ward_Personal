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

int Rn222AlphaButtonPin = 4;
int Po210AlphaButtonPin = 3;
int CosmicRayButtonPin = 6;

void setup() {
  Serial.begin(9600);
  pinMode(Po210AlphaButtonPin, INPUT);
  pinMode(Rn222AlphaButtonPin, INPUT);
  pinMode(CosmicRayButtonPin, INPUT);
  redlaser.init(); // Initiates the red laser which also initiates the dac.
  initiateLaserForDetectorDisplay(); // Initates the laser settings for the detector.

  po210alpha1 = createNewPo210Alpha(); // Initiates the particles.
  rn222alpha1 = createNewRn222Alpha();
  xray1 = createNewXRay();
  cosmicray1 = createNewCosmicRay();
}

void loop() {
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
  if (Po210AlphaDone == false) { // If the alpha has not completed its path...
    po210alpha1 = computeNextPo210AlphaLocation(po210alpha1); // Updates the alphas location.
  }
  else if (Po210AlphaDone == true and digitalRead(Po210AlphaButtonPin) == HIGH) { // If the alpha is done and a reasonable amount of time has passed.
    Po210AlphaDone = false; // Allow for the alpha to be displayed once again.
  }

  if (Rn222AlphaDone == false) { // If the alpha has not completed its path...
    rn222alpha1 = computeNextRn222AlphaLocation(rn222alpha1); // Updates the alphas location.
  }
  else if (Rn222AlphaDone == true and digitalRead(Rn222AlphaButtonPin) == HIGH) { // If the alpha is done and a reasonable amount of time has passed.
    Rn222AlphaDone = false; // Allow for the alpha to be displayed once again.
  }

  if (cosmicrayDone == false) { // If the cosmic ray has not completed its path...
    cosmicray1 = computeNextCosmicRayLocation(cosmicray1); // Updates the cosmic ray next locations.
  }
  else if (cosmicrayDone == true and digitalRead(CosmicRayButtonPin) == HIGH) { // If the cosmic ray is done and a reasonable amount of time has passed.
    cosmicrayDone = false; // Allow for the cosmic ray to be displayed once again.
  }

//  if (xrayDone == false) { // If the xray has not completed its path...
//    xray1 = computeNextXRayLocation(xray1); // Updates the xrays next locations.
//  }
//  else if (xrayDone == true and (currentMillis > lastXRayEvent + nextXRayEvent)) { // If the xray is done and a reasonable amount of time has passed.
//    xrayDone = false; // Allow for the xray to be displayed once again.
//  }
//
}
