#include "vibrator.h"

Vibrator::Vibrator(int pinVibrator) : pinVibrator(pinVibrator)
{
}

void Vibrator::init()
{
    pinMode(this->pinVibrator, OUTPUT);
}

void Vibrator::loop(unsigned long dtMs)
{
    if (this->playing)
    {
        if (this->currentSequenceItemTimeout <= 0)
        {
            DEBUG_VIBRATOR_PRINT("End of item index=");
            DEBUG_VIBRATOR_PRINTLN(this->currentSequenceIndex);
            this->currentSequenceIndex++;

            if (this->currentSequenceIndex < this->currentSequenceSize)
            {
                this->currentSequenceItemTimeout = this->currentSequence[this->currentSequenceIndex];
                analogWrite(this->pinVibrator, this->currentSequenceIndex % 2 == 0 ? PWM_VALUE : LOW);
            }
            else
            {
                // always shut off vibrator at the end
                analogWrite(this->pinVibrator, LOW);
                this->playing = false;
            }
        }
        this->currentSequenceItemTimeout -= dtMs;
    }
}

void Vibrator::playButtonPressed()
{
    this->playSequence(this->buttonSequence, this->buttonSequenceSize);
}

void Vibrator::playEnemyDestroyed()
{
    this->playSequence(this->enemyDestroyedSequence, this->enemyDestroyedSequenceSize);
}

void Vibrator::playEndMusic()
{
    this->playSequence(this->enemyDestroyedSequence, this->enemyDestroyedSequenceSize);
}

void Vibrator::playSequence(int *sequence, int size)
{
    this->currentSequence = sequence;
    this->currentSequenceSize = size;
    this->currentSequenceIndex = 0;
    this->playing = true;
    this->currentSequenceItemTimeout = sequence[0];

    // start vibrator right away
    analogWrite(this->pinVibrator, PWM_VALUE);

    DEBUG_VIBRATOR_PRINT("Start playing vibrator, size=");
    DEBUG_VIBRATOR_PRINT(size);
    DEBUG_VIBRATOR_PRINTLN();
}
