README.TXT
==========

This sample downloaded from 

https://github.com/CrossTheRoadElec/FRC-Examples.git

This was modified to operate one side of a drivebase that has two motors with two TalonSRXs and a single CTRE
Magnetic Encoder on the driven wheel axle.

It is easiest to monitor what is going on by displaying the console output from the roborio - click on the cog
on the driver station then select "View Console".

Some examples of the program working via button 1 ... assuming position = 0 at startup ...

1. Joystick moved full forward then press button 1: drive wheels (on one side) will complete -50
revolutions to get to position=-50

2. Joystick moved full backward then press button 1: drive wheels (on one side) will complete +100
revolutions to get to position=+50

3. Joystick moved to half backward position then press button 1: drive wheels (on one side) will
complete -25 revolutions to get to position=+25

You can also use button 2 with a trial and error approach to determine whether you need
SetSensorDirection(true) or SetSensorDirection(false), the process will be ...

1. Push the joystick forward then press button 2

2. Look at the console output:

     if out value is positive and position reported is increasing then you have the correct SetSensorDirection() setting
     if out value is positive and position reported is decreasing then you have the incorrect SetSensorDirection() setting
     if out value is negative and position reported is decreasing then you have the correct SetSensorDirection() setting
     if out value is negative and position reported is increasing then you have the incorrect SetSensorDirection() setting

3. Once this has been established and the correct SetSensorDirection() call made in your code then the button 1 behavior
will be as described above.
