#!/usr/bin/perl
#
# perl script to extract version information from native file and package systems for FRC in 2019 and later seasons
#
# COMMAND PROMPT USAGE: "c:\Program Files\Git\usr\bin\perl.exe" softwareinventory.pl
#
# OR: "c:\Program Files (x86)\Git\usr\bin\perl.exe" softwareinventory.pl
#
# BASH TERMINAL USAGE:  "./softwareinventory.pl"
#
# OR: "/c/Program Files/Git/usr/bin/perl.exe" softwareinventory.pl
#
# OR: "/c/Program Files (x86)/Git/usr/bin/perl.exe" softwareinventory.pl
#

use Cwd;

my $CWD = getcwd;
my $ME = "softwareinventory";
my $YEAR = "2021";
my $TMPDIR = "$ENV{'TEMP'}";

my $FRCDIR;
my $LVDIR;
if( "$YEAR" eq "2021" )
  {
  $FRCDIR = "C:\\Users\\Public\\wpilib\\2021";
  $LVDIR = "C:\\Program Files (x86)\\National Instruments\\LabVIEW 2019";
  }
elsif( "$YEAR" eq "2020" )
  {
  $FRCDIR = "C:\\Users\\Public\\wpilib\\2020";
  $LVDIR = "C:\\Program Files (x86)\\National Instruments\\LabVIEW 2019";
  }
elsif( "$YEAR" eq "2019" )
  {
  $FRCDIR = "C:\\Users\\Public\\frc2019";
  $LVDIR = "C:\\Program Files (x86)\\National Instruments\\LabVIEW 2018";
  }
else
  {
  print "ERROR: unsupported year - aborting!\n";
  exit 1;
  }
my $EXEEXTRACTOR = "$TMPDIR/$ME.$$.vbs";
my $JAREXTRACTOR = "${FRCDIR}\\jdk\\bin\\jar.exe";
my $FRCTOOLROOT = "${FRCDIR}\\tools";
my $FRCVSCODEROOT = "${FRCDIR}\\vscode";
my $FRCDOCOROOT = "${FRCDIR}\\documentation";
my $FRCPROJROOT = "${LVDIR}\\project";
my $FRCINSTROOT = "C:\\Program Files (x86)";

my %PMSI;

# STEP 1 : extract version information from PMSI in registry
loadpmsi();
print "INFO: version information extracted from Windoze Software Inventory . . .\n";
extractversionfrompmsi('7-Zip');
extractversionfrompmsi('CTRE Phoenix Framework');
extractversionfrompmsi('FRC Radio Configuration Utility');
extractversionfrompmsi('Git');
extractversionfrompmsi('Java');
extractversionfrompmsi('WinPcap');
extractversionfrompmsi('MobaXterm');

# STEP 2 : extract version information from specific EXE files
print "INFO: version information extracted from EXE files . . .\n";
constructexeextractor();
extractversionfromexe( 'VS Code',               "${FRCVSCODEROOT}\\Code.exe" );
extractversionfromexe( 'FRC Driver Station',    "${FRCINSTROOT}\\FRC Driver Station\\DriverStation.exe" );
extractversionfromexe( 'FRC DS Logfile Viewer', "${FRCINSTROOT}\\FRC Driver Station\\DS_logFileViewer.exe" );
extractversionfromexe( 'FRC Gamepad Tool',      "${FRCINSTROOT}\\FRC Gamepad Tool\\Gamepad Tool.exe" );
extractversionfromexe( 'FRC GT DP Inst',        "${FRCINSTROOT}\\FRC Gamepad Tool\\Tools\\driver\\DPInst.exe" );
extractversionfromexe( 'FRC GT DP Inst (x64)',  "${FRCINSTROOT}\\FRC Gamepad Tool\\Tools\\driver\\DPInst64.exe" );
extractversionfromexe( 'FRC Dashboard',         "${FRCINSTROOT}\\FRC Dashboard\\Dashboard.exe" );
extractversionfromexe( 'roboRIO Imaging Tool',  "${FRCPROJROOT}\\roboRIO Tool\\roboRIO_ImagingTool.exe" );
extractversionfromexe( 'Axis Camera Tool',      "${FRCPROJROOT}\\Axis Camera Tool\\AxisCameraSetup.exe" );
destroyexeextractor();

# STEP 3 : extract version information from specific JAR files
print "INFO: version information extracted from JAR files . . .\n";
extractversionfromjar( 'OnlineViewer',          "${FRCTOOLROOT}\\OutlineViewer.jar" );
extractversionfromjar( 'PathWeaver',            "${FRCTOOLROOT}\\PathWeaver.jar" );
extractversionfromjar( 'RobotBuilder',          "${FRCTOOLROOT}\\RobotBuilder.jar" );
extractversionfromjar( 'RobotBuilder (old)`',   "${FRCTOOLROOT}\\RobotBuilder-Old.jar" );
extractversionfromjar( 'Shuffleboard',          "${FRCTOOLROOT}\\shuffleboard.jar" );
extractversionfromjar( 'SmartDashboard',        "${FRCTOOLROOT}\\SmartDashboard.jar" );
extractversionfromjar( 'ToolsUpdater',          "${FRCTOOLROOT}\\ToolsUpdater.jar" );

