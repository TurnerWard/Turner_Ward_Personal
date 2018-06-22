#include "Laser.h" // All the includes needed for the laser show.
#include "Drawing.h"
#include "Cube.h"
#include "Objects.h"

Laser laser(5); // Creates a laser instance with the laser pointer connected to pin 5.
unsigned long currentMillis; // Can run for ~50 days.
unsigned long nextEvent; // Can run for ~50 days.

void setup() {
  Serial.begin(9600);
  laser.init(); // Initiates the laser which also initiates the dac.
  initiateLaserForDetectorDisplay(); // Initates the laser settings for the detector.
}

//////////////////////////////////////////////
////////// Max value is 2^12 = 4096 //////////
/////////// Middle is (2048, 2048) ///////////
//////////////////////////////////////////////
//////////////// FUNCTION LIST ///////////////
//////////////////////////////////////////////
// -> void drawLine(int xStart, int yStart, int xEnd, int yEnd); // Draws a line from point one to point two.
// -> void letterJumbleToWord(String startWord, String endWord, int xOffset, int yOffset); // Starts from a given word and quickly scrambels them until it arrives at the second word.
// -> void increasingFontSize(String str, int xOffset, int yOffset); // Increases the font size from 0 to the standard font size. This needs to occur around (2048,2048) for full effect.
// -> void rotateStringX(String str, int xOffset, int yOffset); // Rotates the string about the x-axis.
// -> void rotateStringY(String str, int xOffset, int yOffset); // Rotates the string about the y-axis.
// -> void countDown(); // Creates a circle that counts dont from 9 to 1.
// -> void circle(); // Creates a circle.
// -> void VandeGraaffSimulation(int count, int xOffset, int yOffset); // Simualtes a Van de Graaff simulation.
// -> void drawWord(String str, int xOffset, int yOffset); // Displays a word at the given location.
// -> void drawStar(int sizeMultiplier, int xMiddlePoint, int yMiddlePoint); // Creates a star at the provided location. Multiplier of 40 is approximalty the max at the center.

void loop() {

  //VandeGraaffSimulation(100, 2048, 2048);

  displayDetector();
  
  currentMillis = millis();
  if(nextEvent < currentMillis) {
    //electronLineTrack();   
    electronDiskTrack();
    nextEvent = millis() + random(500, 3000);
  }
}

// letterJumbleToWord("ZGK0/!","NEWS-G", 2048, 2048);

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// HELPER FUNCTIONS ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void electronLineTrack() {
  laser.off(); // Makes sure the laser is off.
  randomSeed(0); // Randomizes the seed.
  
  int rStart = random(1028, 2048); // Randomly returns the radius value for the electron to start at between 1028 and 2048.
  int thetaStart = random(0, 360); // Randomly returns the theta value for the electron to start at.

  laser.sendto(rStart*COS(thetaStart)/16384, rStart*SIN(thetaStart)/16384); // Converts from polar to cartesian and moves the laser to the start position.
  laser.on(); // Turns the laser on.

  int rCurrent = rStart;
  int thetaCurrent = thetaStart;
  while(rCurrent > 100) { // While outside the inner radius where the electric field is weaker.                
    int rMovement = random(100,500); // Generates a random value between 100 and 500 for the r distance that the electron will move in this step. 
    int thetaMovement = random(-35,35); // Generates a random value between -35 and 35 for the theta direction that the electron will move in this step.
    rCurrent = rCurrent - rMovement; // Updates the current r value.
    thetaCurrent = thetaCurrent + thetaMovement; // Updates the current theta value.
    laser.sendto(rCurrent*COS(thetaCurrent)/16384, rCurrent*SIN(thetaCurrent)/16384); // Converts from polar to cartesian and moves the laser to the newly updates position.
  }

  laser.sendto(0, 0); // If the electron is within 100 pixels of the center of the detector the electric field value is so strong it will be pulled directily towards the center.
  laser.off(); // Turns off the laser as the pathing is now complete.
}

void electronDiskTrack() {
  laser.off(); // Makes sure the laser is off.
  randomSeed(0); // Randomizes the seed.
  
  int rStart = random(1028, 2048); // Randomly returns the radius value for the electron to start at between 1028 and 2048.
  int thetaStart = random(0, 360); // Randomly returns the theta value for the electron to start at.

  simulateTrack(100, rStart*COS(thetaStart)/16384, rStart*SIN(thetaStart)/16384); // Converts from polar to cartesian and creates the electron at the start position.
  laser.on(); // Turns the laser on.

  int rCurrent = rStart;
  int thetaCurrent = thetaStart;
  while(rCurrent > 100) { // While outside the inner radius where the electric field is weaker.                         
    displayDetector();
    int rMovement = random(10,50); // Generates a random value between 100 and 500 for the r distance that the electron will move in this step. 
    int thetaMovement = random(-5,5); // Generates a random value between -35 and 35 for the theta direction that the electron will move in this step.
    rCurrent = rCurrent - rMovement; // Updates the current r value.
    thetaCurrent = thetaCurrent + thetaMovement; // Updates the current theta value.
    simulateTrack(100, rCurrent*COS(thetaCurrent)/16384, rCurrent*SIN(thetaCurrent)/16384); // Converts from polar to cartesian and creates the electron at the start position.
  }

  while (rCurrent <= 100 && 0 < rCurrent) {
    displayDetector();
    rCurrent = rCurrent - 20;
    simulateTrack(100, rCurrent*COS(thetaCurrent)/16384, rCurrent*SIN(thetaCurrent)/16384); // If the electron is within 100 pixels of the center of the detector the electric field value is so strong it will be pulled directily towards the center.
  }
  laser.off(); // Turns off the laser as the pathing is now complete.
}

