#include "input.h"

Input::Input(int pinCenter, int pinLeft, int pinRight, int pinTop, int pinBottom, InputListener* listener) {

	// this->lastEncoded = 0;
	// this->encoderValue = 0;
	// this->lastEncoderValue = 0;
	// this->buttonPressed = false;
	// this->lastButtonPressed = false;
	// this->timeButtonDown = 0;
	// this->ignoreNextRelease = false;
	// this->antiReboundMs = 0;
    this->buttons[0].construct(pinCenter, CENTER, listener);
    this->buttons[1].construct(pinRight, RIGHT, listener);
    this->buttons[2].construct(pinLeft, LEFT, listener);
    this->buttons[3].construct(pinTop, TOP, listener);
    this->buttons[4].construct(pinBottom, BOTTOM, listener);
}

void Input::init(){
    for(int i=0; i<5; i++){
        this->buttons[i].init();
    }
}


void Input::loop(unsigned long nowMs, unsigned long dtMs){
    for(int i=0; i<5; i++){
        this->buttons[i].loop(nowMs, dtMs);
    }
	// this->checkButtonLongPress(nowMs, dtMs);
	// this->checkButtonNormalPress(nowMs);
    //
	// if(this->antiReboundMs!=0){
	// 	this->antiReboundMs -= min(dtMs, this->antiReboundMs);
	// }
}
//
// void Input::changeDetected(){
//     this->updateEncoder();
//     this->checkRotation(millis());
// }
//
// void Input::updateEncoder(){
//
//   int MSB = digitalRead(this->pinRotaryA); //MSB = most significant bit
//   int LSB = digitalRead(this->pinRotaryB); //LSB = least significant bit
//
//   int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
//   int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
//
//   if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) this->encoderValue ++;
//   if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) this->encoderValue --;
//
//   this->lastEncoded = encoded; //store this value for next time
// }
//
// void Input::checkButtonLongPress(unsigned long nowMs, unsigned long dtMs){
// 	this->buttonPressed = digitalRead(this->pinButton) == LOW;
//
// 	if(this->buttonPressed && !this->ignoreNextRelease){
// 		this->timeButtonDown += dtMs;
// 		if(this->timeButtonDown>=BUTTON_LONG_PRESS_MS){
// 			this->ignoreNextRelease = true;
// 			DEBUG_INPUT_PRINTLN("Btn long");
//             if(this->listener){
//                 this->listener->longPressEvent(nowMs);
//             }
// 		}
// 	}
// }
//
// void Input::checkButtonNormalPress(unsigned long nowMs){
// 	if(this->lastButtonPressed!=this->buttonPressed){
// 		if(this->buttonPressed){
// 			DEBUG_INPUT_PRINTLN("Btn press");
// 		}else{
//             DEBUG_INPUT_PRINTLN("Btn rel");
// 			if(!this->ignoreNextRelease){
// 				if(this->antiReboundMs==0){
//                     if(this->listener){
//                         this->listener->pressEvent(nowMs);
//                     }
// 					this->antiReboundMs = ANTI_REBOUND_MS;
// 				}else{
// 					DEBUG_INPUT_PRINT("Btn reboud, timeout=");
//                     DEBUG_INPUT_PRINTLN(this->antiReboundMs);
// 				}
// 			}else{
// 				this->ignoreNextRelease = false;
// 			}
// 			this->timeButtonDown = 0;
// 		}
// 		this->lastButtonPressed = this->buttonPressed;
// 	}
// }
//
// void Input::checkRotation(unsigned long nowMs){
// 	//divide by 4 to match tics of the rotary encoder
// 	int lastEnc = this->lastEncoderValue>>2;
// 	int currEnc = this->encoderValue>>2;
//
// 	int delta = currEnc-lastEnc;
// 	if(delta != 0){
// 		if(delta<0){
//             DEBUG_INPUT_PRINTLN("Rot -");
//             if(this->listener){
//                 this->listener->rotaryEvent(-1, nowMs);
//             }
// 		}else{
//           DEBUG_INPUT_PRINTLN("Rot +");
//           if(this->listener){
//               this->listener->rotaryEvent(1, nowMs);
//           }
// 		}
// 		this->lastEncoderValue = this->encoderValue;
// 	}
// }
