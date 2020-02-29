#!/usr/bin/perl

use strict;
use Time::HiRes qw( usleep );

my $ctlfile = $0;
$ctlfile =~ s|.pl$|.ctl|;

my $video_src_1 = "v4l2src device=/dev/video0";
my $video_src_2 = "v4l2src device=/dev/video1";
my $video_src_3 = "v4l2src device=/dev/video2";
my $slot_A_port = 1181;
my $slot_B_port = 1182;
my $slot_C_port = 1183;
# my $slot_A_port = 5801;
# my $slot_B_port = 5802;
# my $slot_C_port = 5803;
# my $client_ip_address = "192.168.0.126";
# my $client_ip_address = "10.55.84.164";
my $client_ip_address = "10.55.84.226";

my $control = 1;
my $previous = 1;
switch($control);
my $running = 1;
while( $running )
  {
  open( CTL, "<$ctlfile" );
  $control = <CTL>;
  close( CTL );
  next unless( ( "$control" eq "1" ) || ( "$control" eq "2" ) || ( "$control" eq "3" ) );
  if( "$control" ne "$previous" )
    {
    switch($control);
    $previous = $control;
    }
  usleep(100);
  }

exit 0;

sub switch
  {
  my ( $control ) = @_;
  if( "$control" eq "1" )
    {
    relaunch( $video_src_1, $client_ip_address, $slot_A_port, "VIDEO 1", 160, 120 );
    relaunch( $video_src_2, $client_ip_address, $slot_B_port, "VIDEO 2", 160, 120 );
    relaunch( $video_src_3, $client_ip_address, $slot_C_port, "VIDEO 3", 160, 120 );
    }
  elsif( "$control" eq "2" )
    {
    relaunch( $video_src_2, $client_ip_address, $slot_A_port, "VIDEO 2", 160, 120 );
    relaunch( $video_src_1, $client_ip_address, $slot_B_port, "VIDEO 1", 160, 120 );
    relaunch( $video_src_3, $client_ip_address, $slot_C_port, "VIDEO 3", 160, 120 );
    }
  elsif( "$control" eq "3" )
    {
    relaunch( $video_src_3, $client_ip_address, $slot_A_port, "VIDEO 3", 160, 120 );
    relaunch( $video_src_2, $client_ip_address, $slot_B_port, "VIDEO 2", 160, 120 );
    relaunch( $video_src_1, $client_ip_address, $slot_C_port, "VIDEO 1", 160, 120 );
    }
  else
    {
    print "WARNING: ignoring unexpected control signal ($control).\n";
    }

  }

sub relaunch
  {
  my ( $source, $ipaddr, $port, $ident, $width, $height ) = @_;
  # terminate any existing stream on this port
  foreach( `ps -ef | grep gst-launch-1.0 2>&1` )
    {
    if( /$port/ )
      {
      my ( $user, $pid, $therest ) = split( /\s+/, $_ );
      `kill $pid`;
      }
    }
  # launch new instance on the port
  my $cmd = "gst-launch-1.0 ${source} ! textoverlay text=\"${ident}\" valignment=2 halignment=1 font-desc=\"sans 72\" ! jpegenc ! image/jpeg,width=${width},height=${height} ! progressreport ! rtpjpegpay ! udpsink host=${ipaddr} port=${port} > /tmp/ic_gstserver.${port}.log";
  `$cmd 2>&1 &`;
  }
