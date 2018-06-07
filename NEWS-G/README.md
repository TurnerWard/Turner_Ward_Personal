# NEWS-G Galvo System Controller
Arduino code to control a DAC that controls the galvo system motors.

## Code Documentation

### Arduino Standard


|**Name**     |**Desctiption**                                                         |**Aruguments** |
|-------------|------------------------------------------------------------------------|---------------|
|setup()      |Initiates all the pins and functions needed to control the DAC and laser|None           |
|loop()       |Runs repeatedly and controls the main flow of the program               |None           |

#### NEWS-G Controller Specific 


|**Name**                   |**Description**                                                                         |
|-------------------------|---------------------------------------------------------------------------------------|
|drawLine(int xStart, int yStart, int xEnd, int yEnd)             | Draws a line from point 1 to point 2 when provided with a start and end location. |
|letterJumbleToWord(String startWord, String endWord, int xOffset, int yOffset)                 | Starts with a provided string and cycles through the letters in the fastest direction to convert all to the final string. The final string is held for a breif period of time before being compressed into nothing. |
|increasingFontSize(String str, int xOffset, int yOffset)                     | Creates a string and displays it with a tiny font size. The font size is slowly increased until it reaches its max size. |
|rotateStringX(String str, int xOffset, int yOffset)       | Displays a string and rotates it about the x axis approximatly 3 times. The words on the outer edges of the string tend to not rotate properly. |
|rotateStringY(String str, int xOffset, int yOffset)     | Displays a string and rotates it about the y axis approximatly 3 times. As the word appears perpendicular to the viewer a strange cross section appears but this cannot seen to be fixed. |
|countDown()              | Creates a circle with the number 9 within it. Every second the number changes to the number below until 1 is reaches in which case the count down ends. |
|circle()         | Creates a circle. Is used primarily for the countDown() function; however, it can be changed to have input parameters to be its own stand alone functions. |
|VandeGraaffSimulation(int count, int xOffset, int yOffset)    | Simulates a Van de Graaff generater using a circle and demonstrating lightening around the outer circle to middle. |