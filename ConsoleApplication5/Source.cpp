#include "pch.h"
// Nathan Stucki, Section 6, stookler@yahoo.com
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main1() {
	bool seedAgain = true;
	bool loopAgain = true;
	char userInput;

	while (loopAgain) {
		if (seedAgain) {
			srand(42);
		}

		for (int i = 0; i < 10; i++) {
			cout << rand() << endl;
		}

		cout << endl << "Loop again? (y/n): ";
		cin >> userInput;
		if (userInput == 'n') {
			loopAgain = false;
		}
		cout << endl;

		cout << endl << "Seed again? (y/n): ";
		cin >> userInput;
		if (userInput == 'n') {
			seedAgain = false;
		}
		else {
			seedAgain = true;
		}
		cout << endl;
	}

	return 0;
}