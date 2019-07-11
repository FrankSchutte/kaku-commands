/*
  NewRFSniffer
  Usage: ./NewRFSniffer
  [] = optional
  Hacked from:
    https://bitbucket.org/fuzzillogic/433mhzforarduino/src/default/
    https://github.com/ninjablocks/433Utils/blob/master/RPi_utils/RFSniffer.cpp
    https://github.com/chaanstra/raspKaku
  by @FrankSchutte to provide a handy RF code sniffer
*/

#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../libs/NewRemoteReceiver.h"

int main(int argc, char *argv[])
{
  int PIN = 2;
  
  if(wiringPiSetup() == -1) {
    printf("wiringPiSetup failed, exiting...");
    return 0;
  }

  void showCode(NewRemoteCode receivedCode)
  {
    printf("Address: " + receivedCode.address);

    if (receivedCode.groupBit)
    {
      printf(", group");
    }
    else
    {
      printf(", unit: " + receivedCode.unit);
    }

    switch (receivedCode.switchType)
    {
      case NewRemoteCode::off:
      printf(", off");
        break;
      case NewRemoteCode::on:
        printf(", on");
        break;
      case NewRemoteCode::dom:
        printf(", dim");
        break;
    }

    if (receivedCode.dimLevelPresent)
    {
      printf(", dim level: " + receivedCode.dimLevel;
    }

    printf(", period: " + receivedCode.period + "us");
    fflush(stdout);
  }

  NewRemoteReceiver::init(PIN, 2, showCode);

  while (1)
  {

  }

  usleep(100);
}
exit(0);
