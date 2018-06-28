////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//                NEWS-G Detector Display using a DAC and Thorlabs Galvo System                   //
//                                                                                                //
//  Made by: Turner Ward                                                                          //
//                                                                                                //
//                                                                                                //
//  Note: Not every header file within this folder was written by Turner.                         //
//        With that in mind the following functions were: -> NEWSG_DectorDisplays.ino             //
//                                                        -> AlphaFunctions.h                     //
//                                                        -> CommonFunctions.h                    //
//                                                        -> CosmicRayFunctions.h                 //
//                                                        -> ElectronFunctions.h                  //
//                                                        -> PointLikeParticleFunctions.h         //
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

// Include files. All the files needed to operate the galvo system within the main function.
#include "Laser.h"
#include "AlphaFunctions.h"
#include "CommonFunctions.h"
#include "CosmicRayFunctions.h"
#include "ElectronFunctions.h"
#include "PointLikeParticleFunctions.h"

// Variable declaration. These are the pins that the buttons should be connected to for initiating the different particles.
int Po210AlphaButtonPin = 3;
int Rn222AlphaButtonPin = 4;
int CosmicRayButtonPin = 6;
int PointLikeParticleButtonPin = 8;

// Setup.
void setup() {
  initiateDisplay(); // Initiates the laser, buttons, and display.
}

// Loop.
void loop() {
  displayDetector(displayEnergyLevel); // Displays the detector.
  detectorBrain(); // Determines the particles that should be displayed and performs tasks.
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// HELPER FUNCTIONS ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

/* void detectorBrain()

   The brain that controls the detectors display.

*/
void detectorBrain () {
  if (Po210AlphaDone == false) { // If the Po 210 alpha has not yet completed its path...
    po210alpha1 = computeNextPo210AlphaLocation(po210alpha1); // Updates the Po 210 alphas location.
  }
  else if (Po210AlphaDone == true and digitalRead(Po210AlphaButtonPin) == HIGH) { // If the Po 210 alpha is done and the button has been pushed.
    Po210AlphaDone = false; // Allow for the Po 210 alpha to be displayed once again.
  }

  if (Rn222AlphaDone == false) { // If the Rn222 alpha has not yet completed its path...
    rn222alpha1 = computeNextRn222AlphaLocation(rn222alpha1); // Updates the Rn 222 alphas location.
  }
  else if (Rn222AlphaDone == true and digitalRead(Rn222AlphaButtonPin) == HIGH) { // If the Rn 222 alpha is done and the button has been pushed
    Rn222AlphaDone = false; // Allow for the Rn 222 alpha to be displayed once again.
  }

  if (cosmicrayDone == false) { // If the cosmic ray has not yet completed its path...
    cosmicray1 = computeNextCosmicRayLocation(cosmicray1); // Updates the cosmic ray next location.
  }
  else if (cosmicrayDone == true and digitalRead(CosmicRayButtonPin) == HIGH) { // If the cosmic ray is done and the button has been pushed.
    cosmicrayDone = false; // Allow for the cosmic ray to be displayed once again.
  }

  if (pointlikeparticleDone == false) { // If the point like particle has not yet completed its path...
    pointlikeparticle1 = computeNextPointLikeParticleLocation(pointlikeparticle1); // Updates the point like particles location.
  }
  else if (pointlikeparticleDone == true and digitalRead(PointLikeParticleButtonPin) == HIGH) { // If the point like particle is done and the button has been pushed.
    pointlikeparticleDone = false; // Allow for the point like particle to be displayed once again.
  }
}

/* initiateDisplay()

   Initiates all the laser and particle settings needed for scalled, offsets, and displays.

*/
void initiateDisplay() {
  Serial.begin(9600); // Allows for serial communications to occur.
  
  pinMode(Po210AlphaButtonPin, INPUT); // Initiates the digital write button inputs.
  pinMode(Rn222AlphaButtonPin, INPUT);
  pinMode(CosmicRayButtonPin, INPUT);
  pinMode(PointLikeParticleButtonPin, INPUT);

  redlaser.init(); // Initiates the red laser which also initiates the dac.
  
  if(displayEnergyLevel == true) {
  redlaser.setScale(0.80); // Sets the scaling to be normal (no multiplication factor applied to the image) for the red laser.
  redlaser.setOffset(2048-400, 2048+400); // Sets the offset for the laser so the circles center corresponds to (0,0) for the red laser.
  }
  else {
    redlaser.setScale(1); // Sets the scaling to be normal (no multiplication factor applied to the image) for the red laser.
    redlaser.setOffset(2048, 2048); // Sets the offset for the laser so the circles center corresponds to (0,0) for the red laser.
  }

  po210alpha1 = createNewPo210Alpha(); // Initiates the particles and creates new versions of each specific particle.
  rn222alpha1 = createNewRn222Alpha();
  cosmicray1 = createNewCosmicRay();
  pointlikeparticle1 = createNewPointLikeParticle();
}
