#include <iostream>
#include <string>
using namespace std;

class InputHandler {
	public:

	int handleUserInput() {
		string userInput;
		while (true) {
			cout << "Enter your option: ";
			cin >> userInput;
			cout << endl;

			try {
				int number = stoi(userInput);
				return number;
			} catch (const invalid_argument&) {
				cout << "Error: Invalid input. Please enter an integer number." << endl << endl;
			}
		}
	}
};