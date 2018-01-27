# perl script to generate c++ *.h file from a *.csv
#
# USAGE: takes *.csv file as the only command line argument and creates adjacent *.h
#
#   perl motionprofileconverter.pl S1\S1_left.csv
#
# NOTE: input *.csv file format will be ...
#
#   0, 0 ,10.0
#   :
#   :
#   10.1000000000001, 0, 10.0
#
# NOTE: output *.h file format will be ...
#
#   #ifndef SRC_MOTIONPROFILES_MOTIONPROFILE<iiiii>
#   #define SRC_MOTIONPROFILES_MOTIONPROFILE<iiiii>
#   // COLUMN 1 = Position (rotations)
#   // COLUMN 2 = Velocity (rpm)
#   // COLUMN 3 = Duration (ms)
#   const int k<iiiiii>Sz = <nnnnn>;
#   const double k<iiiii>[][3] = {
#   {0,     0       ,10.0},
#   :
#   :
#   {10.1000000000001,      0       ,10.0}};
#   #endif
#
# where
#
#   nnnnn = number of points (rows) in the CSV file
#   iiiii = unique ident based on CSV filename
#

use strict;

my $csvfile = $ARGV[0];
my $outfile = $csvfile;
$outfile =~ s|\.csv$|.h|;
my $ident = $csvfile;
$ident =~ s|\.csv$||;
$ident =~ s|\/|_|g;

if( ! -e $csvfile )
  {
  print "ERROR: csvfile ($csvfile) does not exist - aborting!\n";
  exit 1;
  } 

print "INFO: using identifier $ident\n";
print "INFO: using input file $csvfile\n";
print "INFO: using output file $outfile\n";

my $numberofpoints = 0;
my @pointsbuffer;
open( CSV, "<${csvfile}" );
while( <CSV> )
  {
  s|\x0A||;
  s|\x0D||;
  if( /^\d+\.\d+, \d+\.\d+, \d+$/ )
    {
    push( @pointsbuffer, $_ );
    $numberofpoints++;
    }
  else
    {
    print "WARNING: detected dud line >$_< - skipping!";
    }
  }
close( CSV );
print "INFO: detected $numberofpoints points\n";

if( -e $outfile )
  {
  unlink( $outfile );
  }

outputfilestart( $ident, $numberofpoints );
my $pointnumber = 1;
my $eol = ",";
foreach ( @pointsbuffer )
  {
  $eol = "" if( $pointnumber == $numberofpoints );
  outputstr( "{$_}${eol}\n" );
  }
outputfileend();

exit 0;



sub outputstr
  {
  open( OUT, ">>$outfile" );
  print OUT @_;
  close( OUT );
  }

sub outputfilestart
  {
  my ( $ident, $points ) = @_;
  my $upperident = uc( $ident );
  outputstr(
    "#ifndef SRC_MOTIONPROFILES_${upperident}\n" .
    "#define SRC_MOTIONPROFILES_${upperident}\n" .
    "// COLUMN 1 = Position (rotations)\n" .
    "// COLUMN 2 = Velocity (rpm)\n" .
    "// COLUMN 3 = Duration (ms)\n" .
    "const int k${ident}Sz = ${points};\n" .
    "const double k${ident}[][3] = {\n"
    );
  }

sub outputfileend
  {
  outputstr(
    "};\n" .
    "#endif\n"
    );
  }
