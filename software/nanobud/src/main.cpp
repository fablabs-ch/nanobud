#include <Arduino.h>
#include <U8glib.h>

#include "constants.h"
#include <input.h>
#include <sound.h>
#include <game_spaceinvaders.h>

U8GLIB_SSD1306_128X64 display(U8G_I2C_OPT_NONE); // I2C: SCL=A5,SDA=A4

Sound sound(PIN_BUZZER);
GameSpaceInvaders game(&display, &sound);
Input input(PIN_ROTARY_BUTTON, PIN_ROTARY_A, PIN_ROTARY_B, &game);

unsigned long lastLoop = 0;

void setup(){
  Serial.begin(115200);

  Serial.println("start");

  input.init();
  sound.init();
  game.init();

}

void loop(){
    unsigned long now = millis();
    unsigned long dtMs = now - lastLoop;

    input.loop(dtMs);
    sound.loop(dtMs);
    game.loop(dtMs);

    lastLoop = now;
}
