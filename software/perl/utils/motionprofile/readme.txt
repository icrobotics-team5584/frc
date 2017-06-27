README.TXT
==========



Overview:
---------

This suite of 4 perl scripts can be used to generate multiple Motion Profiles for use in FRC C++ code.

For a drive base we typically generate pairs (A and B) of profiles for each autonomous run. Profile A will be applied to one side of the drivebase and Profile B to the other. If the profiles are the same then the robot can be expected to drive in a straight line. If profiles A and B are different then you can expect the robot to travel a curved path.

The aim of the MULTI mode is to support generation of a profile that can be used on one side of the robot. Coupling this with a SIMPLE profile generated for the other side of the robot we can expect the robot to move in three phases: (i) accelerating in sync on both sides to drive straight at constanst speed; (ii) then decelerating on one side (therefore turning) for a period before accelerating on that side to matching speed on both sides; (c) complete remainder of profiles at the same speed and decelerate both sides in sync (i.e. straight drive).



Summary:
--------

  motionprofile.wrapper.pl      - wrapper script enabling us to record all parameters and regenerate all motion profiles in one hit, as well as calling each of the other three scripts here, the wrapper will copy the *.h files into the appropriate directory of the eclipse project

  motionprofile.pl              - generates a *.h and a *.csv using the parameters listed below

  motionprofile.graph.pl        - generates *.png image from the *.csv file, image contains a graph of the position, velocity and acceleration in the profile

  motionprofile.document.pl     - generates a single MotionProfile.html file with references to each of the *.png files so that we have a summary-on-a-page of all of the Motion Profiles that we have generated



Parameters:
-----------

Basic parameters used in SIMPLE and MULTI modes ...

  -ident = name of the profile (e.g. LeftPegA, LeftPegB, RightPegA, RightPegB, MidPegA, MidPegB, BaselineA, BaselineB)

  -mode  = SIMPLE|MULTI - use SIMPLE for a single inverted bathtub profile, use MULTI for a curve constructed from two bathtubs (either added or subtracted)

  -t1    = time constant 1

  -t2    = time constant 2

  -itp   = interval (msec)

  -vprog = maximum (rotations/sec)

  -dist  = distance to travel (rotations)

Additional parameters for MULTI mode ...

  -curve2dist       = distance for second curve (rotations)

  -curve2offset     = delay from curve one to curve two in steps

  -curve2proportion = curve 2 magnitude relative to curve 1 magnitude (in range 0 to 1)

  -curve2multiplier = set to +1 for curves to be additive, set to -1 for curve 2 to be subtracted from curve 1
