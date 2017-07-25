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

int main() {
	printHeader();
	StratBot myStratBot = StratBot();
	myStratBot.runSims();
	closeBovada();
	Sleep(500);
	ShowWindow(GetConsoleWindow(), SW_RESTORE);
	SetForegroundWindow(GetConsoleWindow());
	myStratBot.printResults();
	cout << "Press ENTER to terminate bot." << endl;
	cin.ignore();
	cin.ignore();
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
	cout << "	You will be betting on 1st 12." << endl;
	cout << endl;
}