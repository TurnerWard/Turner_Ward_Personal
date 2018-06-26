# NEWS-G Galvo System Controller for the Detector Display
Arduino code to control a DAC that controls the galvo system motors to display the detector and represent particles.

## Code Documentation

### Arduino Standard

|**Name** 				|**Arguments** | **Description**                                          				    |
|-----------------------|-------------------------------------------------------------------------------------------|
|setup()      			| 			   | Initiates all the pins and functions needed to control the DAC and laser.  |
|loop()       			| 			   | Runs repeatedly and controls the main flow of the program.                 |

## The following NEWS-G specific functions have been broken down based on the file that they are in. This makes the purpose of each file very clear and easy to follow.

### NEWSG_DetectorDisplay.ino

#### Variables:
	-> Po210AlphaButtonPin = 3
	-> Rn222AlphaButtonPin = 4
	-> CosmicRayButtonPin = 6
	-> PointLikeParticleButtonPin = 8

|**Name** 				|**Arguments** | **Description**                                          				    |
|-----------------------|-------------------------------------------------------------------------------------------|
|void detectorBrain()   | 			   | The brain that controls the detectors display. This function determines which functions are currently running, keeps track of what functions need to be called based on the stage of the particle, and determine when the user wants a specific track to be displayed.  |
|void displayDetector() | 			   | Using the predetermined SIN and COS arrays to display a circle along with a rod, this function displays the detector. |

