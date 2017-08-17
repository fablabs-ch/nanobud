//Defines the missles that are shot by the ship at the aliens.
class missiles {
  float myX;
  float myY;
  float mySpeed = 5.0;
  missiles( float X, float Y) {
    myX = X;
    myY = Y;
  }
 void update() {
   fill(255,0,0);
   myY -= mySpeed;
   rect(myX, myY, 5, 10);
 }
}
