#ifndef _GAME_SNAKE_TYPES_H
#define _GAME_SNAKE_TYPES_H

#include <Arduino.h>


#define SNAKE_MAX_X 16
#define SNAKE_MAX_Y 8

enum class GameSnakeState
{
    GAME_INIT,
    GAME_NORMAL,
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
