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
	std::string gameData;

public:
	GameData(){
		//Take in gameData from FMS
		gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
	}

	std::string GetSwitch(){
		//Return alliance switch position
		if (gameData[0] == 'L')
			return "Left";
		else
			return "Right";
	}

	std::string GetScale(){
		//Return alliance scale position
		if (gameData[1] == 'L')
			return "Left";
		else
			return "Right";
	}
};
