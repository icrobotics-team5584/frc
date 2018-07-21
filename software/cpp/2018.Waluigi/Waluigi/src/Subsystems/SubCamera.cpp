/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SubCamera.h"
#include "../RobotMap.h"
#include <CameraServer.h>

SubCamera::SubCamera() : Subsystem("SubCamera") {

	camera = CameraServer::GetInstance()->StartAutomaticCapture(0);
	camera.SetResolution(320, 240);
	camera.SetFPS(10);

	server = CameraServer::GetInstance()->GetServer();
}

void SubCamera::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void SubCamera::flipImage() {

}
