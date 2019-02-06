#include <LimitButton.h>
#include <iostream>

LimitButton::LimitButton(shared_ptr<DigitalInput> limitSwitch, bool invert) {
	_limitSwitch = limitSwitch;
    _invert = invert;
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
    cout << "LIMITBUTTON GET" << endl;
    WhenActive(command);
}


