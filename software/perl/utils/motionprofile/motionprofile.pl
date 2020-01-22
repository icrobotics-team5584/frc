#
# motion profile generator for postion/velocity/heading/duration
#

use strict;

use XML::Simple;

use Getopt::Long;

my $debug = 0;
GetOptions (
  "debug" => \$debug );

my $config = XMLin("motionprofile.xml", KeyAttr => { profile => 'name', segment => 'id' }, ForceArray => [ 'profile', 'segment' ]);

# use Data::Dumper;
# print Dumper($config);

foreach my $p ( keys %{ $config->{'profiles'}->{'profile'} } )
  {
  my $profilename = $p;
  my $numberofsegmentsinprofile = getsegmentsinprofile( $profilename );
  print "INFO: processing profile: $profilename ($numberofsegmentsinprofile segments detected)\n";
  processprofilesegments( $profilename, $numberofsegmentsinprofile );
  }
exit 0;

sub getsegmentsinprofile
  {
  my ( $profilename ) = @_;
  my $moresegmentsexist = 1;
  my $segmentcounter = 0;
  while( $moresegmentsexist )
    {
    my $foundnext = 0;
    foreach my $s ( keys %{ $config->{'profiles'}->{'profile'}->{$profilename}->{'path'}->{'segment'} } )
      {
      my $segmentid = $s;
      my $nextsegment = $segmentcounter + 1;
      $foundnext++ if( $segmentid == $nextsegment );
      }
    if( $foundnext )
      {
      $segmentcounter++;
      }
    else
      {
      $moresegmentsexist = 0;
      }
    }
  return $segmentcounter;
  }

sub gettotalprofilepathlength
  {
  my ( $profilename ) = @_;
  my $numberofsegments = getsegmentsinprofile( $profilename );
  my $segment = 1;
  my $pathlength = 0;
  while( $segment <= $numberofsegments )
    {
    $pathlength = $pathlength + $config->{'profiles'}->{'profile'}->{$profilename}->{'path'}->{'segment'}->{$segment}->{'length'};
    $segment++;
    }
  return $pathlength;
  }

sub converttorotations
  {
  my ( $distance, $diameter, $units ) = @_;
  print "INFO: units detected: $units\n";
  my $rotations = $distance / ( 3.1415926 * $diameter );
  return $rotations;
  }

sub processprofilesegments
  {
  my ( $ident, $segments ) = @_;
  
  # extract profile direction
  my $dir = $config->{'profiles'}->{'profile'}->{$ident}->{'direction'};
  my $polarity = 0;
  if( "$dir" eq "forwards" )
    {
    $polarity = +1;
    }
  elsif( "$dir" eq "backwards" )
    {
    $polarity  = -1;
    }
  else
    {
    print "ERROR: unsupported direction specified ($dir) - aborting!\n";
    exit 1;
    }
  
  # extract control parameters from config hash
  my $itp = $config->{'controls'}->{'itp'};                        # in msec
  my $t1 = $config->{'controls'}->{'t1'};                          # in msec
  my $t2 = $config->{'controls'}->{'t2'};                          # in msec
  my $vprog = $polarity * $config->{'controls'}->{'velocity'};     # in rotations/sec
  my $sensormode = $config->{'robot'}->{'sensor'}->{'mode'};       # we need to double distances if this is SensorSum mode
  my $dist = $polarity * converttorotations( gettotalprofilepathlength( $ident ), $config->{'robot'}->{'wheels'}->{'diameter'}, $config->{'units'}->{'length'} );
  $dist = $dist * 2 if( "$sensormode" eq "SensorSum" );
  
  # generate the velocity array(s)
  
  my @velocities = getvelocities( $ident, $vprog, $dist, $t1, $t2, $itp );
  
  # now generate the position and acceleration arrays from the velocity array
  
  my @positions = getpositions( $itp, @velocities );
  my @accelerations = getaccelerations( $itp, @velocities );
  
  # now generate the heading array from the positions array
  
  my @headings = getheadings( $ident, @positions );
  
  # construct buffer for header file
  
  my $hbuffer = "";   # buffer for data to go to HTML file
  my $cbuffer = "";   # buffer for data to go to CSV file
  my $gbuffer = "";   # buffer for data to go the GRAPH file
  my $eol = ",";
  my $steps = $#velocities + 1;
  my $i;
  for( $i = 0; $i < $steps; $i++ )
    {
    my $rotations = @positions[$i];
    my $rpm = @velocities[$i] * 60;
    my $vel = @velocities[$i];
    my $heading = @headings[$i];
    my $duration = $itp;
    if( $i == $steps - 1 )
      {
      $eol = "};";
      }
    $hbuffer = $hbuffer . "{${rotations},\t${rpm},\t${heading},\t${duration}}${eol}\n";
    $cbuffer = $cbuffer . "${rotations},${vel},${heading},${duration}\n";
    $gbuffer = $gbuffer . @positions[$i] . "," . @velocities[$i] . "," . @accelerations[$i] . "\n";
    }

  # output the header file
  
  open( HDR, ">MotionProfile${ident}.h" );
  print HDR "#pragma once\n";
  print HDR "// COLUMN 1 = Position (rotations)\n";
  print HDR "// COLUMN 2 = Velocity (rpm)\n";
  print HDR "// COLUMN 3 = Heading (degrees)\n";
  print HDR "// COLUMN 4 = Duration (ms)\n";
  print HDR "const int k${ident}Sz = $steps;\n";
  print HDR "const double k${ident}[][4] = {\n";
  print HDR $hbuffer;
  close( HDR );
  
  # output the csv file
  
  my $steps = $#velocities + 1;
  my $i;
  open( CSV, ">MotionProfile${ident}.csv" );
  print CSV $cbuffer;
  close( CSV );
  
  # output the graph file (this file is in a suitable format for use by the graph generation program)
  
  my $steps = $#velocities + 1;
  my $i;
  open( GRAPH, ">MotionProfile${ident}.graph" );
  for( $i = 0; $i < $steps; $i++ )
    {
    print GRAPH "$i,$velocities[$i],$positions[$i],$accelerations[$i]\n";
    }
  close( GRAPH );
  
  }

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
  my $maxsteps = 2000;
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

