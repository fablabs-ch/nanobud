//Booleans used to determine game state.
boolean levelActive = false;
boolean noPlay = false;

//Global image variables.
PImage bg;
PImage player;
PImage bonus;
PImage alien1a;
PImage alien1b;
PImage alien2a;
PImage alien2b;
PImage alien3a;
PImage alien3b;
PImage temp1;
PImage temp2;

//Global Fonts
PFont scoreFont;
PFont levelFont;

//Storage and usage ints for the program.
int levelA;
int level=1;
int scorecount;
int levelScore;
int rowCount = 2;
int levelPause = 0;
int randomBomb;

//Arraylists to hold the various objects in the arena, allowing us to remove destoryed objects.
ArrayList<invaders> aliens = new ArrayList<invaders>();
ArrayList<missiles> bullets = new ArrayList<missiles>();
ArrayList<bombs> alienBombs = new ArrayList<bombs>();

// setup sets the beginning
void setup (){

//set screensize/color
size(1000, 800);


//smooth down edges of shapes(anti-aliasing)
smooth();

///////////////// IMAGES AND FONTS/////////////////
// All the images and fonts are ready and loaded
bg = loadImage("bg.jpg");
player = loadImage("player.png");
bonus = loadImage("bonus.png");
alien1a = loadImage("alien1a.png");
alien1b = loadImage("alien1b.png");
alien2a = loadImage("alien2a.png");
alien2b = loadImage("alien2b.png");
alien3a = loadImage("alien3a.png");
alien3b = loadImage("alien3b.png");
scoreFont = loadFont("scoreFont.vlw");
levelFont = loadFont("levelFont.vlw");
scorecount = 0;
int startX = 500;
int startY = 100;
levelA = 255;

/*This code creates and and loads the aliens into the array. It uses the rowcount variable to know
how many aliens to create and varies the type of alien on every line. 
*/
int alienY = 60;
for(int i=0; i<=rowCount; i++) {
  float location = 140.0;
  if(i==0) {
    temp1 = alien1a;
    temp2 = alien1b;
  } else if( i==1 ) {
    temp1 = alien2a;
    temp2 = alien2b;
  } else if( i==2 ) {
    temp1 = alien3a;
    temp2 = alien3b;
  }
  for( int j=0; j<10; j++) {
    invaders invader = new invaders(location, alienY, temp1, temp2);
    aliens.add(invader);
    location += 70;
  }
  alienY += 60;
  }
}





