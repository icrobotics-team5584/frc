
#include "ToggleButton.h"


ToggleButton::ToggleButton(GenericHID* joystick, int axisNumber, bool isAxis) {
	_joystick = joystick;
	_axisNumber = axisNumber;
    _isAxis = isAxis;
}


bool ToggleButton::Get(){
    if(_isAxis){
        if (_joystick->GetRawAxis(_axisNumber) > 0) {
        	return true;
        } else {
        	return false;
        }
    } else{
        if(_joystick->GetRawButton(_axisNumber) == true){
            return true;
        } else{
            return false;
        }
    }
}

void ToggleButton::WhileHeld(Command* command) {
	WhileActive(command);
}

void ToggleButton::WhenPressed(Command* command) {
    if(prevState){
        WhenActive(_cmd2);
        prevState = false;
    } else{
        WhenActive(_cmd1);
        prevState = true;
    }
	
}

float ToggleButton::GetAxis(){
	return _joystick->GetRawAxis(_axisNumber);
}

void ToggleButton::SetCommand(Command* cmd1, Command* cmd2){
    _cmd1 = cmd1;
    _cmd2 = cmd1;
    
}