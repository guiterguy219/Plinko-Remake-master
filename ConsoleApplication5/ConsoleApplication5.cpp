#include "pch.h"
// Nathan Stucki, Section 6, stookler@yahoo.com
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

//RETURNS WINNINGS AMOUNT
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

//CREATES A PATH FOR A SINGLE CHIP RETURNING A POINTER TO AN ARRAY
double* SingleChipInsert(double slotNum) {

	int randNum = 0;

	static double path[13];

	path[0] = slotNum;

	for (int i = 1; i < 13; ++i) {

		if (slotNum >= 0.5 && slotNum <= 7.5) {
			randNum = rand() % 2;
			if (randNum == 0) {
				slotNum -= 0.5;
			}
			else if (randNum == 1) {
				slotNum += 0.5;
			}
		}
		else if (slotNum == 0) {
			slotNum += 0.5;
		}
		else if (slotNum == 8) {
			slotNum -= 0.5;
		}
		
		path[i] = slotNum;
	}

	return path;
}

int main() {
	string userInputString;
	int userInput;
	string userInput2;
	int randNum = 0;
	int numChips = 0;
	double userInput3 = 0.0;
	double totalWinnings = 0.0;
	double avgWinnings = 0.0;
	const int RANDOM_SEED = 42;
	bool select = true;
	double *p; //pointer

	srand(RANDOM_SEED);

	cout << "Welcome to the Plinko simulator! Enter 3 to see options." << endl << endl;

	//ASKS FOR SELECTION AND EXECUTES DIFFERENT FUNCTIONS UNTIL USER QUITS
	do {
		cout << "Enter your selection now:" << endl << endl;

		//receives user string
		getline(cin, userInputString);

		//catch invalid input
		try { userInput = stoi(userInputString); }
		catch (...) {
			cout << endl << "Invalid input." << endl << endl;
			select = true;
			continue;
		}

		switch (userInput) {
//SINGLE CHIP DROP
		case 1:
			cout << "*** Drop a single chip ***" << endl;
			cout << "Which slot do you want to drop the chip in (0-8)?" << endl << endl;

			//receives user string
			getline(cin, userInput2);

			//catch invalid input
			try { userInput3 = stod(userInput2); }
			catch (...) {
				cout << endl << "Invalid input." << endl << endl;
				select = true;
				break;
			}

			if ((userInput3 > -1) && (userInput3 < 9)) {
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
//MULTIPLE CHIP DROP
		case 2:
			cout << "*** Drop multiple chips ***" << endl;
			cout << "How many chips do you want to drop (>0)?" << endl;

			//receives user string
			getline(cin, userInputString);

			//catch invalid input
			try { numChips = stoi(userInputString); }
			catch (...) {
				cout << endl << "Invalid input." << endl << endl;
				select = true;
				break;
			}

			if (numChips > 1) {
				cout << endl << "Which slot do you want to drop the chip in (0-8)?" << endl;

				//recieves user string
				getline(cin, userInput2);

				//catch invalid input
				try { userInput3 = stod(userInput2); }
				catch(...) {
					cout << endl << "Invalid input." << endl << endl;
					select = true;
					break;
				}

				if ((userInput3 >= 0) && (userInput3 <= 8)) {
					for (int i = 0; i < numChips; ++i) {
						p = SingleChipInsert(userInput3);

						totalWinnings += ComputeWinnings(*(p + 12));
					}

					cout << "Total winnings on " << numChips << " chips: $" << fixed << setprecision(2) << totalWinnings << endl;
					avgWinnings = totalWinnings / numChips;
					cout << "Average winnings per chip: $" << avgWinnings << endl;
					totalWinnings = 0.00;
					avgWinnings = 0.00;
				}
				else {
					cout << "Invalid slot." << endl;
				}
			}
			else {
				cout << "Invalid number of chips." << endl;
			}
			select = true;
			break;
//DISPLAY MENU
		case 3:
			cout << "Menu: Please select one of the following options:" << endl << endl;
			cout << "1 - Drop a single chip into one slot" << endl;
			cout << "2 - Drop multiple chips into one slot" << endl;
			cout << "3 - Show the options menu" << endl;
			cout << "4 - Quit the program" << endl << endl;
			select = true;
			break;
//QUIT
		case 4:
			select = false;
			cout << "Goodbye!" << endl;
			break;
		default:
			cout << "Invalid selection. Enter 3 to see options." << endl << endl;
			select = true;
			break;
		}
	} while (select);

	return 0;
}

