#ifndef _GAME_SPACEINVADERS_LASER_H
#define _GAME_SPACEINVADERS_LASER_H

#include <U8glib.h>

class Lasers {
public:
  enum { LASER_H = 3, MAX_LASERS = 4, INACTIVE_LASER = 0xff };

  Lasers() { reset(); }

  void reset() {
    memset(_y, INACTIVE_LASER, MAX_LASERS);
    //_lastStep = millis();
  }

  void add(uint8_t x, uint8_t y) {
    for (int i = 0; i < MAX_LASERS; i++) {
      if (_y[i] == INACTIVE_LASER) {
        _y[i] = y;
        _x[i] = x;
        break;
      }
    }
  }

  void draw(U8GLIB* display) {
    for (int i = 0; i < MAX_LASERS; i++) {
      uint8_t y = _y[i];
      if (y != INACTIVE_LASER) {
        display.drawVLine(_x[i], _y[i], LASER_H);
      }
    }
  }

  void step() {
//    if (millis() - _lastStep < 50)
//      return;
//
//    _lastStep = millis();

    for (int i = 0; i < MAX_LASERS; i++) {
      uint8_t y = _y[i];
      if (y != INACTIVE_LASER) {
        if (y < 2) {
          y = INACTIVE_LASER;
        } else {
          y -= 2;
        }
      }
      _y[i] = y;
    }
  }

  uint8_t _y[MAX_LASERS];
  uint8_t _x[MAX_LASERS];
//  unsigned long _lastStep;
};

#endif
