# NEWS-G Galvo System Controller for the Detector Display
Arduino code to control a DAC that controls the galvo system motors to display the detector and represent particles.

There are some variables that may be adjusted if the program is not operating as desired. If these variables are global they should be able to be found at the top of the header files they reside in. If the variables are not global they will be found at the top of the function they reside in.

Due to the large size of the code needed to control the galvo system in the desired method it should be noted that the arduinos dynamic memory and program storage space are getting quite full. If very large changes are planned to be made external ram, more program space, or a change of controller should be considered.


## Code Documentation

### Arduino Standard

|**Name and Arguments** | **Description**                                          		  		     |
|-----------------------|----------------------------------------------------------------------------|
|setup()      			| Initiates all the pins and functions needed to control the DAC and laser.  |
|loop()       			| Runs repeatedly and controls the main flow of the program.                 |

### The following NEWS-G specific functions have been broken down based on the file that they are in. This makes the purpose of each file very clear and easy to follow.

### NEWSG_DetectorDisplay.ino

#### Important Variables:
	-> int Po210AlphaButtonPin = 3
	-> int Rn222AlphaButtonPin = 4
	-> int CosmicRayButtonPin = 6
	-> int PointLikeParticleButtonPin = 8

#### Functions:	
|**Name and Arguments** | **Description**                                          				     |
|-----------------------|----------------------------------------------------------------------------|
|void detectorBrain()   | The brain that controls the detectors display. This function determines which functions are currently running, keeps track of what functions need to be called based on the stage of the particle, and determine when the user wants a specific track to be displayed.  |
|void initiateDisplay() | Initiates the laser, particle, and settings needed to display the detector and particles.  |

### AlphaFunctions.h
#### Structs:
	-> Alpha{int xMovementPath[11], int yMovementPath[11], energy, movementLocation}

#### Important Variables:
##### The following four variables are the alpha particles movement libraries used for movement.
	-> const int xMPPFQ1Po210[6][11] PROGMEM = ...
	-> const int yMPPFQ1Po210[6][11] PROGMEM = ...
	-> const int xMPPFQ1Rn222[6][11] PROGMEM = ...
	-> const int yMPPFQ1Rn222[6][11] PROGMEM = ...
	
#### Functions:	
|**Name and Arguments** | **Description**                                          				    |
|-----------------------|----------------------------------------------------------------------------|
|bool checkPo210AlphaElectronDist()    | Returns false if the Po 210 electrons are still within the detector. This distance continues to be monitored while the electrons are converted to ions and drift back towards the edges of the detector. When all the ions have left the detector the function returns true letting the program know it can stop determining the electrons next position.  |
|bool checkRn222AlphaElectronDist()    | Does the same thing as above but for the Rn 222 electrons.  |
|Alpha createNewPo210Alpha()  		   | Creates a new Po 210 Alpha based on the movement libraries above along with the known energies for these alphas. |
|Alpha createNewRn222Alpha()		   | Does the same thing as above but for the Rn 222 Alpha.  |
|Alpha computeNextPo210AlphaLocation(Alpha Po210Alpha) 	  | Moves the alpha to the next location in its movement array while creating electrons, reducing its energy, and drifting the already generated electrons and eventually ions. This function is in charge of facilitiating the Po 210 electrons and ions drift until the ions leave the detector.   |
|Alpha computeNextRn222AlphaLocation(Alpha Rn222Alpha) 	  | Does the same thing as above but for the Rn 222 Alpha and Rn 222 electrons and ions. |

### CommonFunctions.h

#### Functions:	
|**Name and Arguments** | **Description**                                          				    |
|-----------------------|----------------------------------------------------------------------------|
|void simulateTrack(int energy, int xMiddlePoint, int yMiddlePoint)   | Simulates a track which position is passed into the function and size is based on the energy of the particle.  |
|void displayDetector() | Using the predetermined SIN and COS arrays to display a circle along with a rod, this function displays the detector. |

### CosmicRayFunctions.h

#### Structs:
	-> CosmicRay{int xMovementPath[11], int yMovementPath[11], energy, movementLocation}

