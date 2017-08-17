//Handles the bombs that are dropped by the aliens. 
class bombs {
  float myX;
  float myY;
  float mySpeed = 5.0;
  bombs(float X, float Y) {
    myX = X;
    myY = Y;
  }
  void update() {
    fill(255,0,0);
    rect(myX+35, myY+ 70, 25,25);
    myY += mySpeed;
  }
}
