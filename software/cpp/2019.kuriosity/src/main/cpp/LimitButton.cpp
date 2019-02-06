#include <LimitButton.h>

LimitButton::LimitButton(DigitalInput* limitSwitch, bool invert) {
	limitSwitch = _limitSwitch;
    invert = _invert;
}

bool LimitButton::Get(){
	
    if(_invert){
        return not(_limitSwitch->Get());    
    }else{
        return _limitSwitch->Get();
    }
    
}

void LimitButton::WhileHeld(Command* command) {
	WhileActive(command);
}

void LimitButton::WhenPressed(Command* command){
    WhenActive(command);
}