# STEP 4 : extract version information from specific HTM files
print "INFO: version information extracted from HTM files . . .\n";
extractversionfromhtm( 'FRC Documentation',   "${FRCDOCOROOT}\\cpp\\index.html" );

exit 0;



sub loadpmsi
  {
  my $cmd;
  my $regtool;
  if( -e "c:\\Program Files\\Git\\usr\\bin\\regtool.exe" )
    {
    $cmd = '"c:\Program Files\Git\usr\bin\regtool.exe" list /HKLM/SOFTWARE/WOW6432Node/Microsoft/Windows/CurrentVersion/Uninstall';
    $regtool = "c:\\Program Files\\Git\\usr\\bin\\regtool.exe";
    }
  elsif( -e "c:\\Program Files (x86)\\Git\\usr\\bin\\regtool.exe" )
    {
    $cmd = '"c:\Program Files (x86)\Git\usr\bin\regtool.exe" list /HKLM/SOFTWARE/WOW6432Node/Microsoft/Windows/CurrentVersion/Uninstall';
    $regtool = "c:\\Program Files (x86)\\Git\\usr\\bin\\regtool.exe";
    }
  else
    {
    print "ERROR: unable to locate regtool - aborting!\n";
    exit 1;
    }
  # print "DEBUG: cmd: >$cmd<\n";
  # print "DEBUG: regtool: >$regtool<\n";
  foreach( `$cmd` )
    {
    s|\x0A||;
    s|\x0D||;
    # print "DEBUG: >$_<\n";
    my $component = $_;
    my $cmd = "\"${regtool}\" get \"/HKLM/SOFTWARE/WOW6432Node/Microsoft/Windows/CurrentVersion/Uninstall/${component}/DisplayName\"";
    my $dn = `$cmd 2>&1`;
    $dn =~ s|\x0A||;
    $dn =~ s|\x0D||;
    my $cmd = "\"${regtool}\" get \"/HKLM/SOFTWARE/WOW6432Node/Microsoft/Windows/CurrentVersion/Uninstall/${component}/DisplayVersion\"";
    my $dv = `$cmd 2>&1`;
    $dv =~ s|\x0A||;
    $dv =~ s|\x0D||;
    next if( $dn =~ /^Error/ );
    next if( $dv =~ /^Error/ );
    if( "$dn" ne "" && "$dv" ne "" )
      {
      # print "DEBUG: $dn: $dv\n";
      $PMSI{$dn} = $dv;
      }
    }
  }

sub constructexeextractor
  {
  if( ! -e "$EXEEXTRACTOR" )
    {
    open( EE, ">$EXEEXTRACTOR" );
    print EE "set args = WScript.Arguments\n";
    print EE "Set fso = CreateObject(\"Scripting.FileSystemObject\")\n";
    print EE "WScript.Echo fso.GetFileVersion(args(0))\n";
    print EE "Wscript.Quit\n";
    close( EE );
    }
  }

sub destroyexeextractor
  {
  if( -e "$EXEEXTRACTOR" )
    {
    unlink( "$EXEEXTRACTOR" );
    }
  }

sub extractversionfrompmsi
  {
  my ( $prefix ) = @_;
  foreach( sort( keys( %PMSI ) ) )
    {
    my $key = $_;
    my $val = $PMSI{$_};
    if( $key =~ /^${prefix}/ )
      {
      print "  $prefix: $val\n";
      }
    }
  }

sub extractversionfromexe
  {
  my ( $txt, $exe ) = @_;
  my $cmd = "cscript //nologo \"$EXEEXTRACTOR\" \"$exe\"";
  print "  $txt: " . `$cmd 2>&1`;
  }

sub extractversionfromjar
  {
  my ( $txt, $jar ) = @_;
  my $cmd = "\"$JAREXTRACTOR\" xf \"$jar\" META-INF/MANIFEST.MF";
  chdir( $TMPDIR );
  `$cmd 2>&1`;
  my $metafile = "$ENV{'TEMP'}/META-INF/MANIFEST.MF";
  my $version = "";
  open( META, "<$metafile" );
  while( <META> )
    {
      s|\x0A||;
      s|\x0D||;
    if( /version/i )
      {
      s|^.*:\s*||;
      s|[^\d]*$||;
      $version = $_;
      }
    }
  close( META );
  unlink( $metafile );
  print "  $txt: $version\n";
  chdir( $CWD );
  }

sub extractversionfromhtm
  {
  my ( $txt, $htm ) = @_;
  my $version = "";
  open( HTM, "<$htm" );
  while( <HTM> )
    {
    if( /projectnumber/ )
      {
      s|^.*projectnumber[^\d]*||;
      s|[^\d]*$||;      
      $version = $_;
      }
    }
  close( HTM );
  print "  $txt: $version\n";
  }
