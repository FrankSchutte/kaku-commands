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
#include "../libs/NewRemoteReceiver.cpp"

using namespace std;

bool stopWhenCodeSniffed = true;
bool stop = false;

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

  if (stopWhenCodeSniffed)
  {
    stop = true;
  }
}

int main(int argc, char *argv[])
{
  int PIN = 2;

  cout << "Usage: [stopWhenCodeSniffed] [timeout]" << endl;
  cout << "stopWhenCodeSniffed<bool> if set to false sniffing stops when interrupted manually (ctrl + c), defaults to true" << endl;
  
  if(wiringPiSetup() == -1) {
    cout << "wiringPiSetup failed, exiting..." << endl;
    return 0;
  }
  
  if (argc >= 2) stopWhenCodeSniffed = atoi(argv[1]) == 1 || argv[1] == "true";

  NewRemoteReceiver::init(PIN, 2, showCode);
  while (!stop)
  {
    usleep(100);
  }

  exit(0);
}
