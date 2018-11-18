#include "game_menu.h"

#define MENU_ITEMS 2
char *menu_strings[MENU_ITEMS] = { "Space Invader", "Snake" };

GameMenu::GameMenu(U8G2 *display, Sound *sound, Vibrator *vibrator)
    : display(display), sound(sound), vibrator(vibrator)
{
}

void GameMenu::init()
{
    this->displayWidth = this->display->getWidth();
    this->displayHeight = this->display->getHeight();

    this->display->setFont(u8g2_font_profont15_tr);
}


void GameMenu::loop(unsigned long nowMs, unsigned long dtMs)
{
    if (this->gameState == GameMenuState::GAME_NORMAL)
    {
        this->game->loop(nowMs, dtMs);
        return;
    }

    if (!this->display->nextPage())
    {
        this->display->firstPage();
    }

    if (this->gameState == GameMenuState::GAME_INIT)
    {
        this->displayRestart();

        // TODO timeout switch to MENU
    }
    else if (this->gameState == GameMenuState::GAME_MENU)
    {
        this->drawMenu();
    }
}

void GameMenu::displayRestart()
{
    this->display->drawXBMP(0, 0, this->displayWidth, this->displayHeight, logo);
}

void GameMenu::drawMenu() {
  uint8_t i, d;
  u8g2_uint_t  h = this->display->getAscent() - this->display->getDescent();
  u8g2_uint_t  w = this->displayWidth;
  // header
  char title[] = "[ Nano Bud ]";
  this->display->setDrawColor(1);
  this->display->drawBox(0, 0, w, h + 2);
  d = (w - this->display->getStrWidth(title))/2;
  this->display->setDrawColor(0);
  this->display->drawStr(d, h, title);

  for( i = 0; i < MENU_ITEMS; i++ ) {        // draw all menu items
    d = (w - this->display->getStrWidth(menu_strings[i]))/2;
    this->display->setDrawColor(1);
    if ( i == this->currentMenu ) {               // current selected menu item
      this->display->drawBox(0, (i+1)*(h+1) + 2, w, h);     // draw cursor bar
      this->display->setDrawColor(0);
    }
    this->display->drawStr(d, (i+1) * h + (h + i + 2), menu_strings[i]);
  }
}

void GameMenu::repeatPressEvent(Button button, unsigned long nowMs)
{
    if (this->gameState == GameMenuState::GAME_NORMAL)
    {
        this->game->repeatPressEvent(button, nowMs);
    }
}

void GameMenu::pressEvent(Button button, unsigned long nowMs)
{
    if (this->gameState == GameMenuState::GAME_INIT)
    {
        this->gameState = GameMenuState::GAME_MENU;
    }
    else if (this->gameState == GameMenuState::GAME_MENU)
    {
        switch (button)
        {
        case BT_UP:
            if ( this->currentMenu == 0 )
                this->currentMenu = MENU_ITEMS;
            this->currentMenu--;
            break;
        case BT_RIGHT:
            break;
        case BT_DOWN:
            this->currentMenu++;
            if ( this->currentMenu >= MENU_ITEMS )
                this->currentMenu = 0;
            break;
        case BT_LEFT:
            break;
        case BT_CENTER:
            // ensure that we set default mode if game does not
            this->display->setDrawColor(1);
            if (this->currentMenu == 0)
            {
                this->game = new GameSpaceInvaders(this->display, this->sound, this->vibrator);
            }
            else if (this->currentMenu == 1)
            {
                this->game = new GameSnake(this->display, this->sound, this->vibrator);
            }
            this->gameState = GameMenuState::GAME_NORMAL;
            this->game->init();
            break;
        }
    }
    else {
        this->game->pressEvent(button, nowMs);
    }
}
