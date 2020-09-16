/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Jacob Gerega
 * Version : 1.0
 * Date    : September 3rd, 2020
 * Description : Computes the square root of a number to a tolerance of epsilon via Newtons method
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <limits>
#include <iomanip>

using namespace std;

/**
 * Returns the square root of an double to a tolerance of epsilon.
 */

double sqrt(double num, double epsilon) {

	if (num == 0 || num == 1) {
		return num;
	}
	if (num < 0) {
		return numeric_limits<double>::quiet_NaN();
	}

	double lg = 0;
	double ng = num;

	while (abs(lg - ng) >= epsilon) {
		lg = ng;
		ng = (lg + (num / lg)) / 2;
	}
	return ng;

}

double sqrt(double num) {

	if (num == 0 || num == 1) {
		return num;
	}
	if (num < 0) {
		return numeric_limits<double>::quiet_NaN();
	}

	double lg = 0;
	double ng = num;

	while (abs(lg - ng) >= 1e-7) {
		lg = ng;
		ng = (lg + (num / lg)) / 2;
	}
	return ng;

}

int main(int argc, char *argv[]) {
	double n, m;
	istringstream iss;

	if (argc > 3 || argc == 1) {
		cerr << "Usage: " << argv[0]
				<< " <value> [epsilon]" << endl;
		return 1;
	}
	if (argc == 3) {
		iss.str(argv[1]);
		if (!(iss >> n)) {
			cerr << "Error: Value argument must be a double." << endl;
			return 1;
		}
		iss.clear();
		iss.str(argv[2]);
		if (!(iss >> m) || m <= 0) {
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
		iss.clear();
		cout << fixed << setprecision(8) << sqrt(n, m) << endl;
	} else if (argc == 2) {
		iss.str(argv[1]);
		if (!(iss >> n)) {
			cerr << "Error: Value argument must be a double." << endl;
			return 1;
		}
		iss.clear();
		cout << fixed << setprecision(8) << sqrt(n) << endl;
	}
	return 0;
}

