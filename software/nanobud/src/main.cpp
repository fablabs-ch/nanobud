#include <Arduino.h>
#include <U8glib.h>

#include "constants.h"
#include <input.h>
#include <sound.h>
#include <game_spaceinvaders.h>

U8GLIB_SSD1306_128X64 display(U8G_I2C_OPT_NONE); // I2C: SCL=A5,SDA=A4

Sound sound(PIN_BUZZER);
GameSpaceInvaders game(&display, &sound);
Input input(PIN_CENTER, PIN_LEFT, PIN_RIGHT, PIN_TOP, PIN_BOTTOM, &game);

// void encoderChange(){
//     input.changeDetected();
// }

unsigned long lastLoop = 0;

void setup(){
  Serial.begin(115200);

  Serial.println("start");

  input.init();
  sound.init();
  game.init();

  // attachInterrupt(0, encoderChange, CHANGE);
  // attachInterrupt(1, encoderChange, CHANGE);
}

void loop(){
    unsigned long nowMs = millis();
    unsigned long dtMs = nowMs - lastLoop;

    input.loop(nowMs, dtMs);
    sound.loop(dtMs);
    game.loop(nowMs, dtMs);

    lastLoop = nowMs;
}
