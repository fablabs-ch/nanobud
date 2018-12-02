#ifndef _GAME_SNAKE_FOOD_H
#define _GAME_SNAKE_FOOD_H

#include <U8g2lib.h>
#include "types.h"
#include "snake.h"

// #define DEBUG_GAME_SNAKE_FOOD

#ifdef DEBUG_GAME_SNAKE_FOOD
#define DEBUG_GAME_SNAKE_FOOD_PRINT(x) Serial.print(x)
#define DEBUG_GAME_SNAKE_FOOD_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_GAME_SNAKE_FOOD_PRINT(x)
#define DEBUG_GAME_SNAKE_FOOD_PRINTLN(x)
#endif

class Food
{
  public:
    Food()
    {
    }

    void init(Snake *snake)
    {
        this->snake = snake;
        reset();
    }

    void reset()
    {
        randomSeed(millis());
        this->generateNewFood();
    }

    void generateNewFood()
    {
        uint8_t x = random(0, SNAKE_MAX_X);
        uint8_t y = random(0, SNAKE_MAX_Y);

        Direction dir;
        do
        {
            x++;
            if (x >= SNAKE_MAX_X)
            {
                y++;
                x = 0;
            }
            if (y >= SNAKE_MAX_Y)
            {
                y = 0;
            }
            dir = this->snake->snakePresent[x][y];
        } while (dir != DIR_NONE);
        this->position = {.x = x, .y = y};
        DEBUG_GAME_SNAKE_FOOD_PRINT("FOOD: x=");
        DEBUG_GAME_SNAKE_FOOD_PRINT(x);
        DEBUG_GAME_SNAKE_FOOD_PRINT(" y=");
        DEBUG_GAME_SNAKE_FOOD_PRINT(y);
        DEBUG_GAME_SNAKE_FOOD_PRINTLN();
    }

    bool wasEaten()
    {
        return this->position.x == this->snake->headPosition.x && this->position.y == this->snake->headPosition.y;
    }

    void draw(U8G2 *display)
    {
        display->drawCircle(this->position.x * 8 + 4, this->position.y * 8 + 4, 3);
        display->drawPixel(this->position.x * 8 + 4, this->position.y * 8 + 4);
    }

  private:
    Position position;
    Snake *snake;
};

#endif
