#ifndef _GAME_SPACEINVADERS_LASER_H
#define _GAME_SPACEINVADERS_LASER_H

#include <U8g2lib.h>

class Lasers {
public:
    enum { LASER_H = 3, MAX_LASERS = 4, INACTIVE_LASER = 0xff };

    Lasers(){
        reset();
    }

    void init(Sound* sound, Vibrator* vibrator){
        this->sound = sound;
        this->vibrator = vibrator;
    }

    void reset() {
        memset(_y, INACTIVE_LASER, MAX_LASERS);
    }

    void add(uint8_t x, uint8_t y) {
        for (int i = 0; i < MAX_LASERS; i++) {
            if (_y[i] == INACTIVE_LASER) {
                _y[i] = y;
                _x[i] = x;
                // this->sound->playButtonPressed();
                this->vibrator->playButtonPressed();
                break;
            }
        }
    }

    void draw(U8G2* display) {
        for (int i = 0; i < MAX_LASERS; i++) {
            uint8_t y = _y[i];
            if (y != INACTIVE_LASER) {
                display->drawVLine(_x[i], _y[i], LASER_H);
            }
        }
    }

    void step(unsigned long dtMs) {
        this->nextMove -= min(dtMs, this->nextMove);
        if(this->nextMove==0){
            this->nextMove = 50;
            for (int i = 0; i < MAX_LASERS; i++) {
                uint8_t y = _y[i];
                if (y != INACTIVE_LASER) {
                    if (y < 2) {
                        y = INACTIVE_LASER;
                    } else {
                        y -= 1;
                    }
                }
                _y[i] = y;
            }
        }
    }

    //publis so monsters can access it
    uint8_t _y[MAX_LASERS];
    uint8_t _x[MAX_LASERS];

private:
    Sound* sound;
    Vibrator* vibrator;
    unsigned long nextMove = 0;

};

#endif
