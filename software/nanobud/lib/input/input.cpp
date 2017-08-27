#include "input.h"

Input::Input(int pinButton, int pinRotaryA, int pinRotaryB, InputListener* listener)
 : pinButton(pinButton), pinRotaryA(pinRotaryA), pinRotaryB(pinRotaryB), listener(listener) {
	this->lastEncoded = 0;
	this->encoderValue = 0;
	this->lastEncoderValue = 0;
	this->buttonPressed = false;
	this->lastButtonPressed = false;
	this->timeButtonDown = 0;
	this->ignoreNextRelease = false;
	this->antiReboundMs = 0;
}

void Input::init(){
	pinMode(this->pinRotaryA, INPUT);
	pinMode(this->pinRotaryB, INPUT);
	pinMode(this->pinButton, INPUT);

	digitalWrite(this->pinRotaryA, HIGH); //turn pullup resistor on
	digitalWrite(this->pinRotaryB, HIGH); //turn pullup resistor on
	digitalWrite(this->pinButton, HIGH); //turn pullup resistor on
}


void Input::loop(unsigned long dtMs){
	this->updateEncoder();
	this->checkRotation();
	this->checkButtonLongPress(dtMs);
	this->checkButtonNormalPress();
	if(this->antiReboundMs!=0){
		this->antiReboundMs-=dtMs;
		if(antiReboundMs<0){
			this->antiReboundMs = 0;
		}
	}
}

void Input::updateEncoder(){

  int MSB = digitalRead(this->pinRotaryA); //MSB = most significant bit
  int LSB = digitalRead(this->pinRotaryB); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) this->encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) this->encoderValue --;

  this->lastEncoded = encoded; //store this value for next time
}

void Input::checkButtonLongPress(unsigned long dtMs){
	this->buttonPressed = digitalRead(this->pinButton) == LOW;

	if(this->buttonPressed && !this->ignoreNextRelease){
		this->timeButtonDown += dtMs;
		if(this->timeButtonDown>=BUTTON_LONG_PRESS_MS){
			this->ignoreNextRelease = true;
			DEBUG_INPUT_PRINT("Btn long");
            if(this->listener){
                this->listener->longPressEvent();
            }
		}
	}
}

void Input::checkButtonNormalPress(){
	if(this->lastButtonPressed!=this->buttonPressed){
		if(this->buttonPressed){
			DEBUG_INPUT_PRINT("Btn press");
		}else{
            DEBUG_INPUT_PRINT("Btn rel");
			if(!this->ignoreNextRelease){
				if(antiReboundMs==0){
                    if(this->listener){
                        this->listener->pressEvent();
                    }
					this->antiReboundMs = ANTI_REBOUND_MS;
				}else{
					DEBUG_INPUT_PRINT("Btn reboud");
				}
			}else{
				this->ignoreNextRelease = false;
			}
			this->timeButtonDown = 0;
		}
		this->lastButtonPressed = this->buttonPressed;
	}
}

void Input::checkRotation(){
	//divide by 4 to match tics of the rotary encoder
	int lastEnc = this->lastEncoderValue>>2;
	int currEnc = this->encoderValue>>2;

	int delta = currEnc-lastEnc;
	if(delta != 0){
		if(delta<0){
            DEBUG_INPUT_PRINT("Rot +");
            if(this->listener){
                this->listener->rotaryEvent(1);
            }
		}else{
          DEBUG_INPUT_PRINT("Rot -");
          if(this->listener){
              this->listener->rotaryEvent(-1);
          }
		}
		this->lastEncoderValue = this->encoderValue;
	}
}
