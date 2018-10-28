#ifndef _GAME_SNAKE_SNAKE_H
#define _GAME_SNAKE_SNAKE_H

#include <U8glib.h>
#include "types.h"

#define DEBUG_GAME_SNAKE

#ifdef DEBUG_GAME_SNAKE
#define DEBUG_GAME_SNAKE_PRINT(x) Serial.print(x)
#define DEBUG_GAME_SNAKE_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_GAME_SNAKE_PRINT(x)
#define DEBUG_GAME_SNAKE_PRINTLN(x)
#endif

// 16x8 = 128

#define SNAKE_MAX_X 16
#define SNAKE_MAX_Y 8

class Snake
{
  public:
    Snake()
    {
    }

    void init()
    {
        reset();
    }

    void reset()
    {
        memset(this->snakePresent, 0, 16 * 8);
        this->snakePresent[0][2] = DIR_RIGHT;
        this->snakePresent[1][2] = DIR_RIGHT;
        this->snakePresent[2][2] = DIR_RIGHT;
        this->snakePresent[3][2] = DIR_RIGHT;
        this->snakePresent[4][2] = DIR_RIGHT;
        this->snakePresent[5][2] = DIR_RIGHT;
        this->snakePresent[6][2] = DIR_RIGHT;
        this->snakePresent[7][2] = DIR_RIGHT;
        this->snakePresent[8][2] = DIR_RIGHT;
        this->snakePresent[9][2] = DIR_HEAD;
        this->tailPosition = {.x = 2, .y = 2};
        this->headPosition = {.x = 9, .y = 2};
    }

    Position getNextPosition(Position from, Direction direction)
    {
        Position to = {.x = from.x, .y = from.y};
        if (direction == DIR_DOWN)
        {
            to.y++;
            if (to.y >= SNAKE_MAX_Y)
            {
                to.y = 0;
            }
        }
        else if (direction == DIR_UP)
        {
            to.y--;
            if (to.y <= 0)
            {
                to.y = SNAKE_MAX_Y - 1;
            }
        }
        else if (direction == DIR_LEFT)
        {
            to.x--;
            if (to.x <= 0)
            {
                to.x = SNAKE_MAX_X - 1;
            }
        }
        else if (direction == DIR_RIGHT)
        {
            to.x++;
            if (to.x >= SNAKE_MAX_X)
            {
                to.x = 0;
            }
        }
        return to;
    }

    void step(unsigned long dtMs)
    {
        this->nextMove -= min(dtMs, this->nextMove);
        if (this->nextMove == 0)
        {
            this->nextMove = 2000;

            Position nextTailPosition = this->getNextPosition(this->tailPosition, this->snakePresent[this->tailPosition.x][this->tailPosition.y]);
            this->snakePresent[this->tailPosition.x][this->tailPosition.y] = DIR_NONE;
            this->tailPosition = nextTailPosition;

            Position nextHeadPosition = this->getNextPosition(this->headPosition, this->currentDirection);
            this->snakePresent[this->headPosition.x][this->headPosition.y] = this->currentDirection;
            this->snakePresent[nextHeadPosition.x][nextHeadPosition.y] = DIR_HEAD;
            this->headPosition = nextHeadPosition;

            DEBUG_GAME_SNAKE_PRINT("HEAD: x=");
            DEBUG_GAME_SNAKE_PRINT(nextHeadPosition.x);
            DEBUG_GAME_SNAKE_PRINT(" y=");
            DEBUG_GAME_SNAKE_PRINT(nextHeadPosition.y);
            DEBUG_GAME_SNAKE_PRINTLN();
            this->printNext = true;
        }
    }

    void draw(U8GLIB *display)
    {
        Position pos = this->tailPosition;
        Direction dir = DIR_NONE;
        do
        {
            dir = this->snakePresent[pos.x][pos.y];
            Position nextPos = this->getNextPosition(pos, dir);

            switch (dir)
            {
            case DIR_UP:
                display->drawBox(pos.x * 8 + 1, pos.y * 8 - 1, 6, 8);
                break;
            case DIR_DOWN:
                display->drawBox(pos.x * 8 + 1, pos.y * 8 + 1, 6, 8);
                break;
            case DIR_RIGHT:
                display->drawBox(pos.x * 8 + 1, pos.y * 8 + 1, 8, 6);
                break;
            case DIR_LEFT:
                display->drawBox(pos.x * 8 - 1, pos.y * 8 + 1, 8, 6);
                break;
            }

            if (this->printNext)
            {
                DEBUG_GAME_SNAKE_PRINT("Pos: x=");
                DEBUG_GAME_SNAKE_PRINT(pos.x);
                DEBUG_GAME_SNAKE_PRINT(" y=");
                DEBUG_GAME_SNAKE_PRINT(pos.y);
                DEBUG_GAME_SNAKE_PRINT(" dir=");
                DEBUG_GAME_SNAKE_PRINT(dir);
                DEBUG_GAME_SNAKE_PRINT(" head=");
                DEBUG_GAME_SNAKE_PRINT(DIR_HEAD);
                DEBUG_GAME_SNAKE_PRINTLN();
            }

            pos = nextPos;
        } while (dir != DIR_HEAD);

        this->printNext = false;

        //display HEAD
        display->drawBox(pos.x * 8, pos.y * 8, 8, 8);
    }

    void setDirection(Direction dir)
    {
        bool dirH = dir == DIR_LEFT || dir == DIR_RIGHT;
        bool curDirH = this->currentDirection == DIR_LEFT || this->currentDirection == DIR_RIGHT;
        if (dirH != curDirH)
        {
            this->currentDirection = dir;
        }
    }

  private:
    unsigned long nextMove = 0;
    Direction currentDirection = DIR_RIGHT;

    Direction snakePresent[SNAKE_MAX_X][SNAKE_MAX_Y];
    Position headPosition;
    Position tailPosition;

    bool printNext = false;
};

#endif
