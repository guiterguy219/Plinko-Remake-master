#include "pch.h"
// Nathan Stucki, Section 6, stookler@yahoo.com yee danosaur
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

int UserInput(int userInput) {

	const int IGNORE_VAL = 1000;

	while (cin.fail() || userInput < 0 || userInput > 8) {
		cin.clear();
		cin.ignore(IGNORE_VAL, '\n');
		cout << "Invalid slot." << endl;
		cout << "Which slot do you want to drop the chip in (0-8)?" << endl << endl;
		cin >> userInput;
	}
	return userInput;
}
int UserInput2(int userInput) {

	const int IGNORE_VAL = 1000;

	while (cin.fail() || userInput < 1) {
		cin.clear();
		cin.ignore(IGNORE_VAL, '\n');
		cout << "Invalid number of chips." << endl << endl;
		cout << "How many chips do you want to drop (>0)?" << endl << endl;
		cin >> userInput;
	}
	return userInput;
}
int SwitchInput(int userInput) {

	const int IGNORE_VAL = 1000;

	while (cin.fail() || userInput < 0) {
		cin.clear();
		cin.ignore(IGNORE_VAL, '\n');
		cout << "Invalid selection. Enter 4 to see options." << endl << endl;
		cout << "Enter your selection now:" << endl << endl;
		cin >> userInput;
	}
	return userInput;
}
int UserInput3(int userInput) {

	const int IGNORE_VAL = 1000;

	while (cin.fail() || userInput < 0) {
		cin.clear();
		cin.ignore(IGNORE_VAL, '\n');
		cout << "Invalid slot" << endl << endl;
		cout << "Enter your selection now:" << endl << endl;
		cin >> userInput;
	}
	return userInput;
}

double ComputeWinnings(int slot) {

	double WINNINGS[9];

	WINNINGS[0] = 100.00;
	WINNINGS[1] = 500.00;
	WINNINGS[2] = 1000.00;
	WINNINGS[3] = 0.00;
	WINNINGS[4] = 10000.00;
	WINNINGS[5] = 0.00;
	WINNINGS[6] = 1000.00;
	WINNINGS[7] = 500.00;
	WINNINGS[8] = 100.00;

	return WINNINGS[slot];
}

double* SingleChipInsert(double slotNum) {

	

	static double path[13];
	double newSlot = 0.0;

	path[0] = slotNum;
	newSlot = slotNum;

	for (int i = 1; i < 13; ++i) {
		if (newSlot >= 0.5 && newSlot <= 7.5) {
			int randNum = 0;
			randNum = rand() % 2;
			if (randNum == 0) {
				newSlot -= 0.5;
			}
			else if (randNum == 1) {
				newSlot += 0.5;
			}
		}
		else if (newSlot == 0) {
			newSlot += 0.5;
		}
		else if (newSlot == 8) {
			newSlot -= 0.5;
		}
		
		path[i] = newSlot;
	}

	return path;
}

int main() {
	int userInput= 0;
	int userInput2 = 0;
	int randNum = 0;
	int numChips = 0;
	double userInput3 = 0.0;
	double totalWinnings = 0.0;
	double avgWinnings = 0.0;
	const int RANDOM_SEED = 42;
	const int IGNORE_VAL = 1000;
	//double WINNINGS[8];
	bool select = true;
	double *p; //pointer

	srand(RANDOM_SEED);

	cout << "Welcome to the Plinko simulator! Enter 4 to see options." << endl << endl;

	do {
		cout << "Enter your selection now:" << endl << endl;
		cin >> userInput;
		userInput = SwitchInput(userInput);

		

		int i = 0;
		switch (userInput) {
		case 1:
			cout << "*** Drop a single chip ***" << endl;
			cout << "Which slot do you want to drop the chip in (0-8)?" << endl << endl;
			cin >> userInput2;
			userInput2 = UserInput(userInput2);
			userInput3 = userInput2;
			if ((userInput2 > -1) && (userInput2 < 9)) {
				p =	SingleChipInsert(userInput3);

				//print out path
				cout << "*** Dropping chip into slot " << userInput2 << " ***" << endl;
				cout << "Path: [";
				for (int i = 0; i < 13; i++) {
					cout << fixed << setprecision(1) << *(p + i);
					if (i < 12) { cout << ", "; }
					else if (i == 12) { cout << "]" << endl; }
				}

				cout << "Winnings: $" << fixed << setprecision(2) << ComputeWinnings(*(p + 12)) << endl;
			}

			else {
				cout << "Invalid slot." << endl;
				select = true;
			}

			break;
			//Part 3 - multiple chip drop
		case 2:
			cout << "*** Drop multiple chips ***" << endl << endl;
			cout << "How many chips do you want to drop (>0)?" << endl << endl;
			cin >> numChips;
			numChips = UserInput2(numChips);
				cout << "Which slot do you want to drop the chip in (0-8)?" << endl;
				cin >> userInput2;
				userInput2 = UserInput(userInput2);
				userInput3 = userInput2;
				if ((userInput3 < 0) || (userInput3 > 8)) {
					cout << "Invalid slot." << endl;
				}
				else {
					for (i = 0; i < numChips; i++) {
						p = SingleChipInsert(userInput3);
						totalWinnings += ComputeWinnings(*(p + 12));
					}
				}
				
					cout << "Total winnings on " << numChips << " chips: $" << fixed << setprecision(2) << totalWinnings << endl;
					avgWinnings = totalWinnings / numChips;
					cout << "Average winnings per chip: $" << avgWinnings << endl;
					totalWinnings = 0.00;
					avgWinnings = 0.00;
			select = true;
			break;
		case 3:
			cout << "*** Sequentially drop multiple chips ***" << endl << endl;
			cout << "How many chips do you want to drop (>0)?" << endl << endl;
			cin >> numChips;
			numChips = UserInput2(numChips);

			if (numChips < 1) {
				cout << "Invalid number of chips." << endl;
			}
			for (i = 0; i < 9; i++) {
				for (int j = 0; j < numChips; j++) {
					p = SingleChipInsert(userInput3);
					totalWinnings += ComputeWinnings(*(p + 12));
				}
				cout << "Total winnings on " << numChips << " chips in slot " << i << ": $" << fixed << setprecision(2) << totalWinnings << endl;
				avgWinnings = totalWinnings / numChips;
				cout << "Average winnings per chip: $" << avgWinnings << endl << endl;
			}
			
			select = true;
			break;
		case 4:
			cout << "Menu: Please select one of the following options:" << endl << endl;
			cout << "1 - Drop a single chip into one slot" << endl;
			cout << "2 - Drop multiple chips into one slot" << endl;
			cout << "3 - Drop multiple chips into each slot" << endl;
			cout << "4 - Show the options menu" << endl;
			cout << "5 - Quit the program" << endl << endl;
			select = true;
			break;
		case 5:
			select = false;
			cout << "Goodbye!" << endl;
			break;
		default:
			cout << "Invalid selection. Enter 4 to see options." << endl << endl;
			select = true;
			break;
		}
	} while (select);

	return 0;
}
