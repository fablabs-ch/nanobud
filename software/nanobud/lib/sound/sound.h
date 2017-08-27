#ifndef _SOUND_H
#define _SOUND_H

#include <Arduino.h>
#include "pitches.h"

#define NOTE_DURATION_TO_MS 50

#define END_GAME_MELODY NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
#define END_GAME_NOTE_DURATION 4, 8, 8, 4, 4, 4, 4, 4
#define END_GAME_MELODY_SIZE 8

#define BUTTON_MELODY NOTE_C3
#define BUTTON_NOTE_DURATION 2
#define BUTTON_MELODY_SIZE 1

#define ENEMY_DESTROYED_MELODY NOTE_C5
#define ENEMY_DESTROYED_NOTE_DURATION 4
#define ENEMY_DESTROYED_MELODY_SIZE 1

// #define DEBUG_SOUND

#ifdef DEBUG_SOUND
    #define DEBUG_SOUND_PRINT(x)  Serial.print (x)
    #define DEBUG_SOUND_PRINTLN(x)  Serial.println (x)
#else
    #define DEBUG_SOUND_PRINTLN(x)
    #define DEBUG_SOUND_PRINT(x)
#endif


class Sound {
public:
    Sound(int pinBuzzer);

    void init();

    void loop(unsigned long);

    void playButtonPressed();
    void playEnemyDestroyed();
    void playEndMusic();

private:
    int pinBuzzer;

    int endGameMelodyNotes[END_GAME_MELODY_SIZE] = { END_GAME_MELODY };
    int endGameMelodyNotesDurations[END_GAME_MELODY_SIZE] = { END_GAME_NOTE_DURATION };
    int endGameMelodySize = END_GAME_MELODY_SIZE;

    int buttonMelodyNotes[BUTTON_MELODY_SIZE] = { BUTTON_MELODY };
    int buttonMelodyNotesDurations[BUTTON_MELODY] = { BUTTON_NOTE_DURATION };
    int buttonMelodySize = BUTTON_MELODY_SIZE;

    int enemyDestroyedMelodyNotes[ENEMY_DESTROYED_MELODY_SIZE] = { ENEMY_DESTROYED_MELODY };
    int enemyDestroyedMelodyNotesDurations[ENEMY_DESTROYED_MELODY_SIZE] = { ENEMY_DESTROYED_NOTE_DURATION };
    int enemyDestroyedMelodySize = ENEMY_DESTROYED_MELODY_SIZE;

    int* currentMelodyNotes;
    int* currentMelodyNotesDuration;
    int currentMelodySize;
    int currentMelodyIndex;
    int currentNoteDuration;
    int nextNote;

    bool playing = false;

    void playMelody(int* melody, int* duration, int size);


};
#endif
