#include "game_spaceinvaders.h"

GameSpaceInvaders::GameSpaceInvaders(U8GLIB* display, Sound* sound)
 : display(display), sound(sound){

}

void GameSpaceInvaders::init(){
    this->displayWidth = this->display->getWidth();
    this->displayHeight = this->display->getHeight();

    this->ship.init(this->displayWidth, this->displayHeight);
    this->lasers.init(this->sound);
    this->monsters.init(this->sound, &(this->lasers), this->displayWidth, this->displayHeight);

    this->monsters.initLevel(level_0, 0, 0, 6, 4, 100);

    this->display->setFont(u8g_font_unifont);

    // this->display->firstPage();
    // do {
    //     this->display->drawXBMP(0, 0, this->displayWidth, this->displayHeight, (const uint8_t*) splash);
    // } while (this->display->nextPage());
}

void GameSpaceInvaders::loop(unsigned long nowMs, unsigned long dtMs){
    if(!this->display->nextPage()){
        this->display->firstPage();
    }
    if(this->gameState == GAME_INIT){
        this->displayRestart();
    }else if(this->gameState == GAME_NORMAL){
        // do {
            this->ship.draw(this->display);
            this->lasers.draw(this->display);
            this->monsters.draw(this->display);
            //TODO Hit tests
        // } while (this->display->nextPage());

        this->ship.step();
        this->lasers.step(dtMs);
        if(this->monsters.step(dtMs)){
            DEBUG_GAME_PRINTLN("Game over");
            this->sound->playEndMusic();
            this->setGameState(GAME_OVER, nowMs);
        }
        if(this->monsters.hitTest()){
            DEBUG_GAME_PRINTLN("Game win");
            this->sound->playEndMusic();
            this->setGameState(GAME_WIN, nowMs);
        }
    }else if(gameState == GAME_OVER){
        this->display->drawStr(30, 15, "Game over");
        this->displayRestart();
    }else{
        this->display->drawStr(30, 15, "Game win");
        this->displayRestart();
    }
}

void GameSpaceInvaders::displayRestart(){
    this->display->drawStr(10, 45, "Press top for");
    this->display->drawStr(35, 60, "restart");
}

void GameSpaceInvaders::move(int delta){
     this->ship.move(delta);
}

void GameSpaceInvaders::fire(){
     this->lasers.add(this->ship.getX(), this->ship.getY());
}

void GameSpaceInvaders::setGameState(enum GameSpaceInvadersState gameState, unsigned long nowMs){
    this->gameStateLastChange = nowMs;
    this->gameState = gameState;
}

void GameSpaceInvaders::repeatPressEvent(Button button, unsigned long nowMs){
    switch (button) {
        case CENTER:
             this->fire();
        break;
        case RIGHT:
            this->move(5);
            break;
        case LEFT:
            this->move(-5);
            break;
        case TOP:
            this->monsters.initLevel(level_0, 0, 0, 6, 4, 100);
            this->lasers.reset();
            this->setGameState(GAME_NORMAL, nowMs);

    }
}


void GameSpaceInvaders::pressEvent(Button button, unsigned long nowMs){}
