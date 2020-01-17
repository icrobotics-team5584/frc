README.TXT
==========



Overview:
---------

This suite of perl utilities can be used to generate multiple Motion Profiles for use in FRC C++ code.

The profiles generated are designed for use with TALON SRX motor controllers configured for use in "Motion Profile Arc" mode. For a sample project refer to CPP_MotionProfileArc_Simple in the IC github repo (frc/software/cpp/CPP_MotionProfileArc_Simple).

The main utility is motionprofile.pl which is controlled by a simple XML file (motionprofile.xml). The motionprofile.pl utility generates two output files for each profile that is defined in the motionprofile.xml input file: a C++ header and a CSV file. The output files are named MotionProfile{profilename}.h and MotionProfile{profilename}.csv.

There is a graph generating utility (motionprofile.graph.pl) which takes a profile in CSV format and generates a graph as a PNG image.

The motionprofile.document.pl utility can be used to generate a single HTML sumarry document that references each of the generated PNG images.

The wrapper utility motionprofile.wrapper.pl can be used to run all of the above and optionally "deploy" the header files into the VSCODE IDE.

Recommend that you run the utilities in a git bash shell.



Prerequisites:
--------------

NOTE: motionprofile.graph.pl has a dependency on the GD module. If your version of perl reports errors like "Can't locate GD/Graph/lines.pm in @INC (you may need to install the GD::Graph::lines module) (@INC contains: ..." then install the GD module and any dependencies, or just install strawberry perl as that has GD and depencencies already incorporated in the base package.

NOTE: to change the perl installation that is used you will need to add the appropriate installation directory to the start of the path, if using GIT bash shell then ...

        export PATH=/c/Strawberry/perl/bin/:$PATH

Or, if using windows command prompt ...

        set PATH=c:\Strawberry\perl\bin\;%PATH%

NOTE: if the GD::Graph module is still listed as missing then use CPAN Client to install the module ...

    Start Menu > Strawberry Perl > Tools > CPAN Client
    Start > Cpan Client
    Start Menu > All Apps > Strawberry Perl > CPAN Client

Then install the module (e.g. the GD::Graph module) in the client window by typing ...

    install GD::Graph
    exit



XML control file format:
------------------------

Refer to motionprofile.xml for sample configuration.i

The parameters used for config format version 1.0 are ...

* "robot" section consisting of ONE of each of the following parameters:
  * "name" = name of the robot (e.g. "MUCK")
  * "wheels"
    * "diameter" = diameter of the wheel(s) that drive the encoder
    * "track" = distance between left and right drive wheels
  * "sensor"
    * "mode" = the mode of the distance source (allowed values are: SensorSum|Quadrature)

* "controls" section consisting of ONE of each of the following parameters:
    * "pathlimit" = maximium path length - this is intended to provide a safety check only
    * "velocity" = the cruise velocity of the profile
    * "itp" =  interval (msec)
    * "t1" = time constant 1
    * "t2" = time constant 2

* "units" section consisting of ONE of each of the following parameters:
  * "time" = all times in the xml are in this unit (allowed values: seconds)
  * "length" = all lengths in the xml are in this unit (allowed values: inches)
  * "angle" = all angles in the xml are in this unit (allowed values: degrees)

* "profiles" section consisting of ONE OR MORE "profile" sections:

  * "profile" section consisting of ONE of each of the following parameters:
    * "name" = name of the profile (e.g. "InitialisationToTrench")
    * "direction" = forwards|backwards
    * "path" section consisting of ONE OR MORE "segment" sections:
      * "segment" sections can be of two types (turn or straight)
        * straight segment consists of ONE of each of the following parameters:
	  * "id" = an integer to specify the order of the segment
	  * "type" =  "straight"
	  * "length" = the length of the segment
        * turn segment consists of ONE of each of the following parameters:
	  * "id = an integer to specify the order of the segment
	  * "type = "turn"
	  * "turn = right|left (when specifying this, irrespective of forwards/backwards, imagine sitting on the robot facing the front)
	  * "angle" =  change of direction (positive number)
	  * "length" = the length of the segment

NOTE: profile and segment names should be unique.

NOTE: segment IDs should be numerical 1,2,3 ..

NOTE: by design a profile runs all segments in the same direction. Where the robot needs to in one direction and then another it is expected that each will be configured as a separate profile (in the same XML control file).

