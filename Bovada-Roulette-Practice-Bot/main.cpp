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

using namespace std;

void printHeader();
void getStratFromUser(vector<double>& strat_stakes);
void closeBovada();
void openDeveloperTools();
void findHTMLvalues();
void primeChromeForObjectSelction();
void mouseMove(int x, int y);
void leftClick();

int main() {
	vector<double> strat_stakes;

	printHeader();
	getStratFromUser(strat_stakes);

	//Open Bovada
	ShellExecute(NULL, "open", "https://casino.bovada.lv/table-games/european-roulette?mode=practice", NULL, NULL, SW_SHOWMAXIMIZED);
	Sleep(7000); // Sleep to let page load. Hopefully there is a better way to do this!
	openDeveloperTools();
	Sleep(3000); // Sleep to let developer tools open
	findHTMLvalues();
	Sleep(10000);
	
	closeBovada();
	cout << "Press ENTER to terminate bot." << endl;
	cin.get();
}

void printHeader() {
	cout << "You are now running the Bovada Practice Mode Bot." << endl;
	cout << "Currently, this bot assumes the following: " << endl;
	cout << "	OS: Windows 10 Home" << endl;
	cout << "	Default Browser: Google Chrome 59.0.3071.115" << endl;
	cout << "	Bookmarks bar is shown." << endl;
	cout << "	Resolution: 1600 x 1900" << endl;
	cout << "	Screen size: 17.3\"" << endl;
	cout << "	https://casino.bovada.lv/table-games/european-roulette?mode=practice" << endl;
	cout << endl;
}

void getStratFromUser(vector<double>& strat_stakes) {
	int total_rolls;
	cout << "Enter how many rolls your strategy can have before breaking: ";
	cin >> total_rolls;
	strat_stakes.resize(total_rolls);
	cout << "Please enter each bet in order starting with the first: " << endl;
	double input_bet;
	for (int i = 0; i < total_rolls; ++i) {
		cin >> input_bet;
		strat_stakes[i] = input_bet;
	}
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

void openDeveloperTools() { // CTRL + Shift + I
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press the "CTRL" key
	ip.ki.wVk = VK_CONTROL; // virtual-key code for the "CTRL" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	//Press the "Shift" key
	ip.ki.wVk = VK_SHIFT;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Press the "I" key
	ip.ki.wVk = 'I';
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "I" key
	ip.ki.wVk = 'I';
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "Shift" key
	ip.ki.wVk = VK_SHIFT;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "CTRL" key
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

}

void findHTMLvalues() {
	primeChromeForObjectSelction();
	Sleep(2000);
	mouseMove(80, 374);
	leftClick();
	Sleep(2000);
	primeChromeForObjectSelction();
	Sleep(2000);
	mouseMove(230,374);
	leftClick();
}

void primeChromeForObjectSelction() { // CTRL + Shift + C (prime Chrome to select HTML objects)
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press the "CTRL" key
	ip.ki.wVk = VK_CONTROL; // virtual-key code for the "CTRL" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	//Press the "Shift" key
	ip.ki.wVk = VK_SHIFT;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Press the "C" key
	ip.ki.wVk = 'C';
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "C" key
	ip.ki.wVk = 'C';
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "Shift" key
	ip.ki.wVk = VK_SHIFT;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "CTRL" key
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
}

void mouseMove(int x, int y) {
	double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
	double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
	double fx = x*(65535.0f / fScreenWidth);
	double fy = y*(65535.0f / fScreenHeight);
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = (long)fx;
	Input.mi.dy = (long)fy;
	::SendInput(1, &Input, sizeof(INPUT));
}

void leftClick() {
	INPUT    Input = { 0 };
	// left down 
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	// left up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}