#### Important Variables:
##### The following two variables are the cosmic rays particles movement libraries used for movement.
	-> const int xMPPFQ1Muon[6][11] PROGMEM = ...
	-> const int yMPPFQ1Muon[6][11] PROGMEM = ...

#### Functions:	
|**Name and Arguments** | **Description**                                          				    |
|-----------------------|----------------------------------------------------------------------------|
|bool checkCosmicElectronDist() | Returns false if the cosmic rays electrons are still within the detector. This distance continues to be monitored while the electrons are converted to ions and drift back towards the edges of the detector. When all the ions have left the detector the function returns true letting the program know it can stop determining the electrons next position.  |
|CosmicRay createNewCosmicRay() | Creates a new cosmic ray based on the movement libraries above along with the known energies for these cosmic rays. |
|CosmicRay computeNextCosmicRayLocation(CosmicRay cosmicray) | Moves the cosmic ray to the next location in its movement array while creating electrons, reducing its energy, and drifting the already generated electrons and eventually ions. This function is in charge of facilitating the cosmic ray electrons and ion drift until the ions leave the detector.	|

### ElectronFunctions.h

#### Structs:
	-> Electron{int rLocation, int thetaLocation, int energy, bool ion}

#### Functions:	
|**Name and Arguments** | **Description**                                          				    |
|-----------------------|----------------------------------------------------------------------------|
|Electron generateElectron(int xLocation, int yLocation, int energyDeposited) | Generated an electron with the depostied energy value at the provided (x,y) pair. Since the electron struct stores with information in polar coordinates this function converts all the information to polar.  |
|Electron computeNextElectronLocation(Electron electron) | Randomly determines the electrons drift path while increasing its speed when close to the center of the detector for the electrons. When the electron reaches the center of the detector this function begins to treat it as a ion and randomly determines a direction to drift it outwards from. This drift is not random as the electron drift was.  |

### PointLikeParticleFunctions.h

#### Structs:
	-> PointLikeParticle{int xMovementPath[11], int yMovementPath[11], energy, movementLocation}

#### Important Variables:
##### The following three variables are the point like particles movement and energy libraries used for movement.
	-> const int xMPPFQ1PointLikeParticle[7][11] PROGMEM = ...
	-> const int yMPPFQ1PointLikeParticle[7][11] PROGMEM = ...
	-> const int PointLikeParticleEnergy[7] PROGMEM = ...

#### Functions:	
|**Name and Arguments** | **Description**                                          				    |
|-----------------------|----------------------------------------------------------------------------|
|bool checkPointLikeParticleElectronDist() | Returns false if the point like particles electrons are still within the detector. This distance continues to be monitored while the electrons are converted to ions and drift back towards the edges of the detector. When all the ions have left the detector the function returns true letting the program know it can stop determining the electrons next position.  |
|PointLikeParticle createNewPointLikeParticle() | Creates a new point like particle based on the movement and energy libraries. |
|PointLikeParticle computeNextPointLikeParticleLocation(PointLikeParticle pointlikeparticle) | Moves the point like particle to the next location in its movement array while creating electrons, reducing its energy, and drifting the already generated electrons and eventually ions. This function is in charge of facilitating the point like particles electron and ion drift until the ions leave the detector.	|

### Particle Track Cheat Sheet
#### The following image contains the track number particle display for each particle in the first quadrant. If looking to make changes to one of these tracks please refer to this picture.
![alt text](https://github.com/TurnerWard/Turner_Ward_Personal/blob/master/NEWS-G/NEWSG_DetectorDisplay/NumberedParticleTrack.PNG)

### Demo Video
#### Here is a video moving through the 4 different particle events with two different events for each display.
![Demo Video Link](https://github.com/TurnerWard/Turner_Ward_Personal/blob/master/NEWS-G/NEWSG_DetectorDisplay/NEWSG_DemoVideo_Final.MOV)

### NEXT STEPS
#### -> Display the current that is being produced by the ions as they drift.
#### -> Add in multiple laser colours (the difficult part here would be determining how to have the lasers at the same angle. Need a semi-transparent mirror.)
#### -> Creating a more finalized control panel by getting or creating a button console location.
#### -> Moving all/most components into a box and securing the components.

