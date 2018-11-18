#ifndef _GAME_SPACEINVADERS_H
#define _GAME_SPACEINVADERS_H

#include <Arduino.h>
#include <sound.h>
#include <vibrator.h>
#include <game.h>
#include <U8g2lib.h>

static const uint32_t splash_space_invader [] U8X8_PROGMEM = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7936,0,0,0,536362880,520095680,127,25171968,0x7FF8FFE0,0x3FC007C0,127,25171968,0x7FF87FE0,0x3FE00FE0,127,6316032,0xF8F871F0,0x3FF00FE0,7,6316032,0xF8F831F0,838344672,7,33552384,0xF0F811F0,7872480,7,33552384,0xF0F801F0,3677936,7,0x79F9E00,0xF0F807F0,3940080,119,0x79F9E00,0xF8F81FF0,3947640,127,536870784,0xFCF83FF0,3947640,127,536870784,0x7FF8FFE0,3947640,127,436205952,0x7FF9FF80,3963000,7,436205952,536475648,7895164,7,427825536,0xF9F000,821592060,7,427825536,0xF9F000,0x3FF87FFC,7,7987200,0xF9F000,0x3FF0FFFC,127,7987200,0xF9F1E0,0x3FE0F03E,127,0,0xF8F9F0,0x3FC0F03E,127,0,0xF8FFF0,520220734,1,0,0xF87FF0,4159,3145728,0,0xF03FC0,0,8128496,0,384,0xF8080000,8265715,0,0,0xFC2FF004,8265715,0,0xC1F00000,0xF83FF00F,2571507,0,0xC0F007CC,947908623,474224,0x801E0000,0xC0F807CF,947712031,473200,0x801F07C0,0xE0FC0F8F,955281439,2047088,0x807F0FC0,0xE0FC1F8F,955314239,8339056,0x80FF0FC0,0xE0781F8F,0xB9E0F03F,0xFE1FF3,0x81FF0FC0,0xF07C1F0F,0xF9E0F03D,0xFC0FF3,0x81FF0FC0,0xF07E3F0F,0xF9E0F03D,0xE00FF3,0x81FF0FC0,0xF03E3F0F,0xF9E0F078,0xE007F3,0x7FF0FC0,0xF83E3E0F,971042936,0xE20F70,0xFFF0FC0,0xF83E3E0F,954265720,0xF60F70,536809408,0x781F7E1F,955314416,8330864,0x3F9F0FC0,0x7C1F7C1F,955314416,4136048,0x3F9F0FC0,0xFC1FF81F,0xF878F0FF,3947635,0x3F1F0FC0,0xFC0FF81F,0xF87CF1FF,14451,0xFE1F0FC0,0xFC0FF01F,0xF83FF1FF,51,0xFC1F0FC0,0xFE0FF01F,941617632,0,0xF81F0FC0,0x3E0FF01F,0xFF1E0,0,0xF01F0FC0,0x3E07F01F,5088,0,0xF01F0FC0,0x3E07E01F,0,0,0xE03F0FC0,520347679,0,0,0xC03F0FC0,245791,16777216,524288,0x803F0FC0,31,16777216,786432,4132800,15,41943040,524288,4132800,0,0x82866000,25889906,462784,0,0xC4444000,38572617,1984,0,0x87C44000,63478792,0,0,0x88244000,4755976,0,0,0x882E4000,39621192,0,0,0xDC758000,25902129,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint8_t level_0[] = { 0, 0, 0, 0, 0, 0, 0xff, 0xff,
                            2, 2, 2, 2, 2, 2, 0xff, 0xff,
                            4, 4, 4, 4, 4, 4, 0xff, 0xff,
                            4, 4, 4, 4, 4, 4, 0xff, 0xff};

// #define DEBUG_GAME

#ifdef DEBUG_GAME
    #define DEBUG_GAME_PRINT(x)  Serial.print (x)
    #define DEBUG_GAME_PRINTLN(x)  Serial.println (x)
#else
    #define DEBUG_GAME_PRINT(x)
    #define DEBUG_GAME_PRINTLN(x)
#endif

#include "lasers.h"
#include "ship.h"
#include "monters.h"

enum class GameSpaceInvadersState { GAME_INIT, GAME_SHOW_LEVEL, GAME_NORMAL, GAME_WIN, GAME_OVER };

class GameSpaceInvaders : public Game {
public:
    GameSpaceInvaders(U8G2* display, Sound* sound, Vibrator* vibrator);

    void init();
    void loop(unsigned long nowMs, unsigned long dtMs);


    void repeatPressEvent(Button button, unsigned long nowMs);

    void pressEvent(Button button, unsigned long nowMs);

private:
    U8G2* display;
    Sound* sound;
    Vibrator* vibrator;

    Lasers lasers;
    PlayerShip ship;
    Monsters monsters;

    int displayWidth;
    int displayHeight;

    int level = 1;

    unsigned long gameStateLastChange;
    enum GameSpaceInvadersState gameState = GameSpaceInvadersState::GAME_INIT;

    void setGameState(enum GameSpaceInvadersState gameState, unsigned long nowMS);
    void displayRestart();
    void displayLevel();

    void fire();
    void move(int delta);

};
#endif
