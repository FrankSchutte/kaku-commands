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

bool codeSniffed = false;

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

  codeSniffed = true;
}

int main(int argc, char *argv[])
{
  int PIN = 2;

  cout << "Usage: [stopWhenCodeSniffed] [timeout]" << endl;
  cout << "stopWhenCodeSniffed<bool> if set to false sniffing stops when interrupted manually (ctrl + c), defaults to true" << endl;
  cout << "timeout<int> specify in seconds. Only if argument stopWhenCodeSniffed is set to true the timeout is used, defaults to 10" << endl;
  
  if(wiringPiSetup() == -1) {
    cout << "wiringPiSetup failed, exiting..." << endl;
    return 0;
  }

  bool stopWhenCodeSniffed = true;
  if (argc >= 2) stopWhenCodeSniffed = argv[1];
  int timeout = 10;
  if (argc >= 3) timeout = atoi(argv[2]);
  timeout *= 1000;

  NewRemoteReceiver::init(PIN, 2, showCode);

  clock_t start = clock();
  cout << "start: " << start << endl;
  cout << "timeout: " << timeout << endl;

  while (!stopWhenCodeSniffed || (!codeSniffed || clock() - start < timeout))
  {
    usleep(100);
  }

  exit(0);
}
