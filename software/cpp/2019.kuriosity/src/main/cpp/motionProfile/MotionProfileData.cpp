#include "motionProfile/MotionProfileData.h"
#include <iostream>

MotionProfileData::MotionProfileData( ) {
	sets.resize(2);
	mpSize = 0;
}

void MotionProfileData::ReadMotionProfile(std::string MP) {
	//Read in two csv files, one for each side of the robot
	ReadCSV(0, MP + "/" + MP + "_left.csv");
	ReadCSV(1, MP + "/" + MP + "_right.csv");
}

void MotionProfileData::ReadCSV(int set, std::string fileName) {
	//Read in a csv of trajectory points into a vector
	std::cout << "MotionProfileData: reading from: /home/admin/" << fileName << std::endl;
	io::CSVReader<3> in("/home/admin/" + fileName);

	TrajectoryPoint point;

	mpSize = 0;

	if( ! sets[set].empty() ) {
		std::cout << "MotionProfileData: detected content - clearing buffer set: " << set << std::endl;
		sets[set].clear();
	}

	double duration;
	while(in.read_row(point.position, point.velocity, duration)){
		mpSize++;
		point.zeroPos = false;
		point.isLastPoint = false;
		point.timeDur = ConvertDuration(duration);
		sets[set].push_back(point);
	}

	sets[set][0].zeroPos = true;
	sets[set].back().isLastPoint = true;

}

void MotionProfileData::ReadMotionProfile(Segment *path, int length, double wheelBaseWidth) {
	Segment *leftTrajectory = new Segment[length];
	Segment *rightTrajectory = new Segment[length];
	pathfinder_modify_tank(path, length, leftTrajectory, rightTrajectory, wheelBaseWidth);

	ReadSegment(0, leftTrajectory, length);
	ReadSegment(1, rightTrajectory, length);
	delete leftTrajectory;
	delete rightTrajectory;
}

void MotionProfileData::ReadSegment(int set, Segment *path, int length) {

	// Clear set if it already contains a profile
	if (!sets[set].empty()) {
		std::cout << "MotionProfileData: detected content - clearing buffer set: " << set << std::endl;
		sets[set].clear();
	}

	// Load Segment into vector of Trajectory Points
	TrajectoryPoint point;
	for (int pointIndex = 0; pointIndex < length; pointIndex++) {
		Segment segment = path[pointIndex];

		point.position = segment.position;
		point.velocity = segment.velocity;
		point.timeDur = ConvertDuration(segment.dt);
		point.zeroPos = false;
		point.isLastPoint = false;

		sets[set].push_back(point);
	}

	// Set final and intial points 
	sets[set][0].zeroPos = true;
	sets[set].back().isLastPoint = true;
}

int MotionProfileData::GetNumberOfPoints() {
	return (int)sets[0].size();
}

double MotionProfileData::GetPosition( int set, int number ) {
	switch (set){
	case 0:
		return sets[set][number].position;
	case 1:
		return -sets[set][number].position;
	default:
		return sets[set][number].position;
	}

}

double MotionProfileData::GetVelocity( int set, int number ) {
	switch (set){
	case 0:
		return sets[set][number].velocity;
	case 1:
		return -sets[set][number].velocity;
	default:
		return sets[set][number].velocity;
	}
}

//double MotionProfileData::GetDuration( int set, int number ) {
//	return sets[set][number][2];
//}

TrajectoryPoint MotionProfileData::GetPoint( int set, int number ) {
	return sets[set][number];
}


TrajectoryDuration MotionProfileData::ConvertDuration(double dur){
	if (dur < 2.5) {
		return TrajectoryDuration_0ms;
	} else if (dur < 7.5) {
		return TrajectoryDuration_5ms;
	} else if (dur < 15) {
		return TrajectoryDuration_10ms;
	}else if (dur < 25) {
		return TrajectoryDuration_20ms;
	}else if (dur < 35) {
		return TrajectoryDuration_30ms;
	}else if (dur < 45) {
		return TrajectoryDuration_40ms;
	}else if (dur < 55) {
		return TrajectoryDuration_50ms;
	}else {
		return TrajectoryDuration_100ms;
	}
}