// draw loops infinetly (some variables change over time)
void draw (){
image(bg, 0, 0);
noStroke();
textFont(scoreFont, 48);
fill(0, 255, 0);
text(scorecount, 50, 75);

//Generates a random number and uses that number to determine whether or not to drop a bomb.
//When the program drops a bomb it uses another random number to determine which alien willd drop it.
//If this alien is alive then a bomb is created and dropped.
randomBomb = (int) random(0,1000);
if(randomBomb > 990 && !noPlay ) {
  int randomAlien;
  randomAlien = (int) random(0,aliens.size());
  invaders temp = aliens.get(randomAlien);
  if(temp.alive){
    bombs bomb = new bombs(temp.myX, temp.myY);
    alienBombs.add(bomb);
  }
}

//Causes the bombs to update themselves and check if they have intersected with the player object.
for(int i=0; i<alienBombs.size(); i++) {
   bombs temp = alienBombs.get(i);
   temp.update();
  if(temp.myY+50 >=height-70 && temp.myX <= mouseX-(player.width/2) +60 && temp.myX+70 >= mouseX-(player.width/2)) {
    gameOver();
    alienBombs.clear();
  }
}

//Draw and moves the aliens. If one alien is found to be touching the side the program calls the 
//move down method. Also checks to see if any aliens have intersectd the player and ended the game.
//Chekcs the missle objects to see if they have intersected, killing the alien.
for(int i=0; i<aliens.size(); i++) {
  invaders temp = aliens.get(i);
  temp.draw();
  temp.move();
  if(temp.alive && (temp.myX == width - 60 ||
      temp.myX == -15)) {
    dropDown();
  }
  if(temp.alive && temp.myY+50 >=height-70 && temp.myX <= mouseX-(player.width/2) +60 && temp.myX+70 >= mouseX-(player.width/2)) {
    gameOver();
  }
  for(int j=0; j<bullets.size(); j++) {
    missiles bullet = bullets.get(j);
    if(bullet.myX<0) {
      bullets.remove(j);
    }
    if(temp.alive) {
      if(bullet.myX+5 >= temp.myX && bullet.myX<= temp.myX+65) {
        if(bullet.myY <= temp.myY+50 && bullet.myY+10 >= temp.myY) {
           temp.alive = false;
           scorecount++;
           levelScore++;
           bullets.remove(j);
        }
      }
    }
  }
}

//Updates the missiles that are created with the space bar. 
for(int i=0; i<bullets.size(); i++) {
  bullets.get(i).update();
}

//If the score in an individual level equals the number of aliens, then all aliens are dead
//when this happens the game adds a row and shows the next level text. 
if(levelScore == rowCount*10 + 10) {
  levelActive = true;
  levelScore = 0;
  level++;
  bullets.clear();
  alienBombs.clear();
}

//If in a level transition, the text slowly fades on a count. Once the count reaches two seconds,
//the game is reset and all variables are set to their necessary values. 
if(levelActive) {
  levelPause++;
  levelA -= 255/120;
  if(levelPause >= 120) {
    levelActive = false;
    levelPause = 0;
    levelA = 255;
    rowCount += 1;
    reset();
  }
}

////////////////// NEXT LEVEL TEXT //////////////////////
// Use levelA (opacity) to fade out, add an if statement to determine
// when to display. The boolean is just a place indication
if(levelActive == true && level == 2){
  fill(255, levelA);
  textFont(levelFont, 125);
  text("Level 2", 50, height/1.5);
} else if(levelActive == true && level == 3 ){
  fill(255, levelA);
  textFont(levelFont, 125);
  text("Level 3", 50, height/1.5);
}else if(levelActive == true && level == 4){
  fill(255, levelA);
  textFont(levelFont, 125 );
  text("Level 4", 50, height/1.5);
}else if(levelActive == true && level == 5){
  fill(255, levelA);
  textFont(levelFont, 125);
  text("Level 5", 50, height/1.5);
}

//The actual player object.
image(player, mouseX-(player.width/2), (height-80));

//Code to display text when the game is over. 
if(noPlay) {
    textFont(levelFont, 90);
    text("Game Over", 100, height/2);
    textFont(levelFont, 40);
    text("Hit Space to Reset", 140, height/2 + 50);
    
}
}

//Monitors for keyboard commands.
void keyPressed() {
  //if the game is being played then a bullet object is created and loaded into the array. 
  if(key == ' ' && !noPlay) {
    missiles temp = new missiles(mouseX-2.5, height-80);
    bullets.add(temp); 
  //If the game is not being played and space bar is pressed then the game is reset and all
  //variables are reset to their necessary restart values. 
  } else if(key == ' ' && noPlay) {
    scorecount = 0;
    levelScore = 0;
    rowCount = 2;
    level = 1;
    reset();
    noPlay = false;
  }
}

//Drops the aliens down one row and changes their direction. 
void dropDown() {
  for(int i=0; i<aliens.size(); i++) {
    aliens.get(i).xSpeed = -aliens.get(i).xSpeed;
    aliens.get(i).myY += 40; 
  }
}

//Clears the aliens and loads a new set of them into the arrays
void reset() {
  aliens.clear();
  int alienY = 70;
  for(int i=0; i<=rowCount; i++) {
  float location = 140.0;
  if(i==0 || i==3) {
    temp1 = alien1a;
    temp2 = alien1b;
  } else if( i==1 || i==4) {
    temp1 = alien2a;
    temp2 = alien2b;
  } else if( i==2 || i==5) {
    temp1 = alien3a;
    temp2 = alien3b;
  }
  for( int j=0; j<10; j++) {
    invaders invader = new invaders(location, alienY, temp1, temp2);
    aliens.add(invader);
    location += 70;
  }
  alienY += 60;
}
}

//Clears everything for a game over event. 
void gameOver() {
  noPlay = true;
  aliens.clear();
  bullets.clear();
}
