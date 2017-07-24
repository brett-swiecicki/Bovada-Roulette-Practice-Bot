//Brett Swiecicki
#ifndef STRATBOT_H
#define STRATBOT_H

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
		results_pair.first = 0;
		results_pair.second = 0;
		bankroll = getBankroll();
		while (num_sims > 0) {

			--num_sims;
		}
	}
	
	void printResults() {

	}

private:
	vector<double> strat_stakes;
	pair<int, int> results_pair; //.first = wins, .second = losses
	double bankroll;
	int num_sims;

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
	}

	double getBankroll() {
		mouseMove(1431, 346); //Double click on bankroll in developer options
		leftClick();
		leftClick();
		copyToClipboard();
		string bankroll_string = getClipboardText();
		//Format data and return ($1,000.00)
		bankroll_string.erase(0, 1); //1,000.00, erases $
		bankroll_string.erase(1, 1); //1000.00, erases ,
		bankroll_string.erase((bankroll_string.length() - 3), 3); //1000, erases .00
		return stod(bankroll_string);
	}

	void makeBet(int bet) {

	}

	void selectBet1() {

	}

	void selectBet5() {

	}

	void selectBet25() {

	}

	void selectBet100() {

	}

	void selectBet500() {

	}

	void betOnFirstTwelve() {

	}
};

#endif

/*
pair<int, int> hergieSim() {
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 engine(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_int_distribution<> dist(0, (board_size - 1));

		pair<int, int> return_pair;
		int num_wins = 0;
		int num_losses = 0;
		double bankroll = 0.0;
		for (int i = 0; i < (int)strat_stakes.size(); ++i) {
			bankroll += strat_stakes[i];
		}
		double dynamic_bankroll;
		double bet;
		int sim_count = 0;
		while (sim_count < total_sims) {
			dynamic_bankroll = bankroll; //reset the bankroll amount to run the whole strat
			int roll_on_strat = 0;
			while ((dynamic_bankroll > 0.0) && (dynamic_bankroll < (bankroll * 2))) {
				//int random_num = (rand() % board_size); // random_num in the range 0 to E 37 or A 38
				int random_num = dist(engine);
				if (strat_stakes[roll_on_strat] <= dynamic_bankroll) { //Can you even make the bet?
					bet = strat_stakes[roll_on_strat];
					dynamic_bankroll -= bet;
				}
				else {
					bet = bankroll;
					dynamic_bankroll -= bet;
				}
				if (random_num < board_hits) { //HIT!
					dynamic_bankroll += ((payout_factor + 1) * bet);
					roll_on_strat = 0;
				}
				else { //MISS!
					++roll_on_strat;
					if (roll_on_strat == (int)strat_stakes.size()) {
						//Hit the end of the strat? What do we do? Go back to first roll?
						roll_on_strat = 0;
					}
				}
			} //End of inner while loop (actual simulations)
			if (dynamic_bankroll <= 0.0) {
				++num_losses;
			}
			else {
				++num_wins;
			}
			++sim_count;
		}
		return_pair.first = num_wins;
		return_pair.second = num_losses;
		return return_pair;
	}
*/
