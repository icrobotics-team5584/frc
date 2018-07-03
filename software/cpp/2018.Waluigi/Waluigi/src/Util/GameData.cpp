#include "GameData.h"
#include <iostream>


GameData::GameData() {
	//Take in gameData from FMS
	UpdateGameData();
}


void GameData::UpdateGameData() {
	//Take in gameData from FMS at will
	strGameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
	std::cout << "Updated Game Data: " << std::endl;
	std::cout << "	Switch=" << strGameData[0] << std::endl;
	std::cout << "	Scale=" << strGameData[1] << std::endl;
}


GameData::Target GameData::GetSwitch(){
	//Return alliance switch position
	if (strGameData[0] == 'L')
		return targetLeft;
	else
		return targetRight;
}


GameData::Target GameData::GetScale() {
	//Return alliance scale position
	if (strGameData[1] == 'L')
		return targetLeft;
	else
		return targetRight;
}
