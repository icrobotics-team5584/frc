#
# motion profile generator
#
# use in "SIMPLE" mode to generate a simple inverted bathtub velocity
# curve and the associated position and acceleration curves
#
# use in "MULTI" mode to generate a more complex set of curves constructed
# from two bathtub curves
#

use strict;

use Getopt::Long;

my $debug = 0;
my $ident = "NEW.SAMPLE";
my $mode = "MULTI";

# common parameters ...
my $itp = 10;   # in ms
my $t1 = 400;   # in ms
my $t2 = 200;   # in ms

# vprog and dist values for SIMPLE mode ...
my $vprog = 4;   # in rotations/sec
my $dist = 5;    # in rotations

# additional values required for MULTI mode ...
my $curve2offset = 106;        # in steps
my $curve2proportion = 0.50;   # use 0.0 to 1.0 to define curve2 max velocity relative to curve1
my $curve2multiplier = -1;     # set to +1 to add curve1 and curve2, set to -1 to subtract curve2 from curve1
my $curve2dist = 2.94;         # in rotations

GetOptions (
  "ident=s"            => \$ident,
  "mode=s"             => \$mode,
  "itp=s"              => \$itp,
  "t1=s"               => \$t1,
  "t2=s"               => \$t2,  
  "vprog=s"            => \$vprog,
  "dist=s"             => \$dist,
  "curve2offset=s"     => \$curve2offset,
  "curve2proportion=s" => \$curve2proportion,
  "curve2multiplier=s" => \$curve2multiplier,
  "curve2dist=s"       => \$curve2dist,
  "debug"              => \$debug );



# generate the velocity array(s)

my @velocities;
if( "$mode" eq "SIMPLE" )
  {
  @velocities = getvelocities( $ident, $vprog, $dist, $t1, $t2, $itp );
  }
