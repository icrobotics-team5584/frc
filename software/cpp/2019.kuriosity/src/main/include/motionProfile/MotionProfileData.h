#ifndef SRC_MOTIONPROFILEDATA_H_
#define SRC_MOTIONPROFILEDATA_H_

#include <vector>
#include <Libaries/csv.h>
#include <ctre/Phoenix.h>
#include <pathfinder.h>

enum TrajectoryDuration {
	TrajectoryDuration_0ms = 0,
	TrajectoryDuration_5ms = 5,
	TrajectoryDuration_10ms = 10,
	TrajectoryDuration_20ms = 20,
	TrajectoryDuration_30ms = 30,
	TrajectoryDuration_40ms = 40,
	TrajectoryDuration_50ms = 50,
	TrajectoryDuration_100ms = 100,
};

class MotionProfileData {
public:

	MotionProfileData();
    void ReadSegment(int set, Segment *path, int length);
	void ReadCSV(int set, std::string fileName);
	void ReadMotionProfile(std::string MP);
	void ReadMotionProfile(Segment *path, int length, double wheelBaseWidth);
    int GetNumberOfPoints();
    double GetPosition( int set, int number);
    double GetVelocity( int set, int number);
    double GetDuration( int set, int number);
    TrajectoryDuration ConvertDuration(double dur);
    TrajectoryPoint GetPoint(int set, int number);
    std::vector<std::vector<TrajectoryPoint>> sets;
	int mpSize;

};

#endif /* SRC_MOTIONPROFILEDATA_H_ */
