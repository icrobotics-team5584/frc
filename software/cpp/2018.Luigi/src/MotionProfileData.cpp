#include "MotionProfileData.h"
#include <iostream>

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
	for (int i = 0; i<_points; ++i) {
		for (int j = 0; j<3; ++j) {
			_MP1[i][j] = MP1[i][j];
		}
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
