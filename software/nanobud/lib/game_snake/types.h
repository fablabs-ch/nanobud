#ifndef _GAME_SNAKE_TYPES_H
#define _GAME_SNAKE_TYPES_H

#include <Arduino.h>

enum GameSnakeState
{
    GAME_INIT,
    GAME_SHOW_LEVEL,
    GAME_NORMAL,
    GAME_WIN,
    GAME_OVER
};

typedef struct Position
{
    uint8_t x;
    uint8_t y;
} Position;

enum Direction
{
    DIR_NONE,
    DIR_UP,
    DIR_RIGHT,
    DIR_DOWN,
    DIR_LEFT,
    DIR_HEAD
};

#endif
