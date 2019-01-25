#include <iostream>
#include <chrono>
#include <cstdio>
#include <thread>
#include "ntcore.h"

#include "networktables/NetworkTable.h"

using namespace std;

int main() {
  auto nt = NetworkTable::GetTable("test");
  
  nt->SetClientMode();
  nt->SetIPAddress("10.0.80.35\n");
  
  nt->Initialize();
  std::this_thread::sleep_for(std::chrono::seconds(5));

  while (true) { 
    int i = rand() % 1000 + 1;
    nt->PutNumber("randomvalue", i);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

}
