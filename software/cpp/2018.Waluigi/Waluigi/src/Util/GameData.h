#pragma once

#include <WPILib.h>
#include <string>

/*
 * The GameData class reads in the state of the switches and scale at the beginning of
 * the match. It can then return individual elements of the FMS game data string using
 * the GetSwitch() and GetScale() commands. We ignore the switch on the opponent's side
 * of the field because we are not allowed over there in autonomous.
 */

class GameData {

private:
	std::string strGameData;

public:

	enum Target {targetLeft, targetRight};

	GameData();
	void UpdateGameData();
	Target GetSwitch();
	Target GetScale();


};
