#include <Arduino.h>
#include <U8g2lib.h>

#include "constants.h"
#include <input.h>
#include <sound.h>
#include <vibrator.h>

#if GAME == GAME_SPACE_INVADERS
    #include <game_spaceinvaders.h>
#elif GAME == GAME_SNAKE
    #include <game_snake.h>
#elif GAME == GAME_MAIN_MENU
    #include <game_menu.h>
#endif

U8G2_SSD1306_128X64_NONAME_1_HW_I2C display(U8G2_R0); // I2C: SCL=A5,SDA=A4

Vibrator vibrator(PIN_VIBRATOR);
Sound sound(PIN_BUZZER);

#if GAME == GAME_SPACE_INVADERS
    GameSpaceInvaders game(&display, &sound, &vibrator);
#elif GAME == GAME_SNAKE
    GameSnake game(&display, &sound, &vibrator);
#elif GAME == GAME_MAIN_MENU
    GameMenu game(&display, &sound, &vibrator);
#endif


Input input(PIN_CENTER, PIN_LEFT, PIN_RIGHT, PIN_TOP, PIN_BOTTOM, &game);

unsigned long lastLoop = 0;

void setup()
{
    Serial.begin(115200);

    Serial.println("start");
    display.begin();
    input.init();
    sound.init();
    vibrator.init();
    game.init();
}

void loop()
{
    unsigned long nowMs = millis();
    unsigned long dtMs = nowMs - lastLoop;

    input.loop(nowMs, dtMs);
    sound.loop(dtMs);
    vibrator.loop(dtMs);
    game.loop(nowMs, dtMs);

    lastLoop = nowMs;
}
