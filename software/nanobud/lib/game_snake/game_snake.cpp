#include "game_snake.h"

GameSnake::GameSnake(U8GLIB *display, Sound *sound, Vibrator *vibrator)
    : display(display), sound(sound), vibrator(vibrator)
{
}

void GameSnake::init()
{
    this->displayWidth = this->display->getWidth();
    this->displayHeight = this->display->getHeight();

    this->display->setFont(u8g_font_unifont);

    this->snake.init();
}

void GameSnake::loop(unsigned long nowMs, unsigned long dtMs)
{
    if (!this->display->nextPage())
    {
        this->display->firstPage();
    }

    // TODO Only in normal mode
    this->snake.step(dtMs);
    this->snake.draw(this->display);

    // if (this->gameState == GAME_INIT)
    // {
    //     this->displayRestart();
    // }
    // else if (this->gameState == GAME_SHOW_LEVEL)
    // {
    //     this->displayLevel();
    // }
    // else if (this->gameState == GAME_NORMAL)
    // {
    //     this->ship.draw(this->display);
    //     this->lasers.draw(this->display);
    //     this->monsters.draw(this->display);

    //     this->ship.step();
    //     this->lasers.step(dtMs);
    //     if (this->monsters.step(dtMs))
    //     {
    //         DEBUG_GAME_PRINTLN("Game over");
    //         this->sound->playEndMusic();
    //         this->setGameState(GAME_OVER, nowMs);
    //         this->level = 1;
    //     }
    //     if (this->monsters.hitTest())
    //     {
    //         DEBUG_GAME_PRINTLN("Game win");
    //         this->sound->playEndMusic();
    //         this->setGameState(GAME_WIN, nowMs);
    //         this->level++;
    //     }
    // }
    // else if (gameState == GAME_OVER)
    // {
    //     this->display->drawStr(30, 15, "Game over");
    // }
    // else
    // {
    //     this->display->drawStr(30, 15, "Game win");
    // }
}

// void GameSnake::displayRestart()
// {
//     this->display->drawXBMP(0, 0, this->displayWidth, this->displayHeight, (const uint8_t *)splash);
// }

void GameSnake::repeatPressEvent(Button button, unsigned long nowMs)
{
}

void GameSnake::pressEvent(Button button, unsigned long nowMs)
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
    // if (this->gameState == GAME_INIT || this->gameState == GAME_OVER || this->gameState == GAME_WIN)
    // {
    //     this->setGameState(GAME_SHOW_LEVEL, nowMs);
    // }
    // else if (this->gameState == GAME_SHOW_LEVEL)
    // {
    //     this->monsters.initLevel(level_0, 0, 0, 6, 4, 100 - this->level * 5, this->level/5+1);
    //     this->lasers.reset();
    //     this->setGameState(GAME_NORMAL, nowMs);
    // }
}
