#include "game_spaceinvaders.h"

GameSpaceInvaders::GameSpaceInvaders(U8GLIB* display, Sound* sound)
 : display(display), sound(sound){

}

void GameSpaceInvaders::init(){
    this->displayWidth = this->display->getWidth();
    this->displayHeight = this->display->getHeight();

    this->display->firstPage();
    do {
        this->display->drawXBMP(0, 0, this->displayWidth, this->displayHeight, (const uint8_t*) splash);
    } while (this->display->nextPage());
}
void GameSpaceInvaders::loop(unsigned long){

}

void GameSpaceInvaders::rotaryEvent(int delta){
    this->sound->playEnemyDestroyed();
}

void GameSpaceInvaders::pressEvent(){
    this->sound->playButtonPressed();

}

void GameSpaceInvaders::longPressEvent(){
    this->sound->playEndMusic();
}
