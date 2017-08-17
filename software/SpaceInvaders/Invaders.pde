//The aliens class, takes in X, Y, and the images for the alien. Holds methods to move and draw.
class invaders{
  float size = 40;
  float myX;
  float myY;
  float xSpeed = 1;
  PImage frameA;
  PImage frameB;
  int frames = 0;
  boolean alive = true;
  invaders(float X, float Y, PImage first, PImage second) {
    myX = X;
    myY = Y;
    frameA = first;
    frameB = second;
  }
  
  void draw() {
    if(alive) {
      if(frames < 30) {
        image(frameA, myX, myY, 70, 50);
      } else {
        image(frameB, myX, myY, 70, 50);
      }
      frames += 1;
      if(frames > 60) {
        frames = 0;
      }
    }
  }
  void move() {
    myX += xSpeed;
  }
}