void alphaTrack(int energy, int xStartLocation, int yStartLocation, int xEndLocation, int yEndLocation) {
  
}

void displayDetector() {
  laser.off();
  const int scale = 8; // The value needed to convert from the larger scale of max value being 16384 to the smaller more appropriate scale of 2048.
  laser.sendto(SIN(0)/scale, COS(0)/scale); // Moves the laser to the correct starting location.
  laser.on(); // Now since we are in the correct location we can turn the laser on.
  
  for (int r = 0;r<=360;r+=12) // Rotates through the angles of the circle with the provided step size.
  {    
    laser.sendto(SIN(r)/scale, COS(r)/scale); // Displays the circle.
  }
  laser.off(); // After we have displayed the laser we can turn off the laser.

  laser.sendto(0, -2048); laser.on(); laser.sendto(0,0); laser.off(); // Displays the rod.
}

void simulateTrack(int energy, int xMiddlePoint, int yMiddlePoint) {
  laser.sendto(SIN(0)*energy/16384 + xMiddlePoint, COS(0)*energy/16384 + yMiddlePoint);
  laser.on();
  for (int r = 0;r<=360;r+=30) { 
    laser.sendto(SIN(r)*energy/16384 + xMiddlePoint, COS(r)*energy/16384 + yMiddlePoint);
  }
  laser.off();
}

void initiateLaserForDetectorDisplay() {
  laser.setScale(1); // Sets the scaling to be normal (no multiplication factor applied to the image).
  laser.setOffset(2048,2048); // Sets the offset for the laser so the circles center corresponds to (0,0).
}

void NEWSGDEMO() {
  delay(3000);
  currentMillis = millis();
  while(currentMillis < 5000) {
    drawWord("NEWS-G", 1500, 1500);
    currentMillis = millis();
  }
  rotateStringX("NEWS-G", 1500, 1500);
  int endedTime = millis();
  currentMillis = millis();
  while(currentMillis < 5000 + endedTime) {
    drawWord("NEWS-G", 1500, 1500);
    currentMillis = millis();
  }
  rotateStringY("NEWS-G", 1500, 1500);
  delay(3000);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////// FUNTIONS DESIGNED FOR TEXT PROJECTION ////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void drawStar(int sizeMultiplier, int xMiddlePoint, int yMiddlePoint) {
  drawLine(xMiddlePoint, yMiddlePoint+50*sizeMultiplier, xMiddlePoint+10*sizeMultiplier, yMiddlePoint+20*sizeMultiplier);
  drawLine(xMiddlePoint+10*sizeMultiplier, yMiddlePoint+20*sizeMultiplier, xMiddlePoint+40*sizeMultiplier, yMiddlePoint+20*sizeMultiplier);
  drawLine(xMiddlePoint+40*sizeMultiplier, yMiddlePoint+20*sizeMultiplier, xMiddlePoint+20*sizeMultiplier, yMiddlePoint);
  drawLine(xMiddlePoint+20*sizeMultiplier, yMiddlePoint, xMiddlePoint+30*sizeMultiplier, yMiddlePoint-30*sizeMultiplier);
  drawLine(xMiddlePoint+30*sizeMultiplier, yMiddlePoint-30*sizeMultiplier, xMiddlePoint, yMiddlePoint-10*sizeMultiplier);    
  drawLine(xMiddlePoint, yMiddlePoint-10*sizeMultiplier, xMiddlePoint-30*sizeMultiplier, yMiddlePoint-30*sizeMultiplier);
  drawLine(xMiddlePoint-30*sizeMultiplier, yMiddlePoint-30*sizeMultiplier, xMiddlePoint-20*sizeMultiplier, yMiddlePoint);
  drawLine(xMiddlePoint-20*sizeMultiplier, yMiddlePoint, xMiddlePoint-40*sizeMultiplier, yMiddlePoint+20*sizeMultiplier);
  drawLine(xMiddlePoint-40*sizeMultiplier, yMiddlePoint+20*sizeMultiplier, xMiddlePoint-10*sizeMultiplier, yMiddlePoint+20*sizeMultiplier);
  drawLine(xMiddlePoint-10*sizeMultiplier, yMiddlePoint+20*sizeMultiplier, xMiddlePoint, yMiddlePoint+50*sizeMultiplier);
}

