#include "sound.h"


Sound::Sound(int pinBuzzer) : pinBuzzer(pinBuzzer){
}

void Sound::init(){
	pinMode(this->pinBuzzer, OUTPUT);
}

void Sound::loop(unsigned long dtMs){
    if(this->playing){
        if(this->currentNoteDuration>=this->nextNote){
			DEBUG_SOUND_PRINT("End of note index=");
			DEBUG_SOUND_PRINTLN(this->currentMelodyIndex);
			this->currentMelodyIndex++;
			this->nextNote = this->currentMelodyNotesDuration[this->currentMelodyIndex]*NOTE_DURATION_TO_MS;
			this->currentNoteDuration = 0;

            if(this->currentMelodyIndex>=this->currentMelodySize){
				DEBUG_SOUND_PRINTLN("End of melody");
                this->playing = false;
                noTone(this->pinBuzzer);
            }else{
                //play next tone
                tone(this->pinBuzzer, this->currentMelodyNotes[this->currentMelodyIndex]);
            }
        }
	    this->currentNoteDuration += dtMs;
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
    this->currentMelodyNotes = melody;
	this->currentMelodyNotesDuration = duration;
    this->currentMelodySize = size;
	this->currentNoteDuration = 0;
    this->currentMelodyIndex = 0;
    this->playing = true;

	//play first note
	tone(this->pinBuzzer, this->currentMelodyNotes[this->currentMelodyIndex]);
	this->nextNote = this->currentMelodyNotesDuration[this->currentMelodyIndex]*NOTE_DURATION_TO_MS;

		DEBUG_SOUND_PRINT("Start playing melody, size=");
		DEBUG_SOUND_PRINT(size);
		DEBUG_SOUND_PRINT(" first duration=");
		DEBUG_SOUND_PRINT(this->nextNote);
		DEBUG_SOUND_PRINTLN();

}
