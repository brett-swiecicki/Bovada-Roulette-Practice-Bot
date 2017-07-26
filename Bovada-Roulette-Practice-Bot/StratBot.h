//Brett Swiecicki
#ifndef STRATBOT_H
#define STRATBOT_H

#include <iomanip>
#include "BotUtilities.h"

using namespace std;

class StratBot {
public:
	StratBot() {
		ShellExecute(NULL, "open", "https://casino.bovada.lv/table-games/european-roulette?mode=practice", NULL, NULL, SW_SHOWMAXIMIZED); //Open Bovada
		Sleep(500);
		SetForegroundWindow(GetConsoleWindow());
		getStratFromUser();
		ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
		openDeveloperTools();
		findHTMLvalues();
		enableQuickSpin();
	}

	void runSims() {
		num_wins = 0;
		num_losses = 0;
		bankroll = getBankroll();
		double strat_stakes_total = 0;
		for (int i = 0; i < (int)strat_stakes.size(); ++i) {
			strat_stakes_total += strat_stakes[i];
		}
		double lower_bound_bankroll = (bankroll - strat_stakes_total);
		double upper_bound_bankroll = (bankroll + strat_stakes_total);
		double bet;
		while (num_sims > 0) {
			int roll_on_strat = 0;
			while ((bankroll > lower_bound_bankroll) && (bankroll < upper_bound_bankroll)) {
				if ((bankroll - strat_stakes[roll_on_strat]) >= lower_bound_bankroll) {
					bet = strat_stakes[roll_on_strat];
				}
				else {
					bet = (bankroll - lower_bound_bankroll);
				}
				placeBet(bet);
				quickSpin();
				double new_bankroll = getBankroll();
				bool new_bankroll_is_correct = false;
				while (new_bankroll_is_correct == false) {
					if (new_bankroll == (bankroll + (bet * 2))) {
						roll_on_strat = 0;
						new_bankroll_is_correct = true;
					}
					else if (new_bankroll == (bankroll - bet)) {
						++roll_on_strat;
						if (roll_on_strat == (int)strat_stakes.size()) {
							roll_on_strat = 0;
						}
						new_bankroll_is_correct = true;
					}
					else {
						new_bankroll = getBankroll();
					}
				}
				bankroll = new_bankroll;
			}
			if (bankroll == lower_bound_bankroll) {
				++num_losses;
			}
			else {
				++num_wins;
			}
			--num_sims;
			if (num_sims > 0) {
				refreshPage();
				bankroll = getBankroll();
			}
		}
	}
	
	void printResults() {
		int total = (num_wins + num_losses);
		double win_percent = ((((double)num_wins) / ((double)total)) * 100.0);
		double loss_percent = ((((double)num_losses) / ((double)total)) * 100.0);
		cout << std::setprecision(5);
		cout << "Number of wins (minimum required bankroll doubled): " << num_wins << ", (" << win_percent << "%)." << endl;
		cout << "Number of losses (minimum required bankroll hit $0.00): " << num_losses << ", (" << loss_percent << "%)." << endl;
		cout << "Predicted ROI: " << (win_percent - loss_percent) << "%" << endl;
	}

private:
	vector<double> strat_stakes;
	double bankroll;
	int num_sims;
	int num_wins;
	int num_losses;

	void getStratFromUser() {
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
		cout << "How many simulations would you like the bot to run? ";
		cin >> num_sims;
		cout << endl;
	}

	double getBankroll() {
		mouseMove(1000, 315); //Click away to allow amount to reset
		leftClick();
		Sleep(125);

		mouseMove(1440, 315); //Double click on bankroll in developer options
		leftClick();
		leftClick();
		Sleep(125);
		copyToClipboard();
		Sleep(250);
		string bankroll_string = getClipboardText();
		if ((bankroll_string.length() < 5) || (bankroll_string.at(bankroll_string.length() - 3) != '.')) { //Make sure a bankroll was read in
			return getBankroll();
		}
		//Format data and return ($1,000.00)
		bankroll_string.erase(0, 1); //1,000.00, erases $
		if (bankroll_string.length() > 6) { // BAD! TODO! Delete commas
			bankroll_string.erase(1, 1); //1000.00, erases ,
		}
		bankroll_string.erase((bankroll_string.length() - 3), 3); //1000, erases .00 PROBLEM!
		return stod(bankroll_string);
	}

	string getBetAmount() {
		mouseMove(1000, 434); //Click away to allow amount to reset
		leftClick();
		Sleep(125);

		mouseMove(1435, 434);
		leftClick();
		leftClick();
		Sleep(125);
		copyToClipboard();
		Sleep(250);
		return getClipboardText();
	}
	
	void quickSpin() {
		mouseMove(835, 748);
		leftClick();
		string betAmount = getBetAmount();
		while (betAmount != "$0") { //Wait for result
			betAmount = getBetAmount();
		}
	}

	void placeBet(double bet) {
		double desiredBet = bet;
		int place500 = (int)(bet / 500.0);
		if (place500 > 0) {
			selectBet500();
			while (place500 > 0) {
				betOnFirstTwelve();
				bet -= 500.0;
				--place500;
			}
		}

		int place100 = (int)(bet / 100.0);
		if (place100 > 0) {
			selectBet100();
			while (place100 > 0) {
				betOnFirstTwelve();
				bet -= 100.0;
				--place100;
			}
		}

		int place25 = (int)(bet / 25.0);
		if (place25 > 0) {
			selectBet25();
			while (place25 > 0) {
				betOnFirstTwelve();
				bet -= 25.0;
				--place25;
			}
		}

		int place5 = (int)(bet / 5.0);
		if (place5 > 0) {
			selectBet5();
			while (place5 > 0) {
				betOnFirstTwelve();
				bet -= 5.0;
				--place5;
			}
		}

		int place1 = (int)(bet);
		if (place1 > 0) {
			selectBet1();
			while (place1 > 0) {
				betOnFirstTwelve();
				bet -= 1.0;
				--place1;
			}
		}
		//Double check the bet before continuing
		string currentBet_str = getBetAmount();
		if (currentBet_str.at(0) == '$') {
			currentBet_str.erase(0, 1);
		}
		double currentBet = stod(currentBet_str);
		if (currentBet != desiredBet) {
			mouseMove(652, 750);
			leftClick();
			Sleep(250);
			placeBet(desiredBet);
		}
	}

	void selectBet1() {
		mouseMove(160, 745);
		leftClick();
		Sleep(250);
	}

	void selectBet5() {
		mouseMove(230, 745);
		leftClick();
		Sleep(250);
	}

	void selectBet25() {
		mouseMove(285, 745);
		leftClick();
		Sleep(250);
	}

	void selectBet100() {
		mouseMove(350, 745);
		leftClick();
		Sleep(250);
	}

	void selectBet500() {
		mouseMove(410, 745);
		leftClick();
		Sleep(250);
	}

	void betOnFirstTwelve() {
		mouseMove(290, 610);
		leftClick();
		Sleep(200);
	}
};

#endif
