README.TXT
==========

This sample downloaded from 

https://github.com/CrossTheRoadElec/FRC-Examples.git

This was modified to operate one side of a drivebase that has two motors with two TalonSRXs and a single CTRE
Magnetic Encoder on the driven wheel axle.

It is easiest to monitor what is going on by displaying the console output from the roborio - click on the cog
on the driver station then select "View Console".

Some examples of the program working using buttons 5 and 6 ...

1. Enable program in teleop mode via driver station.

2. Press and hold button 5 then press button 6 momentarily.

3. Robot drive on one side will operate for just under 2 seconds based on the profile in the MotionProfile.h file.

4. The world rises to it's feet and applauses at your greatness ... maybe not.

If you are having trouble with this, it is worth checking that you have the sensor direction setting correct. This is
a lot easier to do with the "CPP_PositionClosedLoop" sample code than this exapmple so get that working first then
return to this example.

You may also need to adjust the F-gain in Robot.cpp. We calculated this as described in the CTRE PDF ...

1. Run this code in teleop mode.

2. Navigate to http://roborio-8888-frc.frc-robot.local

3. Select Talon 1

4. Push joystick full forward (motors should be running at full speed on one side of the drive base)

5. Select "Self-Test" on the browser

6. Release Joystick.

7. Make a note of the "RPM" and "Velocity" values in the top section (values X.XX an YYY in the sample here) ...

        Selected Device:6:CTRE MagEnc (rel)
        Pos (rot):  36.715 	Velocity (RPM):   X.XX
        Pos:150388 	Velocity:YYY

8. In our case these were RPM=800 and VELOCITY=5460 (native units per 100ms)

9. This could have been calculated with 4096 x 800 * 1/60 * 1/10

10. F-gain = 100% of 1023 / 5460 =0187363

11. This is the F-gain that we plumbed into the Robot.cpp along with the correct slot selection of course (example code uses slot 1)
