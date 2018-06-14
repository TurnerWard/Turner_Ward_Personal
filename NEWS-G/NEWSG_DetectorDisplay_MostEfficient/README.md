# NEWS-G Galvo System Controller for the Detector Display
Arduino code to control a DAC that controls the galvo system motors to display the detector and represent particles.

## Code Documentation

### Arduino Standard


|**Name**     |**Desctiption**                                                         |**Aruguments** |
|-------------|------------------------------------------------------------------------|---------------|
|setup()      |Initiates all the pins and functions needed to control the DAC and laser|None           |
|loop()       |Runs repeatedly and controls the main flow of the program               |None           |

#### NEWS-G Controller Specific 


|**Name and Arguments**   		    |**Description**                                                        								  					|
|-----------------------------------|---------------------------------------------------------------------------------------------------------------------------|
| initiateLaserForDetectorDisplay() | Initiates the laser settings needed to correctly display the laser show. This includes controlling scalling and setting the cartesian coordinate (0, 0) to respresent the center of the circle. |
| displayDetector() | Displays the spherical shell of the detector along with the rod contained within the detector at the maximum size possible. |
| electronLineTrack() | Displays an electron track using lines to represent the path that an electron would take within the detector. The pathing is completly randomized although it still follows the pull of an electric field to a certain degree. | 
| electronDiskTrack() | Displays an electron track using the simulateTrack function found below. This function acts similarily to that found above in term of being completely randomized while still following the pull of an electric field but is also able to display the energy of the electron in terms of the radius of the disk. This is the prefered function for electron pathing. |
| simulateTrack(int energy, int xMiddlePoint, int yMiddlePoint) | Inputs the location and energy for which the particle has and displays a disk with the radius being proportional to the energy of the particle. The center of the disk will be the location passed into the function. |




