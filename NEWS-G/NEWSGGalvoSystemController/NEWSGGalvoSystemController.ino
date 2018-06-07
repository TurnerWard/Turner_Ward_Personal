#include "Laser.h" // All the includes needed for the laser show.
#include "Drawing.h"
#include "Cube.h"
#include "Objects.h"

Laser laser(5); // Creates a laser instance with the laser pointer connected to pin 5.

void setup() {
  laser.init(); // Initiates the laser which also initiates the dac.
}

void loop() {
  //countDown();
  newsg();
  
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// HELPER FUNCTIONS ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void newsg()
{
  String str = "ARDUINO";
  int w = Drawing::stringAdvance(str);
  laser.setScale(0.5);
  laser.setOffset(1024,1024);
  int count = 360/4;
  int angle = 45;
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


void countDown() { // Draw circle and count down from 9 to 1.
  laser.setScale(1);
  laser.setOffset(2048,2048);
  int center = Drawing::advance('9');
  for (char j = '9';j>'0';j--) {
    float scale = 0.0;
    float step = 0.01;
    for (int i = 0;i<40;i++) {
      laser.setScale(1);
      circle();
      laser.setScale(scale);
      Drawing::drawLetter(j, -center/3, -center*2/3 + 100);   
      scale += step;
      step += 0.002;
    }
  }
}

void circle() { // draw a circle using sin/cos
  const int scale = 12;
  laser.sendto(SIN(0)/scale, COS(0)/scale);
  laser.on();
  for (int r = 5;r<=360;r+=5)
  {    
    laser.sendto(SIN(r)/scale, COS(r)/scale);
  }
  laser.off();
}
