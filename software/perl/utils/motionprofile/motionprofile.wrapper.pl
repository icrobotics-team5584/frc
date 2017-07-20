#
# perl scrit to generate all motion profile files
#
# NOTE: 1 rotation of a 3.5" diameter wheel equates to 11" (279mm) of travel
#

use strict;
use File::Copy;

my $eclipseroot = "c:/scm/icrobotics/frc/software/cpp";
my $eclipseprojectname = "Chunky.Wantirna";
my $eclipseprojectpath = "src/Custom";

#####################################################################################

print "INFO: creating profiles for baseline run\n";

my $vprog = 2.00;
my $dist = 10.00;
my $curve2dist = 0.00;
my $curve2offset = 0;

my $biasA = 1.01;
my $biasB = 1.00;
my $vprogA = $vprog * $biasA;
my $vprogB = $vprog * $biasB;
my $distA = $dist * $biasA;
my $distB = $dist * $biasB;
my $curve2distA = $curve2dist * $biasA;
my $curve2distB = $curve2dist * $biasB;

runcmd( "perl motionprofile.pl -ident BaselineA -mode SIMPLE -t1 400 -t2 200 -itp 10 -vprog ${vprogA} -dist ${distA}" );
runcmd( "perl motionprofile.pl -ident BaselineB -mode SIMPLE -t1 400 -t2 200 -itp 10 -vprog ${vprogB} -dist ${distB}" );

print "INFO: creating graphs for baseline run\n";

runcmd( "perl motionprofile.graph.pl -ident BaselineA" );
runcmd( "perl motionprofile.graph.pl -ident BaselineB" );

#####################################################################################

print "INFO: creating profiles for middle peg run\n";

my $vprog = 2.00;
my $dist = 6.70;
my $curve2dist = 0.00;
my $curve2offset = 0;

my $biasA = 1.01;
my $biasB = 1.00;
my $vprogA = $vprog * $biasA;
my $vprogB = $vprog * $biasB;
my $distA = $dist * $biasA;
my $distB = $dist * $biasB;
my $curve2distA = $curve2dist * $biasA;
my $curve2distB = $curve2dist * $biasB;

runcmd( "perl motionprofile.pl -ident MidA      -mode SIMPLE -t1 400 -t2 200 -itp 10 -vprog ${vprogA} -dist ${distA}" );
runcmd( "perl motionprofile.pl -ident MidB      -mode SIMPLE -t1 400 -t2 200 -itp 10 -vprog ${vprogB} -dist ${distB}" );

print "INFO: creating graphs for middle peg run\n";

runcmd( "perl motionprofile.graph.pl -ident MidA" );
runcmd( "perl motionprofile.graph.pl -ident MidB" );

#####################################################################################

print "INFO: creating profiles for retreat run\n";

my $vprog = -2.00;
my $dist = -1.50;
my $curve2dist = 0.00;
my $curve2offset = 0;

my $biasA = 1.01;
my $biasB = 1.00;
my $vprogA = $vprog * $biasA;
my $vprogB = $vprog * $biasB;
my $distA = $dist * $biasA;
my $distB = $dist * $biasB;
my $curve2distA = $curve2dist * $biasA;
my $curve2distB = $curve2dist * $biasB;

runcmd( "perl motionprofile.pl -ident RetreatA  -mode SIMPLE -t1 400 -t2 200 -itp 10 -vprog ${vprogA} -dist ${distA}" );
runcmd( "perl motionprofile.pl -ident RetreatB  -mode SIMPLE -t1 400 -t2 200 -itp 10 -vprog ${vprogB} -dist ${distB}" );

print "INFO: creating graphs for retreat run\n";

runcmd( "perl motionprofile.graph.pl -ident RetreatA" );
runcmd( "perl motionprofile.graph.pl -ident RetreatB" );

#####################################################################################

print "INFO: creating profiles for right peg run\n";

my $vprog = 2.00;
my $dist = 12.45;
my $curve2dist = 2.50;
my $curve2offset = 235;

my $biasA = 1.01;
my $biasB = 1.00;
my $vprogA = $vprog * $biasA;
my $vprogB = $vprog * $biasB;
my $distA = $dist * $biasA;
my $distB = $dist * $biasB;
my $curve2distA = $curve2dist * $biasA;
my $curve2distB = $curve2dist * $biasB;

runcmd( "perl motionprofile.pl -ident RightA    -mode MULTI  -t1 400 -t2 200 -itp 10 -vprog ${vprogA} -dist ${distA} -curve2dist ${curve2distA} -curve2offset $curve2offset -curve2proportion 0.5 -curve2multiplier -1" );
runcmd( "perl motionprofile.pl -ident RightB    -mode SIMPLE -t1 400 -t2 200 -itp 10 -vprog ${vprogB} -dist ${distB}" );

print "INFO: creating graphs for right peg run\n";

runcmd( "perl motionprofile.graph.pl -ident RightA" );
runcmd( "perl motionprofile.graph.pl -ident RightB" );

#####################################################################################

print "INFO: creating profiles for left peg run\n";

my $vprog = 2.00;
my $dist = 12.85;
my $curve2dist = 2.60;
my $curve2offset = 250;

my $biasA = 1.01;
my $biasB = 1.00;
my $vprogA = $vprog * $biasA;
my $vprogB = $vprog * $biasB;
my $distA = $dist * $biasA;
my $distB = $dist * $biasB;
my $curve2distA = $curve2dist * $biasA;
my $curve2distB = $curve2dist * $biasB;

runcmd( "perl motionprofile.pl -ident LeftA     -mode SIMPLE -t1 400 -t2 200 -itp 10 -vprog ${vprogA} -dist ${distA}" );
runcmd( "perl motionprofile.pl -ident LeftB     -mode MULTI  -t1 400 -t2 200 -itp 10 -vprog ${vprogB} -dist ${distB} -curve2dist ${curve2distB} -curve2offset $curve2offset - curve2proportion 0.5 -curve2multiplier -1" );

print "INFO: creating graphs for left peg run\n";
runcmd( "perl motionprofile.graph.pl -ident LeftA" );
runcmd( "perl motionprofile.graph.pl -ident LeftB" );

#####################################################################################

print "INFO: creating html document for all profiles\n";

runcmd( "perl motionprofile.document.pl" );



my $targetdir = "${eclipseroot}/${eclipseprojectname}/${eclipseprojectpath}";
if( -d $targetdir )
  {
  print "INFO: transfering files to eclipse project $eclipseprojectname (please refresh project to reload)\n";
  foreach( glob( "*.h" ) )
    {
    print "  ... transfering $_\n";
    copy( $_, $targetdir );
    } 
  }
else
  {
  print "WARNING: unable to transfering files to eclipse project $eclipseprojectname - target directory does not exist!\n";
  }



sub runcmd
  {
  my ( $cmd ) = @_;
  print `$cmd 2>&1`;
  }
