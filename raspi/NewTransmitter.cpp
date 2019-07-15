/*
    NewTransmitter.cpp
    Usage: ./NewTransmitter
    by @FrankSchutte to provide a handy RF code sender
 */

#include <wiringPi.h>
#include <../libs/NewRemoteTransmitter.cpp>

int main(int argc, char *argv[])
{
    int PIN = 0;

    if (argc <= 5) {
      cout << "address unit switchType [period]" << endl;
    }

    if(wiringPiSetup() == -1) {
      cout << "wiringPiSetup failed, exiting..." << endl;
      return 0;
    }

    int address = atoi(argv[1]);
    int unit = atoi(argv[2]);
    int switchType = atoi(argv[3]);
    int period = 269;
    if (argc >= 4) period = argv[4];

    cout << "Received commands:" << endl;
    cout << "Address: " << address;
    cout << " unit: " << unit;
    switch (switchType)
    {
      case 0:
        cout << " off";
        break;
      case 1:
        cout << " on";
        break;
      case 2:
        cout << " dim";
        break;
    }
    cout << " period:" << receivedCode.period << "us." << endl;

    NewRemoteTransmitter transmitter(address, 11, period);
    bool isOn = switchType == 1;
    transmitter.sendUnit(unit, isOn);
}