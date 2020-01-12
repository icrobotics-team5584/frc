#
# perl script to generate all motion profile files
#
# NOTE: 1 rotation of a 3.5" diameter wheel equates to 11.00" (279mm) of travel
#
# NOTE: 2 rotation of a 4.0" diameter wheel equates to 12.57" (319mm) of travel
#

use strict;
use File::Copy;

my $vscoderoot = "/c/scm/icrobotics/frc/software/cpp";
my $vscodeprojectname = "CPP_MotionProfileArc_Simple";
my $vscodeprojectpath = "src/main/include";
my $deploy_single_header_file = 1;
my $deploy_header_files = 0;
my $deploy_csv_files = 0;

#####################################################################################

print "INFO: creating profile for primary MotionProfile run\n";

my $vprog = 5.00;
my $dist = 40.00;
my $curve2dist = 0.00;
my $curve2offset = 0;

runcmd( "perl motionprofile.pl -ident MotionProfile -mode SIMPLE -t1 400 -t2 200 -itp 10 -vprog ${vprog} -dist ${dist}" );

print "INFO: creating graphs for MotionProfile run\n";

runcmd( "perl motionprofile.graph.pl -ident MotionProfile" );

#####################################################################################

print "INFO: creating html document for all profiles\n";

runcmd( "perl motionprofile.document.pl" );

#####################################################################################

if( $deploy_single_header_file )
  {
  my $targetdir = "${vscoderoot}/${vscodeprojectname}/${vscodeprojectpath}";
  if( -d $targetdir )
    {
    print "INFO: transfering MotionProfile.h files to vscode project $vscodeprojectname (please refresh project to reload)\n";
    copy( "MotionProfileMotionProfile.h", "$targetdir/MotionProfile.h" );
    }
  else
    {
    print "WARNING: unable to transfer *.h files to vscode project $vscodeprojectname - target directory does not exist!\n";
    }
  }

#####################################################################################

if( $deploy_header_files )
  {
  my $targetdir = "${vscoderoot}/${vscodeprojectname}/${vscodeprojectpath}";
  if( -d $targetdir )
    {
    print "INFO: transfering *.h files to vscode project $vscodeprojectname (please refresh project to reload)\n";
    foreach( glob( "*.h" ) )
      {
      print "  ... transfering $_\n";
      copy( $_, $targetdir );
      } 
    }
  else
    {
    print "WARNING: unable to transfer *.h files to vscode project $vscodeprojectname - target directory does not exist!\n";
    }
  }

#####################################################################################

if( $deploy_csv_files )
  {
  my $targetdir = "${vscoderoot}/${vscodeprojectname}/${vscodeprojectpath}";
  if( -d $targetdir )
    {
    print "INFO: transfering *.csv files to vscode project $vscodeprojectname (please refresh project to reload)\n";
    foreach( glob( "*.csv" ) )
      {
      print "  ... transfering $_\n";
      copy( $_, $targetdir );
      } 
    }
  else
    {
    print "WARNING: unable to transfer *.csv files to vscode project $vscodeprojectname - target directory does not exist!\n";
    }
  }

#####################################################################################

sub runcmd
  {
  my ( $cmd ) = @_;
  print `$cmd 2>&1`;
  }
