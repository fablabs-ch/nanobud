#ifndef _GAME_SNAKE_H
#define _GAME_SNAKE_H

#include <Arduino.h>
#include <sound.h>
#include <vibrator.h>
#include <inputlistener.h>
#include <U8glib.h>

#include "types.h"
#include "snake.h"


// #define DEBUG_GAME

#ifdef DEBUG_GAME
    #define DEBUG_GAME_PRINT(x)  Serial.print (x)
    #define DEBUG_GAME_PRINTLN(x)  Serial.println (x)
#else
    #define DEBUG_GAME_PRINT(x)
    #define DEBUG_GAME_PRINTLN(x)
#endif



class GameSnake : public InputListener {
public:
    GameSnake(U8GLIB* display, Sound* sound, Vibrator* vibrator);

    void init();
    void loop(unsigned long nowMs, unsigned long dtMs);

    void repeatPressEvent(Button button, unsigned long nowMs);

    void pressEvent(Button button, unsigned long nowMs);

private:
    U8GLIB* display;
    Sound* sound;
    Vibrator* vibrator;

    int displayWidth;
    int displayHeight;

    unsigned long gameStateLastChange;
    enum GameSnakeState gameState = GAME_INIT;

    Snake snake;

};
#endif
