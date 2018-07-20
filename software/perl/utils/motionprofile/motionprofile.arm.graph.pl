use strict;
use warnings;
 
use GD::Graph::lines;
use GD::Graph::Data;
use Getopt::Long;

my $ident = "NEW.SAMPLE";

GetOptions (
  "ident=s"            => \$ident
  );



my @points;
open( GRAPH, "<MotionProfile${ident}.graph" );
while( <GRAPH> )
  {
  my @record = split( ",", $_ );
  my $step = $record[0];
  my $velocity = $record[1];
  my $position = $record[2];
  my $acceleration = $record[3];
  my @newrecord = [ $step, $position, $velocity, $acceleration ];
  push( @points, @newrecord );
  }
close( GRAPH );

# now need to transpose matrix before we input to the graph object ...
my @transposedpoints;
for my $aref (@points)
  {
  my $i = 0;
  push @{$transposedpoints[$i++]}, $_ for @$aref;
  }

# my $data = GD::Graph::Data->new([
#     [1,2,3,4,5,6,7,8,9],
#     [1,2,5,6,3,1.5,1,3,4],
#     [2,8,4,3,2,4.5,5,9,1],
#     [3,4,6,2,2,4.5,8,4,2],
# ]) or die GD::Graph::Data->error;
 
my $data = GD::Graph::Data->new() or die GD::Graph::Data->error;
$data->copy_from(\@transposedpoints);

my @legend_keys = qw( Position Velocity Acceleration );
 
my $graph = GD::Graph::lines->new;
 
$graph->set( 
    x_label         => 'Steps',
    y_label         => 'Position/Velocity/Acceleration',
    title           => 'Motion Profile',

    legend_placement=> 'RC',
    line_width      => 1,

    y_min_value     => -3,
    y_max_value     => +3,
    y_tick_number   => 12,
    #y_label_skip    => 3,
 
    #x_labels_vertical => 1,
    x_tick_number   => 10,
    #x_label_skip    => 3,
 
    #bar_spacing     => 10,
    #shadow_depth    => 4,
    #shadowclr       => 'dred',
 
    transparent     => 1,
) or die $graph->error;

$graph->set_legend(@legend_keys);
 
$graph->plot($data) or die $graph->error;
 
my $file = "MotionProfile${ident}.png";
open(my $out, '>', $file) or die "Cannot open '$file' for write: $!";
binmode $out;
print $out $graph->gd->png;
close $out;
