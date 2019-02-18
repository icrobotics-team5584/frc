#
# perl script to extract version information from native file and package systems for FRC in 2019 season
#
# COMMAND PROMPT USAGE: "c:\Program Files\Git\usr\bin\perl.exe" softwareinventory.pl
#
# BASH TERMINAL USAGE: "/c/Program Files/Git/usr/bin/perl.exe" softwareinventory.pl
#

use Cwd;

my $CWD = getcwd;
my $ME = "softwareinventory";
my $TMPDIR = "$ENV{'TEMP'}";
my $EXEEXTRACTOR = "$TMPDIR/$ME.$$.vbs";
my $JAREXTRACTOR = "C:\\Users\\Public\\frc2019\\jdk\\bin\\jar.exe";
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
extractversionfromexe( 'FRC Driver Station',  'C:\Program Files (x86)\FRC Driver Station\DriverStation.exe' );
extractversionfromexe( 'FRC Gamepad Tool',    'C:\Program Files (x86)\FRC Gamepad Tool\Gamepad Tool.exe' );
extractversionfromexe( 'FRC Dashboard',       'C:\Program Files (x86)\FRC Dashboard\Dashboard.exe' );
destroyexeextractor();

# STEP 3 : extract version information from specific JAR files
print "INFO: version information extracted from JAR files . . .\n";
extractversionfromjar( 'OnlineViewer',        'C:\Users\Public\frc2019\tools\OutlineViewer.jar' );
extractversionfromjar( 'PathWeaver',          'C:\Users\Public\frc2019\tools\PathWeaver.jar' );
extractversionfromjar( 'RobotBuilder',        'C:\Users\Public\frc2019\tools\RobotBuilder.jar' );
extractversionfromjar( 'Shuffleboard',        'C:\Users\Public\frc2019\tools\shuffleboard.jar' );
extractversionfromjar( 'SmartDashboard',      'C:\Users\Public\frc2019\tools\SmartDashboard.jar' );
extractversionfromjar( 'ToolsUpdater',        'C:\Users\Public\frc2019\tools\ToolsUpdater.jar' );

# STEP 4 : extract version information from specific HTM files
print "INFO: version information extracted from HTM files . . .\n";
extractversionfromhtm( 'FRC Documentation',   'C:\Users\Public\frc2019\documentation\cpp\index.html' );

sub loadpmsi
  {
  my $cmd = '"c:\Program Files\Git\usr\bin\regtool.exe" list /HKLM/SOFTWARE/WOW6432Node/Microsoft/Windows/CurrentVersion/Uninstall';
  # print "DEBUG: cmd: >$cmd<\n";
  foreach( `$cmd` )
    {
    s|\x0A||;
    s|\x0D||;
    # print "DEBUG: >$_<\n";
    my $component = $_;
    my $cmd = "\"c:\\Program Files\\Git\\usr\\bin\\regtool.exe\" get \"/HKLM/SOFTWARE/WOW6432Node/Microsoft/Windows/CurrentVersion/Uninstall/${component}/DisplayName\"";
    my $dn = `$cmd 2>&1`;
    $dn =~ s|\x0A||;
    $dn =~ s|\x0D||;
    my $cmd = "\"c:\\Program Files\\Git\\usr\\bin\\regtool.exe\" get \"/HKLM/SOFTWARE/WOW6432Node/Microsoft/Windows/CurrentVersion/Uninstall/${component}/DisplayVersion\"";
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
