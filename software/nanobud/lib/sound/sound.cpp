#include "sound.h"


Sound::Sound(int pinBuzzer) : pinBuzzer(pinBuzzer){
}

void Sound::init(){
	pinMode(this->pinBuzzer, OUTPUT);
}

void Sound::loop(unsigned long dtMs){
    if(this->playing){
        this->currentNoteDuration += dtMs;
        if(this->currentNoteDuration>=this->nextNote){
			DEBUG_SOUND_PRINTLN("End of note");
			this->currentMelodyIndex++;
			this->nextNote = this->currentMelodyNotesDuration[this->currentMelodyIndex]*NOTE_DURATION_TO_MS;
			this->currentNoteDuration = 0;

			DEBUG_SOUND_PRINT("index=");
			DEBUG_SOUND_PRINTLN(this->currentMelodyIndex);
            if(this->currentMelodyIndex>=this->currentMelodySize){
				DEBUG_SOUND_PRINTLN("End of melody");
                this->playing = false;
                noTone(this->pinBuzzer);
            }else{
                //play next tone
                tone(this->pinBuzzer, this->currentMelodyNotes[this->currentMelodyIndex]);
            }
        }
    }
}

void Sound::playButtonPressed(){
	this->playMelody(this->buttonMelodyNotes, this->buttonMelodyNotesDurations, this->buttonMelodySize);
}

void Sound::playEnemyDestroyed(){
	this->playMelody(this->enemyDestroyedMelodyNotes, this->enemyDestroyedMelodyNotesDurations, this->enemyDestroyedMelodySize);
}

void Sound::playEndMusic(){
	this->playMelody(this->endGameMelodyNotes, this->endGameMelodyNotesDurations, this->endGameMelodySize);
}

void Sound::playMelody(int* melody, int* duration, int size){
	DEBUG_SOUND_PRINT("Start playing melody, size=");
	DEBUG_SOUND_PRINTLN(size);
    this->currentMelodyNotes = melody;
	this->currentMelodyNotesDuration = duration;
    this->currentMelodySize = size;
	this->currentNoteDuration = 0;
    this->currentMelodyIndex = 0;
    this->playing = true;

	//play first note
	tone(this->pinBuzzer, this->currentMelodyNotes[this->currentMelodyIndex]);
	this->nextNote = this->currentMelodyNotesDuration[this->currentMelodyIndex]*NOTE_DURATION_TO_MS;
}
