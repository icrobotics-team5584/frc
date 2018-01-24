#include "MotionProfileData.h"
#include <iostream>

MotionProfileData::MotionProfileData( ) {
	_sets = 0;
	_points = 0;
}

MotionProfileData::MotionProfileData( const double MP1[][3], const double MP2[][3], const int Points) {
	_sets = 2;
	_points = Points;
	if(  _points > kMaxMotionProfilePoints ) {
		std::cout << "MotionProfileData() WARNING TOO MANY POINTS (" << _points << " is more than " << kMaxMotionProfilePoints << ") TO STORE - TRUNCATING MP\n";
	}

	for (int i = 0; i<_points; ++i) {
		for (int j = 0; j<3; ++j) {
			_MP1[i][j] = MP1[i][j];
			_MP2[i][j] = MP2[i][j];
		}
	}
}

MotionProfileData::MotionProfileData( const double MP1[][3], const int Points) {
	_sets = 1;
	_points = Points;

	if(  _points > kMaxMotionProfilePoints ) {
		std::cout << "MotionProfileData() WARNING TOO MANY POINTS (" << _points << " is more than " << kMaxMotionProfilePoints << ") TO STORE - TRUNCATING MP\n";
	}

	Point point;
	for (int i = 0; i<_points; ++i) {
		point.position = MP1[i][0];
		point.velocity = MP1[i][1];
		point.duration = MP1[i][2];
		profile.push_back(point);
	}

}

void MotionProfileData::ReadCSV(std::string fileName) {
	io::CSVReader<3> in("/home/admin/" + fileName);
	Point point;


	while(in.read_row(point.position, point.velocity, point.duration)){
		std::cout << point.position << ", " << point.velocity << ", " << point.duration << std::endl;
		this->profile.push_back(point);
	}
}

void MotionProfileData::PrintProfile() {
	for( unsigned int i = 0; i < this->profile.size(); i++ ) {
		std::cout << "Row " << i << std::endl;
		std::cout << this->profile.at(i).position << ", " << this->profile.at(i).velocity << ", " << this->profile.at(i).duration << std::endl;
	}
}




int MotionProfileData::GetNumberOfPoints() {
	return _points;
}

double MotionProfileData::GetPosition( int set, int number ) {
	switch (set) {
		case 1:
			return _MP1[number][0];
		case 2:
			return _MP2[number][0];
		default:
			return 0.0;
	}
}

double MotionProfileData::GetVelocity( int set, int number ) {
	switch (set) {
		case 1:
			return _MP1[number][1];
		case 2:
			return _MP2[number][1];
		default:
			return 0.0;
	}
}

double MotionProfileData::GetDuration( int set, int number ) {
	switch (set) {
		case 1:
			return _MP1[number][2];
		case 2:
			return _MP2[number][2];
		default:
			return 0.0;
	}
}
