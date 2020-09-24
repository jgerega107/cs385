/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Jacob Gerega
 * Date        : September 22nd, 2020
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <sstream>

using namespace std;

bool is_all_lowercase(const string &s) {
	// TODO: returns true if all characters in string are lowercase
	// letters in the English alphabet; false otherwise.
	for (char const &c : s) {
		if (c == toupper(c)) {
			return false;
		}
	}
	return true;
}

bool all_unique_letters(const string &s) {
	// TODO: returns true if all letters in string are unique, that is
	// no duplicates are found; false otherwise.
	// You may use only a single int for storage and work with bitwise
	// and bitshifting operators.
	// No credit will be given for other solutions.
	unsigned int storage = 0;
	for (char const &c : s) {
		unsigned int prevLetter = 1 << (c - s[0]);
		if ((storage & prevLetter) != 0) {
			return false;
		}
		storage = storage | prevLetter;
	}
	return true;
}

int main(int argc, char *const argv[]) {
	// TODO: reads and parses command line arguments.
	// Calls other functions to produce correct output.
	if (argc == 1 || argc > 2) {
		cout << "Usage: " << argv[0] << " <string>" << endl;
		return 0;
	}
	if (!is_all_lowercase(argv[1])) {
		cout << "Error: String must contain only lowercase letters." << endl;
		return 0;
	}
	bool unique = all_unique_letters(argv[1]);
	if (unique) {
		cout << "All letters are unique." << endl;
	} else {
		cout << "Duplicate letters found." << endl;
	}
	return 0;
}
