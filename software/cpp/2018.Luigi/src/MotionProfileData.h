#ifndef SRC_MOTIONPROFILEDATA_H_
#define SRC_MOTIONPROFILEDATA_H_

class MotionProfileData {
public:
	MotionProfileData( const double [][3], const double [][3], const int );
	MotionProfileData( const double [][3], const int );
    int GetNumberOfPoints();
    double GetPosition( int, int );
    double GetVelocity( int, int );
    double GetDuration( int, int );

private:
	static const int kMaxMotionProfilePoints = 2048;
	double _MP1[kMaxMotionProfilePoints][3];
	double _MP2[kMaxMotionProfilePoints][3];
	int _points;
	int _sets;

};

#endif /* SRC_MOTIONPROFILEDATA_H_ */