sub getheadings()
  {
  my ( $ident, @positions ) = @_;
  my @retvals;
  my $points = $#positions + 1;
  my $segments = getsegmentsinprofile( $ident );
  my $pathlength = gettotalprofilepathlength( $ident );
  print "DEBUG: pathlength: $pathlength\n";
  my $dir = $config->{'profiles'}->{'profile'}->{$ident}->{'direction'};
  if( ( "$dir" ne "forwards" ) && ( "$dir" ne "backwards" ) )
    {
    print "ERROR: bad direction detected ($dir) - aborting!\n";
    exit 1;
    }

  my $s = 1;
  my $pathtally = 0;
  my @segpoints;
  my @waypoints;
  push( @segpoints, 0 );
  push( @waypoints, 0 );
  while( $s <= $segments )
    {
    my $l = $config->{'profiles'}->{'profile'}->{$ident}->{'path'}->{'segment'}->{$s}->{'length'};
    $pathtally = $pathtally + $l;
    push( @segpoints, $pathtally );
    push( @waypoints, int( $points * $pathtally / $pathlength ) );
    $s++;
    }

  print "DEBUG: segpoints: ";
  foreach( @segpoints ) { print ">$_< "; }
  print "\n";

  print "DEBUG: waypoints: ";
  foreach( @waypoints ) { print ">$_< "; }
  print "\n"; 

  my $point = 1;
  my $heading = 0;
  my $previousheading = 0;
  foreach( @positions )
    {
    # determine relevaant segment id
    my $sid = 0;
    while( $point > @waypoints[$sid] )
      {
      $sid++;
      }

    # determine type of segment (straight/turn)
    my $type = $config->{'profiles'}->{'profile'}->{$ident}->{'path'}->{'segment'}->{$sid}->{'type'};

    if( "$type" eq "straight" )
      {
      $heading = $previousheading;
      }
    elsif( "$type" eq "turn" )
      {
      # determine turn direction (left/right)
      my $turn = $config->{'profiles'}->{'profile'}->{$ident}->{'path'}->{'segment'}->{$sid}->{'turn'};
      # determine angle
      my $angle = $config->{'profiles'}->{'profile'}->{$ident}->{'path'}->{'segment'}->{$sid}->{'angle'};
      # calculate heading
      if( "$turn" eq "left" )
        {
        if( "$dir" eq "forwards" )
          {
          $heading = 1.0 * $angle * ($point-@waypoints[$sid-1]) / (@waypoints[$sid]-@waypoints[$sid-1]);
          }
         elsif( "$dir" eq "backwards" )
          {
          $heading = -1.0 * $angle * ($point-@waypoints[$sid]) / (@waypoints[$sid]-@waypoints[$sid-1]);
          }
         else
          {
          print "ERROR: bad direction detected ($dir) - aborting!\n";
          exit 1;
          }
        }
      elsif( "$turn" eq "right" )
        {
        if( "$dir" eq "forwards" )
          {
          $heading = -1.0 * $angle * ($point-@waypoints[$sid]) / (@waypoints[$sid]-@waypoints[$sid-1]);
          }
        elsif( "$dir" eq "backwards" )
          {
          $heading = 1.0 * $angle * ($point-@waypoints[$sid-1]) / (@waypoints[$sid]-@waypoints[$sid-1]);
          }
         else
          {
          print "ERROR: bad direction detected ($dir) - aborting!\n";
          exit 1;
          }
        }
      else
        {
        print "ERROR: bad segment turn detected ($turn) - aborting!\n";
        exit 1;
        }
      $previousheading = $heading;
      }
    else
      {
      print "ERROR: bad segment type detected ($type) - aborting!\n";
      exit 1;
      }

    push( @retvals, $heading );
    $point++;
    }
  print "INFO: completed calculation of $points headings sucessfully\n";
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
