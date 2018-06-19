# NEWS-G Galvo System Controller for the Detector Display
Arduino code to control a DAC that controls the galvo system motors to display the detector and represent particles.

## Code Documentation

### Arduino Standard

|**Name and Arguments**     |**Description**                                           |
|-------------|------------------------------------------------------------------------|
|setup()      |Initiates all the pins and functions needed to control the DAC and laser|
|loop()       |Runs repeatedly and controls the main flow of the program               |

### NEWS-G Additional Structs

|**Struct Name** | **Variables within Struct**   |**Description**                                           |
|-------------|------------------------------------------------------------------------|
|Electron     |int rLocation, int thetaLocation, int energy | The electron struct contains all the information that needs to be tracked within an electron. |
|Alpha        |int xLocation, int yLocation, int energy, int xMovement, int yMovement | The alpha struct contains all the information that needs to be tracked within an alpha. |

### NEWS-G Controller Specific 

|**Name and Arguments**   		    |**Description**                                                        								  					|
|-----------------------------------|---------------------------------------------------------------------------------------------------------------------------|
| initiateLaserForDetectorDisplay() | Initiates the laser settings needed to correctly display the laser show. This includes controlling scalling and setting the cartesian coordinate (0, 0) to respresent the center of the circle. |
| displayDetector() | Displays the spherical shell of the detector along with the rod contained within the detector at the maximum size possible. |
| Electron generateElectron(int xLocation, int yLocation, int energyDeposited) | Determines where to generate the electron based on the particles position |
| Alpha createNewAlpha() | Initiates an alpha by determining its starting location, energy, and direction of movement. |
| Electron computeNextElectronLocation(Electron electron) | Based on the last electrons movement this function takes in an electron as its parameter and moves it towards the center of the detector as determined by the electric field. |
| Alpha computeNextAlphaLocation(Alpha alpha) | Based on the last alphas movement this function takes in an alpha particle and determines its next movement step. There is also an ~5% chance that an electron is produced in each step. |
| simulateTrack(int energy, int xMiddlePoint, int yMiddlePoint) | Inputs the location and energy for which the particle has and displays a disk with the radius being proportional to the energy of the particle. The center of the disk will be the location passed into the function. |

| | |
| | |
| electronLineTrack() | Displays an electron track using lines to represent the path that an electron would take within the detector. The pathing is completly randomized although it still follows the pull of an electric field to a certain degree. | 
| electronDiskTrack() | Displays an electron track using the simulateTrack function found below. This function acts similarily to that found above in term of being completely randomized while still following the pull of an electric field but is also able to display the energy of the electron in terms of the radius of the disk. This is the prefered function for electron pathing. |




