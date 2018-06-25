# NEWS-G Galvo System Controller for the Detector Display
Arduino code to control a DAC that controls the galvo system motors to display the detector and represent particles.

## Code Documentation

### Arduino Standard

|**Name and Arguments**     |**Description**                                           |
|-------------|------------------------------------------------------------------------|
|setup()      |Initiates all the pins and functions needed to control the DAC and laser.|
|loop()       |Runs repeatedly and controls the main flow of the program.               |

### NEWS-G Additional Structs

|**Struct Name** | **Variables within Struct**   |**Description**                      |
|-------------|------------------------------------------------------------------------|---|
|Electron     |int rLocation, int thetaLocation, int energy | The electron struct contains all the information that needs to be tracked within an electron. |
|Alpha        |int xMovementPath[11] int yMovementPath[11], int energy, int movementLocation | The alpha struct contains all the information that needs to be tracked within an alpha. |
|Cosmic Ray   |int xMovementPath[11] int yMovementPath[11], int energy, int movementLocation | The cosmic ray struct contains all the information that needs to be tracked within a cosmic ray. |

### NEWS-G Controller Specific 

|**Name and Arguments**   		    |**Description**                                                        								  					|
|-----------------------------------|---------------------------------------------------------------------------------------------------------------------------|



