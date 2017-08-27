#include "game_spaceinvaders.h"

GameSpaceInvaders::GameSpaceInvaders(U8GLIB* display, Sound* sound)
 : display(display), sound(sound){

}

void GameSpaceInvaders::init(){
    this->displayWidth = this->display->getWidth();
    this->displayHeight = this->display->getHeight();

    this->ship.init(this->displayWidth, this->displayHeight);
    this->lasers.init(this->sound);

    this->display->firstPage();
    do {
        this->display->drawXBMP(0, 0, this->displayWidth, this->displayHeight, (const uint8_t*) splash);
    } while (this->display->nextPage());
}

void GameSpaceInvaders::loop(unsigned long){
    this->display->firstPage();
    if(this->gameState == GAME_NORMAL){
        do {
            this->ship.draw(this->display);
            this->lasers.draw(this->display);
        } while (this->display->nextPage());

        this->ship.step();
        this->lasers.step();
    }else{
        // TODO
        do {
            this->display->drawStr(26, 33, "TODO");
        } while (this->display->nextPage());
    }
}

void GameSpaceInvaders::rotaryEvent(int delta){
    // this->sound->playEnemyDestroyed();
    this->ship.move(delta);
}

void GameSpaceInvaders::pressEvent(){
    // this->lasers.add(this->displayWidth/2, this->displayHeight);

    this->lasers.add(this->ship.getX(), this->ship.getY());
}

void GameSpaceInvaders::longPressEvent(){
    this->sound->playEndMusic();
}
