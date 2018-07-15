#ifndef _VIBRATOR_H
#define _VIBRATOR_H

#include <Arduino.h>

#define PWM_VALUE 128

#define DEBUG_VIBRATOR

#ifdef DEBUG_VIBRATOR
#define DEBUG_VIBRATOR_PRINT(x) Serial.print(x)
#define DEBUG_VIBRATOR_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_VIBRATOR_PRINTLN(x)
#define DEBUG_VIBRATOR_PRINT(x)
#endif

class Vibrator
{
  public:
    Vibrator(int pinVibrator);

    void init();

    void loop(unsigned long);

    void playButtonPressed();
    void playEnemyDestroyed();
    void playEndMusic();

  private:
    int pinVibrator;

    int endGameSequence[1] = {1000};
    int endGameSequenceSize = 1;

    int buttonSequence[1] = {50};
    int buttonSequenceSize = 1;

    int enemyDestroyedSequence[3] = {100, 50, 100};
    int enemyDestroyedSequenceSize = 3;

    int *currentSequence;
    int currentSequenceSize;
    int currentSequenceIndex;
    int currentSequenceItemTimeout;

    bool playing = false;

    void playSequence(int *sequence, int size);
};
#endif