void drawWord(String str, int xOffset, int yOffset) {
  int w = Drawing::stringAdvance(str);
  laser.setScale(0.5);
  laser.setOffset(xOffset, yOffset);
  laser.setEnable3D(true);
  Drawing::drawString(str,-w/2, -500,1);
  laser.setEnable3D(false);
}

void drawLine(int xStart, int yStart, int xEnd, int yEnd) {
  laser.on();
  laser.setEnable3D(true);
  laser.setScale(1);
  laser.setOffset(-2048, -2048); 
  laser.drawline(xStart, yStart, xEnd, yEnd); // Draws a line from a given start to end location.
  laser.off();
}

void letterJumbleToWord(String startWord, String endWord, int xOffset, int yOffset) {  
  int w = Drawing::stringAdvance(endWord);
  laser.setScale(3048./w);
  laser.setOffset(xOffset,yOffset);
  for (int i = 0;i<35;i++) {
    Drawing::drawString(startWord, -w/2,0,4);
    for (int i = 0;i<8;i++){ 

      if (endWord[i]>startWord[i]) startWord[i]++;
      if (endWord[i]<startWord[i]) startWord[i]--;
    }
  }

  unsigned long Time = millis();
  while(millis() - Time <= 2000) {
     Drawing::drawString(endWord,-w/2,0, 1);
  }
   int clip = 0;
   for (int i = 0;i<60;i++) {
     laser.setClipArea(clip, 0, 4095-clip, 4095);
     Drawing::drawString(endWord, -w/2,0,1);
     clip += 2048 / 50;
   }
   laser.resetClipArea();
}

void increasingFontSize(String str, int xOffset, int yOffset) {
  int w = Drawing::stringAdvance(str);
  laser.setScale(0.01);
  laser.setOffset(xOffset, yOffset); // Max value is 4096.
  float scale = 0;
  for (int i = 0; i<70;i++) {
    scale += 0.01;
    laser.setScale(scale);
    Drawing::drawString(str,-w/2, -500);
  }
}

void rotateStringX(String str, int xOffset, int yOffset) {
  int w = Drawing::stringAdvance(str);
  laser.setScale(0.5);
  laser.setOffset(xOffset,yOffset);
  int count = 360/4;
  int angle = 0;
  for (int i = 0;i<count;i++) {
    Matrix3 world;
    world = Matrix3::rotateX(angle % 360);
    laser.setEnable3D(true);
    laser.setMatrix(world);
    laser.setZDist(2000);
    Drawing::drawString(str,-w/2,-500, 1);
    angle += 8;
  }
  laser.setEnable3D(false);
}
void rotateStringY(String str, int xOffset, int yOffset) {
  int w = Drawing::stringAdvance(str);
  laser.setScale(0.5);
  laser.setOffset(xOffset,yOffset);
  int count = 360/4;
  int angle = 0;
  for (int i = 0;i<count;i++) {
    Matrix3 world;
    world = Matrix3::rotateY(angle % 360);
    laser.setEnable3D(true);
    laser.setMatrix(world);
    laser.setZDist(2000);
    Drawing::drawString(str,-w/2,-500, 1);
    angle += 8;
  }
  laser.setEnable3D(false);
}

void countDown() { // Draw circle and count down from 9 to 1.
  laser.setScale(1);
  laser.setOffset(2048,2048);
  int center = Drawing::advance('9'); // Initiates the locations of the nodes and allows for the width of the object to be determined.
  for (char j = '9';j>'0';j--) {
    float scale = 0.0;
    float step = 0.01;
    for (int i = 0;i<40;i++) {
      laser.setScale(1);
      circle(); // Creates the circle.
      laser.setScale(scale);
      Drawing::drawLetter(j, -center/3, -center*2/3 + 100);   
      scale += step;
      step += 0.002;
    }
  }
}

void circle() { // draw a circle using sin/cos
  const int scale = 12;
  laser.setScale(1);
  laser.setOffset(2048,2048);
  laser.sendto(SIN(0)/scale, COS(0)/scale);
  laser.on();
  for (int r = 5;r<=360;r+=5)
  {    
    laser.sendto(SIN(r)/scale, COS(r)/scale);
  }
  laser.off();
}

void VandeGraaffSimulation(int count, int xOffset, int yOffset) {
  laser.setScale(2);
  laser.setOffset(xOffset,yOffset);
  for (int i = 0;i<count;i++) {
    laser.on();
    int pos = random(360)/5 * 5;
    int diff1 = random(35);
    int diff2 = random(35);
    int diff3 = random(35);
    for (int r = 0;r<=360;r+=5)
    {    
      laser.sendto(SIN(r)/16, COS(r)/16);
      if (r == pos)   {    
        laser.sendto(SIN(r+diff1)/32, COS(r+diff2)/32);
        laser.sendto(SIN(r+diff2)/64, COS(r+diff3)/64);
        laser.sendto(0, 0);
        laser.sendto(SIN(r+diff3)/64, COS(r+diff3)/64);
        laser.sendto(SIN(r+diff2)/32, COS(r+diff1)/32);
        laser.sendto(SIN(r)/16, COS(r)/16);
      }
    }
  }
}
