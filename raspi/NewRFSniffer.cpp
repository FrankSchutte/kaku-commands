/*
  NewRFSniffer.cpp
  Usage: ./NewRFSniffer
  [] = optional
  Hacked from:
    https://bitbucket.org/fuzzillogic/433mhzforarduino/src/default/
    https://github.com/ninjablocks/433Utils/blob/master/RPi_utils/RFSniffer.cpp
    https://github.com/chaanstra/raspKaku
  by @FrankSchutte to provide a handy RF code sniffer
*/

#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include <cstdio>
#include <ctime>
#include "../libs/NewRemoteReceiver.cpp"

using namespace std;

void showCode(NewRemoteCode receivedCode)
{
  cout << "Address: " << receivedCode.address;

  if (receivedCode.groupBit)
  {
    cout << " group";
  }
  else
  {
    cout << " unit: " << receivedCode.unit;
  }

  switch (receivedCode.switchType)
  {
    case NewRemoteCode::off:
      cout << " off";
      break;
    case NewRemoteCode::on:
      cout << " on";
      break;
    case NewRemoteCode::dim:
      cout << " dim";
      break;
  }

  if (receivedCode.dimLevelPresent)
  {
    cout << " dim level: " << receivedCode.dimLevel;
  }

  cout << " period: " << receivedCode.period << "us." << endl;

  exit(0);
}

int main(int argc, char *argv[])
{
  int PIN = 2;
  
  if(wiringPiSetup() == -1) {
    cout << "wiringPiSetup failed, exiting..." << endl;
    return 0;
  }

  int timeout = 10000;
  if (argc >= 2) timeout = atoi(argv[1]);

  NewRemoteReceiver::init(PIN, 2, showCode);

  clock_t start = clock();

  while (clock() - start < timeout)
  {
    usleep(100);
  }

  exit(0);
}
