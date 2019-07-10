
#include "ToggleButton.h"


ToggleButton::ToggleButton(GenericHID* joystick, int axisNumber, bool isAxis) {
    std::cout << "Toggle Init" << std::endl;
	_joystick = joystick;
	_axisNumber = axisNumber;
    _isAxis = isAxis;
}


bool ToggleButton::Get(){
   //if(_isAxis){
   //    if (_joystick->GetRawAxis(_axisNumber) > 0) {
   //    	return true;
   //    } else {
   //    	return false;
   //    }
   //} else{
        if((_joystick->GetRawButton(_axisNumber)) == true){
            std::cout << "toggle button pressed" << std::endl;
            return true;
        } else{
            return false;
        }
    //}
}

void ToggleButton::WhileHeld(Command* command) {
	WhileActive(command);
}

void ToggleButton::WhenPressed() { //change this add a thing in the get function to update the whenactive 
  //  std::cout << "When Pressed" << std::endl;
  //  std::cout << prevState  << "prevstate before" << std::endl;
  //  if(prevState){
  //      std::cout << "Toggle 2" << std::endl;
  //      WhenActive(_cmd2);
  //      prevState = false;
  //  } else{
  //      std::cout << "Toggle 1" << std::endl;
  //      WhenActive(_cmd1);
  //      std::cout << "after whenactive" << std::endl;
  //      prevState = true;
  //  }
  //  std::cout << prevState << "prevstate after" << std::endl;
	
}

float ToggleButton::GetAxis(){
	return _joystick->GetRawAxis(_axisNumber);
}

void ToggleButton::SetCommand(Command* cmd1, Command* cmd2){
    std::cout << "Toggle set command" << std::endl;
    _cmd1 = cmd1;
    _cmd2 = cmd2;
    switchButtonSceduler.reset(new SwitchButtonSceduler(Get(), this, _cmd1, _cmd2));
    switchButtonSceduler->Start();
}