#
# perl script to generate all motion profile files for the DDU arm
#
# Rotations / angles:
#
#       rotations of          degrees of
#       gear wheel            movement
#       --------------------------------
#       1.0                   360
#       0.5                   180
#       0.25                  90
#       0.16667               60
#       0.125                 45
#       0.08333               30
#       0.05                  18
#       0.01                  3.6
#
# These notes assume 5 positions with the upright being zero degrees, the others are
# separated by 45 degrees ...
#
#                 |
#                 |
#                 |
#                 C
#                 |
#        B        |        D
#                 |
#                 |
#     A           .           E
#
#  So we have the following 20 transitions to handle:
#
#         A to B      A to C      A to D      A to E
#
#         B to A      B to C      B to D      B to E
#
#         C to A      C to B      C to D      C to E
#
#         D to A      D to B      D to C      D to E
#
#         E to A      E to B      E to C      E to D
#
# File naming convention will be ArmXY where X is the from location and Y is the to
# location. So, the above transitions will be called ...
#
#         ArmAB       ArmAC       ArmAD       ArmAE
#
#         ArmBA       ArmBC       ArmBD       ArmBE
#
#         ArmCA       ArmCB       ArmCD       ArmCE
#
#         ArmDA       ArmDD       ArmDC       ArmDE
#
#         ArmEA       ArmEB       ArmEC       ArmED
#

use strict;
use File::Copy;

my $eclipseroot = "c:/scm/icrobotics/frc/software/cpp";
my $eclipseprojectname = "2018.Waluigi";
my $eclipseprojectpath = "Waluigi/src/Custom";
my $deploy_header_files = 0;
my $deploy_csv_files = 0;

#####################################################################################
#                   FROM   TO

generatearmprofile( "A",   "B" );
generatearmprofile( "A",   "C" );
generatearmprofile( "A",   "D" );
generatearmprofile( "A",   "E" );

generatearmprofile( "B",   "A" );
generatearmprofile( "B",   "C" );
generatearmprofile( "B",   "D" );
generatearmprofile( "B",   "E" );

generatearmprofile( "C",   "A" );
generatearmprofile( "C",   "B" );
generatearmprofile( "C",   "D" );
generatearmprofile( "C",   "E" );

generatearmprofile( "D",   "A" );
generatearmprofile( "D",   "B" );
generatearmprofile( "D",   "C" );
generatearmprofile( "D",   "E" );

generatearmprofile( "E",   "A" );
generatearmprofile( "E",   "B" );
generatearmprofile( "E",   "C" );
generatearmprofile( "E",   "D" );

#####################################################################################

print "INFO: creating html document for all profiles\n";

runcmd( "perl motionprofile.arm.document.pl" );

#####################################################################################

if( $deploy_header_files )
  {
  my $targetdir = "${eclipseroot}/${eclipseprojectname}/${eclipseprojectpath}";
  if( -d $targetdir )
    {
    print "INFO: transfering *.h files to eclipse project $eclipseprojectname (please refresh project to reload)\n";
    foreach( glob( "*.h" ) )
      {
      print "  ... transfering $_\n";
      copy( $_, $targetdir );
      } 
    }
  else
    {
    print "WARNING: unable to transfer *.h files to eclipse project $eclipseprojectname - target directory does not exist!\n";
    }
  }

#####################################################################################

if( $deploy_csv_files )
  {
  my $targetdir = "${eclipseroot}/${eclipseprojectname}/${eclipseprojectpath}";
  if( -d $targetdir )
    {
    print "INFO: transfering *.csv files to eclipse project $eclipseprojectname (please refresh project to reload)\n";
    foreach( glob( "*.csv" ) )
      {
      print "  ... transfering $_\n";
      copy( $_, $targetdir );
      } 
    }
  else
    {
    print "WARNING: unable to transfer *.csv files to eclipse project $eclipseprojectname - target directory does not exist!\n";
    }
  }

#####################################################################################

sub runcmd
  {
  my ( $cmd ) = @_;
###  print "INFO: running: >$cmd<\n";
  print `$cmd 2>&1`;
  }

#####################################################################################

sub getangle
  {
  my ( $id ) = @_;
  my $retval = "UNKNOWN";
  $retval = -90 if( "$id" eq "A" );
  $retval = -45 if( "$id" eq "B" );
  $retval = 0 if( "$id" eq "C" );
  $retval = 45 if( "$id" eq "D" );
  $retval = 90 if( "$id" eq "E" );
  return $retval;
  }

#####################################################################################

sub generatearmprofile
  {
  my ( $f, $t ) = @_;

  my $from = $f;
  my $to = $t;

  my $pstart = getangle( $from );
  my $pend = getangle( $to );
  my $dist = ( $pend - $pstart ) / 360;
  my $pini = $pstart / 360;
  my $vini = 0;

###  my $vprog = 2.00;
  my $vprog = 0.50;
  if( $dist < 0 )
    { $vprog = $vprog * -1; }

  print "INFO: creating profiles for arm movement ${from} to ${to}\n";

  my $ident = "Arm${from}${to}";

  runcmd( "perl motionprofile.pl" .
          " -ident ${ident}" .
          " -mode SIMPLE" .
          " -t1 400 -t2 200 -itp 10" .
          " -vprog ${vprog} -dist ${dist}" .
          " -pini ${pini} -vini ${vini}" );

  print "INFO: creating graphs for arm movement ${from} to ${to}\n";

  runcmd( "perl motionprofile.arm.graph.pl -ident ${ident}" );
  }

#####################################################################################
