#include "game_spaceinvaders.h"

GameSpaceInvaders::GameSpaceInvaders(U8GLIB *display, Sound *sound, Vibrator *vibrator)
    : display(display), sound(sound), vibrator(vibrator)
{
}

void GameSpaceInvaders::init()
{
    this->displayWidth = this->display->getWidth();
    this->displayHeight = this->display->getHeight();

    this->ship.init(this->displayWidth, this->displayHeight);
    this->lasers.init(this->sound, this->vibrator);
    this->monsters.init(this->sound, this->vibrator, &(this->lasers), this->displayWidth, this->displayHeight);

    this->monsters.initLevel(level_0, 0, 0, 6, 4, 100);

    this->display->setFont(u8g_font_unifont);
}

void GameSpaceInvaders::loop(unsigned long nowMs, unsigned long dtMs)
{
    if (!this->display->nextPage())
    {
        this->display->firstPage();
    }
    if (this->gameState == GAME_INIT)
    {
        this->displayRestart();
    }
    else if (this->gameState == GAME_SHOW_LEVEL)
    {
        this->displayLevel();
    }
    else if (this->gameState == GAME_NORMAL)
    {
        this->ship.draw(this->display);
        this->lasers.draw(this->display);
        this->monsters.draw(this->display);

        this->ship.step();
        this->lasers.step(dtMs);
        if (this->monsters.step(dtMs))
        {
            DEBUG_GAME_PRINTLN("Game over");
            this->sound->playEndMusic();
            this->setGameState(GAME_OVER, nowMs);
        }
        if (this->monsters.hitTest())
        {
            DEBUG_GAME_PRINTLN("Game win");
            this->sound->playEndMusic();
            this->setGameState(GAME_WIN, nowMs);
            this->level++;
        }
    }
    else if (gameState == GAME_OVER)
    {
        this->display->drawStr(30, 15, "Game over");
    }
    else
    {
        this->display->drawStr(30, 15, "Game win");
    }
}

void GameSpaceInvaders::displayRestart()
{
    this->display->drawXBMP(0, 0, this->displayWidth, this->displayHeight, (const uint8_t *)splash);
}

void GameSpaceInvaders::displayLevel()
{
    this->display->drawStr(45, 20, "Level");
    this->display->drawStr(60, 40, String(this->level).c_str());
}

void GameSpaceInvaders::move(int delta)
{
    this->ship.move(delta);
}

void GameSpaceInvaders::fire()
{
    this->lasers.add(this->ship.getX(), this->ship.getY());
}

void GameSpaceInvaders::setGameState(enum GameSpaceInvadersState gameState, unsigned long nowMs)
{
    this->gameStateLastChange = nowMs;
    this->gameState = gameState;
}

void GameSpaceInvaders::repeatPressEvent(Button button, unsigned long nowMs)
{

    if (this->gameState == GAME_NORMAL)
    {
        switch (button)
        {
        case TOP:
        case CENTER:
            this->fire();
            break;
        case RIGHT:
            this->move(5);
            break;
        case LEFT:
            this->move(-5);
            break;
        }
    }
}

void GameSpaceInvaders::pressEvent(Button button, unsigned long nowMs)
{
    if (this->gameState == GAME_INIT || this->gameState == GAME_OVER || this->gameState == GAME_WIN)
    {
        this->setGameState(GAME_SHOW_LEVEL, nowMs);
    }
    else if (this->gameState == GAME_SHOW_LEVEL)
    {
        this->monsters.initLevel(level_0, 0, 0, 6, 4, 100 - this->level * 10);
        this->lasers.reset();
        this->setGameState(GAME_NORMAL, nowMs);
    }
}
