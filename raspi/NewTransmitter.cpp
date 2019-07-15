/*
    NewTransmitter.cpp
    Usage: ./NewTransmitter
    by @FrankSchutte to provide a handy RF code sender
 */

#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include <string>
#include "../libs/NewRemoteTransmitter.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    int PIN = 0;

    if (argc <= 3) {
      cout << "Usage: address unit switchTypeText [period]" << endl;
      cout << "address<integer>" << endl;
      cout << "unit<integer>" << endl;
      cout << "switchTypeText<string> options are: off | on | dim" << endl;
      cout << "period<integer> defaults to 269us" << endl;
      cout << "exiting..." << endl;
      return 0;
    }

    if(wiringPiSetup() == -1) {
      cout << "wiringPiSetup failed, exiting..." << endl;
      return 0;
    }

    int address = atoi(argv[1]);
    int unit = atoi(argv[2]);
    string switchTypeText = argv[3];
    int period = 269;
    if (argc >= 5) period = atoi(argv[4]);

    if (switchTypeText != "off" && switchTypeText != "on" && switchTypeText != "dim")
    {
      cout << "Invalid value for switchType argument" << endl;
      cout << "Provided: \"" << switchTypeText << "\"" << endl;
      cout << "Allowed values are off | on | dim" << endl;
      cout << "exiting..." << endl;
      return 0;
    }

    cout << "Sending code:" << endl;
    cout << "Address: " << address;
    cout << " unit: " << unit;
    cout << " " << switchTypeText;
    cout << " period: " << period << "us." << endl;

    NewRemoteTransmitter transmitter(address, PIN, period);
    bool isOn = switchTypeText == "on";
    transmitter.sendUnit(unit, isOn);

    exit(0);
}
