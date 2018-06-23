#
# perl script to generate HTML summary document of all Motion Profiles with embedded graph images
#



use strict;



my %profiles;
foreach( glob( "*.png" ) )
  {
  s|^MotionProfile||;
  s|.png$||;
  $profiles{$_}++;
  }



my $html_open = "<html>\n";
my $html_close = "</html>\n";

my $head_open = "<head>\n";
my $head_close = "</head>\n";

my $meta_open = "<meta http-equiv=\"refresh\" content=\"5\">\n";
my $meta_close = "</meta>\n";

my $body_open = "<body>\n";
my $body_close = "</body>\n";

my $font_open = "<font face=\"verdana\">\n";
my $font_close = "</font>\n";

my $table_open = "<table>\n";
my $table_close = "</table>\n";

my $tr_open = "<tr>\n";
my $tr_close = "</tr>\n";

my $td_open = "<td align=\"center\">\n";
my $td_close = "</td>\n";



open( DOC, ">MotionProfile.html" );
print DOC $html_open;
print DOC $head_open;
print DOC $meta_open;
print DOC $meta_close;
print DOC $head_close;
print DOC $body_open;
print DOC $font_open;
print DOC $table_open;
foreach( sort( keys( %profiles ) ) )
  {
  my $profile = $_;
  
  print DOC $tr_open;
  print DOC $td_open;
  print DOC "<h1>Motion Profile: '${profile}'</h1>\n";
  print DOC $td_close;
  print DOC $tr_close;
  
  print DOC $tr_open;
  print DOC $td_open;
  print DOC "<img src=\"MotionProfile${profile}.png\" alt=\"MotionProfile${profile}\">\n";
  print DOC $td_close;
  print DOC $tr_close;
  
  }
print DOC $table_close;
print DOC $font_close;
print DOC $body_close;
print DOC $html_close;
close( DOC );
