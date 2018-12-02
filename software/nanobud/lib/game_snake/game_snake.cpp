#include "game_snake.h"

GameSnake::GameSnake(U8G2 *display, Sound *sound, Vibrator *vibrator)
    : display(display), sound(sound), vibrator(vibrator)
{
}

void GameSnake::init()
{
    this->displayWidth = this->display->getWidth();
    this->displayHeight = this->display->getHeight();

    this->display->setFont(u8g_font_unifont);

    this->snake.init();
    this->food.init(&this->snake);
}

void GameSnake::loop(unsigned long nowMs, unsigned long dtMs)
{
    if (!this->display->nextPage())
    {
        this->display->firstPage();
    }

    // TODO Only in normal mode

    if (this->gameState == GAME_INIT)
    {
        this->displayRestart();
    }
    else if (this->gameState == GAME_NORMAL)
    {
        // TODO check food
        // TODO check hits

        if (this->food.wasEaten())
        {
            this->snake.grow();
            this->food.generateNewFood();
            this->sound->playEnemyDestroyed();
            this->vibrator->playEnemyDestroyed();
        }

        if (this->snake.step(dtMs))
        {
            this->snake.draw(this->display);
            this->food.draw(this->display);
        }
        else
        {
            this->gameState = GAME_OVER;
            this->sound->playEndMusic();
            this->vibrator->playEndMusic();
        }
    }
    else if (gameState == GAME_OVER)
    {
        this->display->drawStr(30, 15, "Game over");
    }
}

void GameSnake::displayRestart()
{
    // TODO splash screen
    this->display->drawStr(30, 15, "Snake Game");
    // this->display->drawXBMP(0, 0, this->displayWidth, this->displayHeight, (const uint8_t *)splash);
}

void GameSnake::repeatPressEvent(Button button, unsigned long nowMs)
{
}

void GameSnake::pressEvent(Button button, unsigned long nowMs)
{
    if (this->gameState == GAME_INIT || this->gameState == GAME_OVER)
    {
        this->gameState = GAME_NORMAL;
        this->snake.reset();
        this->food.reset();
    }
    else if (this->gameState == GAME_NORMAL)
    {
        switch (button)
        {
        case BT_UP:
            this->snake.setDirection(DIR_UP);
            break;
        case BT_RIGHT:
            this->snake.setDirection(DIR_RIGHT);
            break;
        case BT_DOWN:
            this->snake.setDirection(DIR_DOWN);
            break;
        case BT_LEFT:
            this->snake.setDirection(DIR_LEFT);
            break;
        }
    }
}
