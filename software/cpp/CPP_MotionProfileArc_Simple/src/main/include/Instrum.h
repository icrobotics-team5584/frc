#pragma once

#include "ctre/Phoenix.h"
#include <string.h>
#include <iostream>
#include <sstream>
/**
 * Routines for printing to console (FRC Message log).
 */
class Instrum {
private:
	static int _loops;

	static bool _bPrintValues;

public:
	static void PrintLine(std::string s) {
		std::cout << s << std::endl;
	}

	static void Loop(bool bPrintValues, TalonSRX *talon) {
		if (!_bPrintValues && bPrintValues) {
			/* user just pressed button, immediete print */
			_loops = 999;
		}
		/* if button is off, don't print */
		if (bPrintValues == false) {
			/* reset so we don't print */
			_loops = 0;
		}
		/* save for next compare */
		_bPrintValues = bPrintValues;

		/* build string and print if button is down */
		if (++_loops >= 10) {
			_loops = 0;
			/* get status info */
			MotionProfileStatus status;
			talon->GetMotionProfileStatus(status);

			std::stringstream line;
			line << "  topBufferRem: " << status.topBufferRem << "\t";
			line << "  topBufferCnt: " << status.topBufferCnt << "\t";
			line << "  btmBufferCnt: " << status.btmBufferCnt << "\t";
			line << "  hasUnderrun: " << status.hasUnderrun << "\t";
			line << "  isUnderrun: " << status.isUnderrun << "\t";
			line << "  activePointValid: " << status.activePointValid << "\t";
			line << "  isLast: " << status.isLast << "\t";
			line << "  profileSlotSelect0: " << status.profileSlotSelect0 << "\t";
			line << "  profileSlotSelect1: " << status.profileSlotSelect1 << "\t";
			line << "  outputEnable: " << status.outputEnable << "\t";
			line << "  timeDurMs: " << status.timeDurMs << "\n";

			PrintLine(line.str());
		}
	}
};

int Instrum::_loops = 0;
bool Instrum::_bPrintValues = false;
