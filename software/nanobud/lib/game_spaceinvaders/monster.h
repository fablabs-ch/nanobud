#ifndef _GAME_SPACEINVADERS_MONSTERS_H
#define _GAME_SPACEINVADERS_MONSTERS_H

#include <sound.h>
#include <inputlistener.h>
#include <U8glib.h>

static const uint16_t monsters[] U8G_PROGMEM = {0x0600,0x0F00,0x1F80,0x36C0,0x3FC0,0x0900,0x1680,0x2940,0x0600,0x0F00,0x1F80,0x36C0,0x3FC0,0x0900,0x1080,0x0900,0x2080,0x9120,0xBFA0,0xEEE0,0x7FC0,0x3F80,0x2080,0x4040,0x2080,0x1100,0x3F80,0x6EC0,0xFFE0,0xBFA0,0xA0A0,0x1B00,0x0E00,0x7FC0,0xFFE0,0xCE60,0xFFE0,0x3F80,0x6EC0,0xC060,0x0E00,0x7FC0,0xFFE0,0xCE60,0xFFE0,0x3F80,0x6EC0,0x3180};

class Monsters {
public:
    enum { SPEED = 300 };
    enum { BLANK_IDX = 6 };
    enum { MAX_COLS = 8, MAX_ROWS = 4, MON_WIDTH = 16, MON_HEIGHT = 8, MON_HMARGIN = 1 };

    Monsters(const int x, const int y, const int width, const int height, const uint8_t *levelData) {
        _x = x;
        _y = y;
        _left = 0;
        _right = width * MON_WIDTH;
        _bottom = height * (MON_HEIGHT + MON_HMARGIN);
        _dx = 1;
        _width = width;
        _height = height;
        _currSprite = 0;
        _lastUpdate = millis();
        memcpy(_levelData, levelData, MAX_COLS * MAX_ROWS);
    }

    void step(unsigned long nowMs) {
        if (nowMs - _lastUpdate >= SPEED) {
          _lastUpdate = nowMs;
          _currSprite ^= 1;
          _x += _dx;
          if (_x + _left < 0) {
            _x = -_left;
            _dx = -_dx;
            _y++;
          }
          if (_x + _right >= screenW) {
            _x = screenW - _right - 1;
            _dx = -_dx;
            _y++;
          }
        }
        if (_y + _bottom >= PlayerShip::SHIP_Y) {
          //_y = 0;
          g_gameState = GAME_OVER;
        }
    }
    void draw(U8GLIB* display) {
        for (int i = 0; i < _height; i++) {
          for (int j = 0; j < _width; j++) {
            const int idx = _levelData[j + i * MAX_COLS] + _currSprite;
            if (idx < BLANK_IDX) {
              display.drawXBMP(_x + j * MON_WIDTH, _y + i * (MON_HEIGHT + MON_HMARGIN), MON_WIDTH, MON_HEIGHT, (unsigned char*) (monsters + idx * MON_WIDTH / 2));
            }
          }
        }
    }

    void hitTest() {
        bool hit = false;
        for (int i = 0; i < Lasers::MAX_LASERS; i++) {
          // quick fallbacks
          uint8_t y = lasers._y[i];
          if ((y == Lasers::INACTIVE_LASER) || (y + Lasers::LASER_H < _y) || (y >= _y + _bottom))
            continue;

          uint8_t x = lasers._x[i];
          if ((x < _x + _left) || (x >= _x + _right))
            continue;

          if (((x - _x) & 0xf) > 12) // hack
            continue;

          int col = (x - _x) / (MON_WIDTH); //& 0xf; // hack mod(ship width)
          int row = (y - _y) / (MON_HEIGHT + MON_HMARGIN);

          if (_levelData[col + row * MAX_COLS] >= BLANK_IDX)
            continue;

          _levelData[col + row * MAX_COLS] = BLANK_IDX;
          lasers._y[i] = 0xff;
          hit = true;
          tone(BUZZER_PIN,523,50);
        }

        if (!hit) {
          return;
        }

        int c0 = _width - 1, c1 = 0;
        int r1 = 0;

        for (int i = 0; i < _height; i++) {
          for (int j = 0; j < _width; j++) {
            if (_levelData[j + i * MAX_COLS] < BLANK_IDX) {
              c0 = min(c0, j);
              c1 = max(c1, j);
              r1 = max(r1, i);
            }
          }
        }
        if (c0 > c1) {
          g_gameState = GAME_WIN;
          return;
        }
        _left = c0 * MON_WIDTH;
        _right = (c1 + 1) * MON_WIDTH;
        _bottom = (r1 + 1) * (MON_HEIGHT + MON_HMARGIN);
    }

    unsigned long _lastUpdate;
    uint8_t _levelData[MAX_COLS * MAX_ROWS];
    int _width;
    int _height;
    int _x;
    int _y;
    int _left;
    int _right;
    int _bottom;
    int _dx;
    uint8_t _currSprite;
};

#endif