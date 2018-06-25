////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//                NEWS-G Detector Display using a DAC and Thorlabs Galvo System                   //
//                                                                                                //
//  Made by: Turner Ward                                                                          //
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

// Include files.
#include "Laser.h"
#include "AlphaFunctions.h"
#include "CommonFunctions.h"
#include "CosmicRayFunctions.h"
#include "ElectronFunctions.h"
#include "XRayFunctions.h"

// Variable declaration.
int Po210AlphaButtonPin = 3;
int Rn222AlphaButtonPin = 4;
int CosmicRayButtonPin = 6;

////////////////////////////////////////////////////////////////////////////////////////////////////


void setup() {
  initiateDisplay();
}

void loop() {
  displayDetector(); // Displays the detector.
  detectorBrain(); // Determines the particles that should be displayed and performs tasks.
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// HELPER FUNCTIONS ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

/* initiateDisplay()

   Initiates all the laser and particle settings needed for scalled, offsets, and displays.

*/
void initiateDisplay() {
  Serial.begin(9600);
  pinMode(Po210AlphaButtonPin, INPUT);
  pinMode(Rn222AlphaButtonPin, INPUT);
  pinMode(CosmicRayButtonPin, INPUT);
  
  redlaser.init(); // Initiates the red laser which also initiates the dac.
  redlaser.setScale(1); // Sets the scaling to be normal (no multiplication factor applied to the image) for the red laser.
  redlaser.setOffset(2048, 2048); // Sets the offset for the laser so the circles center corresponds to (0,0) for the red laser.

  po210alpha1 = createNewPo210Alpha(); // Initiates the particles and creates new versions of each specific particle.
  rn222alpha1 = createNewRn222Alpha();
  xray1 = createNewXRay();
  cosmicray1 = createNewCosmicRay();
}

/* void detectorBrain()
 
   The brain that controls the detectors display.

*/
void detectorBrain () { 
  if (Po210AlphaDone == false) { // If the Po210 alpha has not completed its path...
    po210alpha1 = computeNextPo210AlphaLocation(po210alpha1); // Updates the Po210 alphas location.
  }
  else if (Po210AlphaDone == true and digitalRead(Po210AlphaButtonPin) == HIGH) { // If the Po210 alpha is done and the button has been pushed.
    Po210AlphaDone = false; // Allow for the alpha to be displayed once again.
  }

  if (Rn222AlphaDone == false) { // If the Rn222 alpha has not completed its path...
    rn222alpha1 = computeNextRn222AlphaLocation(rn222alpha1); // Updates the Rn222 alphas location.
  }
  else if (Rn222AlphaDone == true and digitalRead(Rn222AlphaButtonPin) == HIGH) { // If the Rn222 alpha is done and the button has been pushed
    Rn222AlphaDone = false; // Allow for the alpha to be displayed once again.
  }

  if (cosmicrayDone == false) { // If the cosmic ray has not completed its path...
    cosmicray1 = computeNextCosmicRayLocation(cosmicray1); // Updates the cosmic ray next locations.
  }
  else if (cosmicrayDone == true and digitalRead(CosmicRayButtonPin) == HIGH) { // If the cosmic ray is done and the button has been pushed.
    cosmicrayDone = false; // Allow for the cosmic ray to be displayed once again.
  }
}
