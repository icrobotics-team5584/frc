#include "MotionProfileData.h"
#include <iostream>

MotionProfileData::MotionProfileData( ) {

}

void MotionProfileData::ReadCSV(int set, std::string fileName) {
	std::cout << "Running MotionProfileData::ReadCSV(...)" << std::endl;
	std::cout << "Reading .csv from: /home/admin/" << fileName << std::endl;
	io::CSVReader<3> in("/home/admin/" + fileName);

	//I THINK I NEED TO PUSH A NEW VECTOR OF TPs TO SETS BEFORE PUSHING POINTS TO SETS[SET]
	sets.push_back(new std::vector<TrajectoryPoint>);

	std::cout << "Create Trajectory Point" << std::endl;
	TrajectoryPoint point;

	double duration;
	while(in.read_row(point.position, point.velocity, duration)){
		point.zeroPos = false;
		point.isLastPoint = false;
		std::cout << "Converting duration: " << duration << std::endl;
		point.timeDur = ConvertDuration(duration);
		std::cout << "Pushing point to vector" << std::endl;
		sets[set].push_back(point);
		std::cout << "point: " << point.position << ", " << point.velocity << ", " << duration << std::endl;
	}

	std::cout << "setting zero and last point in  MP vector" << std::endl;
	sets[set][0].zeroPos = true;
	sets[set].back().isLastPoint = true;
}

int MotionProfileData::GetNumberOfPoints() {
	int size = (int)sets[0].size();
	for (unsigned int i = 0; i<sets.size(); i++){
		if ((int)sets[i].size() != size){
			throw "Motion Profiles are not the same size";
		}
	}
	return size;
}

double MotionProfileData::GetPosition( int set, int number ) {
	return sets[set][number].position;
}

double MotionProfileData::GetVelocity( int set, int number ) {
	return sets[set][number].velocity;
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
