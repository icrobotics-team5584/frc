#include <iostream>
#include <fstream>

#include "ntcore.h"

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

// #include "string.h"

using namespace std;

int debug = 0;

int main( int argc, char *argv[] )
{

  // handle command line arguments
  if( ( argc > 1 ) && ( strcmp( argv[1], "--debug" ) == 0 ) )
    debug = 1;

  // setup network tables connection
  nt::NetworkTableInstance ntinst = nt::NetworkTableInstance::GetDefault();
  std::shared_ptr<nt::NetworkTable> nt;
  nt = ntinst.GetTable("JETSON");
  ntinst.StartClientTeam(5584);

  // set starting camera configuration
  nt->PutNumber("Cam 0", 1);

  for (;;)
  {

    // get data from network tables
    int control = nt->GetNumber("Cam 0", 0);

    // output to control file
    ofstream ctlfile("ic_gstserver.ctl");
    ctlfile << control;
    ctlfile.close();
  }

}
