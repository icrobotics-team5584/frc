/*
 *  ButtonPOV.cpp
 *
 *  Created: 20190102
 *  Author: Darcy Meago
 */

#include <ButtonPOV.h>

ButtonPOV::ButtonPOV(GenericHID* joystick, int position) {
	_joystick = joystick;
	_position = position;
}

bool ButtonPOV::Get(){

    if((_position - _extraZone) < 0){
        
        _lower = _position + _extraZone;
        _upper = 360 - (abs(_position - _extraZone));

    }else{

        _upper = _position + _extraZone;
        _lower = _position - _extraZone; 
        if ((_joystick->GetPOV() > _lower) && (_joystick->GetPOV() < _upper )) {
		    return true;
	    } else {
		    return false;
	    }

    }
}

void ButtonPOV::WhileHeld(Command* command) {
	WhileActive(command);
}