elsif( "$mode" eq "MULTI" )
  {
  my $vprog1 = $vprog;                         # in rotations/sec
  my $dist1 = $dist;                           # in rotations
  my $vprog2 = $vprog1 * $curve2proportion ;   # in rotations/sec
  my $dist2 = $curve2dist;                     # in rotations
  my @velocities1 = getvelocities( $ident, $vprog1, $dist1, $t1, $t2, $itp );
  my @velocities2 = getvelocities( $ident, $vprog2, $dist2, $t1, $t2, $itp );
  my $steps = $#velocities1 + 1;
  my $i;
  for( $i = 0; $i < $steps; $i++ )
    {
    my $velocity1 = $velocities1[$i];
    my $velocity2 = 0;
    if( ( $i >= $curve2offset ) && ( $i < $curve2offset + $#velocities2 ) )
      {
      $velocity2 = $velocities2[$i - $curve2offset]
      }
    push( @velocities, $velocity1 + ( $curve2multiplier * $velocity2 ) );
    }
  }
else
  {
  print "ERROR: unrecognised mode - aborting!\n";
  exit 1;
  }

# now generate the position and acceleration arrays from the velocity array

my @positions = getpositions( $itp, @velocities );
my @accelerations = getaccelerations( $itp, @velocities );



# construct buffer for header file

my $buffer = "";
my $eol = ",";
my $steps = $#velocities + 1;
my $i;
for( $i = 0; $i < $steps; $i++ )
  {
  my $rotations = @positions[$i];
  my $rpm = @velocities[$i] * 60;
  my $duration = $itp;
  if( $i == $steps - 1 ) 
    {
    $eol = "};";
    }
  $buffer = $buffer . "{${rotations},\t${rpm}\t,${duration}}${eol}\n";
  }



# output the header file

open( HDR, ">MotionProfile${ident}.h" );
print HDR "// COLUMN 1 = Position (rotations)\n";
print HDR "// COLUMN 2 = Velocity (rpm)\n";
print HDR "// COLUMN 3 = Duration (ms)\n";
print HDR "const int k${ident}Sz = $steps;\n";
print HDR "const double k${ident}[][3] = {\n";
print HDR $buffer;
close( HDR );



# output the csv file

my $steps = $#velocities + 1;
my $i;
open( CSV, ">MotionProfile${ident}.csv" );
for( $i = 0; $i < $steps; $i++ )
  {
  print CSV "$i,$velocities[$i],$positions[$i],$accelerations[$i]\n";
  }
close( CSV );



exit 0;



# -----------
# subroutines
# -----------

sub getvelocities()
  {
  my ( $ident, $vprog, $dist, $t1, $t2, $itp ) = @_;

  # calculated values

  my $t4 = ( $dist / $vprog ) * 1000;
  debugout( "DEBUG: T4 = $t4 ms\n" );

  my $fl1 = round( $t1 / $itp );
  debugout( "DEBUG: FL1 = $fl1\n" );

  my $fl2 = round( $t2 / $itp );
  debugout( "DEBUG: FL2 = $fl2\n" );

  my $n = $t4 / $itp;
  debugout( "DEBUG: N = $n\n" );

  # now work through steps

  my $step = 1;
  my $steps = 0;
  my $maxsteps = 1000;
  my $previousfilter1sum;
  my $previousvelocity = 0;
  my $previousposition = 0;
  my @filter1sumarray;
  my $oneifzeropttally = 0;
  my $running = 1;
  my $buffer = "";
  my @retvals;
  open( DBGCSV, ">motionprofile.${ident}.debug.csv" ) if( $debug );
  while( $running )
    {

    # COLUMN B FROM SPREADSHEET = STEP
    debugout( "DEBUG: STEP = $step\n" );

    # COLUMN C FROM SPREADSHEET = TIME
    my $time;
    if( $step == 1 )
      {
      $time = 0;
      }
    else
      {
      $time =  ( ( $step - 1 ) * $itp ) / 1000;
      }
    debugout( "DEBUG: TIME = $time\n" );

    # COLUMN D FROM SPREADSHEET = INPUT
    my $input;
    if( $step == 1 )
      {
      $input = 0;
      }
    else
      {
      $input = ( $step < ( $n +2) ) ? 1 : 0;
      }
    debugout( "DEBUG: INPUT = $input\n" );

    # COLUMN E FROM SPREADSHEET = FILTER 1 SUM
    my $filter1sum;
    if( $step == 1 )
      {
      $filter1sum = 0;
      }
    else
      {
      $filter1sum = max( 0, min( 1, ( $previousfilter1sum + ( ( $input == 1 ) ? ( 1 / $fl1 ) : ( -1 / $fl1 ) ) ) ) );
      }
    debugout( "DEBUG: FILTER1SUM = $filter1sum\n" );
    push( @filter1sumarray, $filter1sum );
    $previousfilter1sum = $filter1sum;

    # COLUMN F FROM SPREADSHEET = FILTER 2 SUM
    my $filter2sum;
    if( $step == 1 )
      {
      $filter2sum = 0;
      }
    else
      {
      $filter2sum =sum( subarray( $step, $step - min( $fl2, $step ) + 1, @filter1sumarray ) );
      }

    # COLUMN G FROM SPREADSHEET = ONE IF ZERO PT
    my $oneifzeropt = ( $filter1sum == 0 ? ( $filter2sum == 0 ? 1 : 0 ) : 0 );
    $oneifzeropttally = $oneifzeropttally + $oneifzeropt;

    # COLUMN H FROM SPREADSHEET = INCLUDED
    my $included = $oneifzeropttally <= 2 ? 1 : 0;

    # COLUMN I FROM SPREADSHEET = VELOCITY
    my $velocity;
    if( $step == 1 )
      {
      $velocity = 0;
      }
    else
      {
      $velocity = ( $included ) ? ( ( $filter1sum + $filter2sum ) / ( 1 + $fl2 ) ) * $vprog :  "" ;
      }
    push( @retvals, $velocity );
  
    # COLUMN J FROM SPREADSHEET = POSITION
    my $position;
    if( $step == 1 )
      {
      $position = 0;
      }
    else
      {
      $position = ( $included ) ?  ( ( ( ( $velocity + $previousvelocity) / 2 ) * $itp ) / 1000) + $previousposition : "";
      }

    # COLUMN K FROM SPREADSHEET = ACCELERATION
    my $acceleration;
    if( $step == 1 )
      {
      $acceleration = 0;
      }
    else
      {
      $acceleration = ( $included ) ? ( $velocity - $previousvelocity ) / ( $itp / 1000 ) : "";
      }

    # COLUMN L FROM SPREADSHEET = IS FIRST
    my $isfirst;
    if( $step == 1 )
      {
      $isfirst = 1;
      }
    else
      {
      $isfirst = 0;
      }

    # COLUMN M FROM SPREADSHEET = IS LAST
    my $islast;
    if( $step == 1 )
      {
      $islast = 0;
      }
    else
      {
      $islast = ( $oneifzeropt && $included ) ? 1 : 0;
      }

    if( $step > $maxsteps )
      {
      print "WARNING: exceeded maximum number of steps - profile truncated\n";
      $running = 0;
      }

    if( $islast )
      {
      print "INFO: completed calculation of velocities sucessfully\n";
      $running = 0;
      }

    # ADD SOMETHING TO DEBUG CSV (if necessary)
    print DBGCSV "$step,$time,$input,$filter1sum,$filter2sum,$oneifzeropt,$included,$velocity,$position,$acceleration,$isfirst,$islast\n" if( $debug );

    $previousvelocity = $velocity;
    $previousposition = $position;

    $step++;
    }

  close( DBGCSV ) if( $debug );

  return @retvals;
  }

sub getpositions
  {
  my ( $itp, @velocities ) = @_;
  my @retvals;
  my $previousvelocity = 0;
  my $previousposition = 0;
  my $step = 1;
  foreach( @velocities )
    {
    my $velocity = $_;
    my $position;
    if( $step == 1 )
      {
      $position = 0;
      }
    else
      {
      $position = ( ( ( ( $velocity + $previousvelocity ) / 2 ) * $itp ) / 1000) + $previousposition;
      }
    $previousvelocity = $velocity;
    $previousposition = $position;
    push( @retvals, $position );
    $step++;
    }
  print "INFO: completed calculation of positions sucessfully\n";
  return @retvals;
  }

sub getaccelerations
  {
  my ( $itp, @velocities ) = @_;
  my @retvals;
  my $previousvelocity = 0;
  my $step = 1;
  foreach( @velocities )
    {
    my $velocity = $_;
    my $acceleration;
    if( $step == 1 )
      {
      $acceleration = 0;
      }
    else
      {
      $acceleration = ( $velocity - $previousvelocity ) / ( $itp / 1000 );
      }
    $previousvelocity = $velocity;
    push( @retvals, $acceleration );
    $step++;
    }
  print "INFO: completed calculation of accelerations sucessfully\n";
  return @retvals;
  }

sub debugout()
  {
  print "@_" if( $debug );
  }

sub sum()
  {
  my $sum = 0;
  foreach( @_ )
    { $sum = $sum + $_; }
  return $sum;
  }

sub subarray()
  {
  my ( $first, $last, @array ) = @_;
  my @subset;
  my $element = 1;
  foreach( @array )
    {
    push( @subset, $_ ) if( ( $element <= $first ) && ( $element >= $last ) );
    $element++;
    }
  return @subset;
  }

sub round()
  {
  my ($x, $pow10) = @_;
  my $a = 10 ** $pow10;
  return (int($x/$a+(($x<0)?-0.5:0.5))*$a);
  }

sub min()
  {
  my ( $a, $b ) = @_;
  if( $a < $b )
    { return $a; }
  else
    { return $b; }
  }

sub max()
  {
  my ( $a, $b ) = @_;
  if( $a > $b )
    { return $a; }
  else
    { return $b; }
  }
