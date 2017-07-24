// Brett Swiecicki
// Project Started: 7/19/2017
/*
Description:
Program automatically runs a user defined roulette strategy on Bovada in practice mode
to confirm effectiveness (assuming practice mode runs identical to the real money mode).
Effectiveness is determined by counting how many times the minimum required bankroll for
the strategy doubles up or busts.
*/

#include <iostream>
#include <string>
#include <vector>
//#define WINVER 0x0500
#include <windows.h>

#include "BotUtilities.h"
#include "StratBot.h"

using namespace std;

void printHeader();
void closeBovada();

int main() {
	printHeader();
	StratBot myStratBot = StratBot();
	myStratBot.runSims();
	myStratBot.printResults();
	closeBovada();
	cout << "Press ENTER to terminate bot." << endl;
	cin.get();
}

void printHeader() {
	cout << "You are now running the Bovada Practice Mode Bot." << endl;
	cout << endl;
	cout << "Currently, this bot assumes the following: " << endl;
	cout << "	OS: Windows 10 Home" << endl;
	cout << "	Default Browser: Google Chrome 59.0.3071.115" << endl;
	cout << "	Bookmarks bar is shown." << endl;
	cout << "	Resolution: 1600 x 1900" << endl;
	cout << "	Screen size: 17.3\"" << endl;
	cout << "	https://casino.bovada.lv/table-games/european-roulette?mode=practice" << endl;
	cout << endl;
}

void closeBovada() { //CTRL + w
	// Create a generic keyboard event structure
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press the "CTRL" key
	ip.ki.wVk = VK_CONTROL; // virtual-key code for the "CTRL" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Press the "W" key
	ip.ki.wVk = 'W';
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "W" key
	ip.ki.wVk = 'W';
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "CTRL" key
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
}