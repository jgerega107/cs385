/*
 * max.cpp
 *
 *  Created on: Sep 2, 2020
 *      Author: user
 */

#include <iostream>
#include <sstream>

/**
 * Returns the max of two integers.
 */

int max(int m, int n){
	return m > n ? m : n;
}

using namespace std;

int main(int argc, char *argv[]){
	int m, n;
	istringstream iss;

	if(argc < 3){
		cerr << "Usage: " << argv[0] << " <integer n> <integer m>" << endl;
		return 1;
	}

	iss.str(argv[1]);
	if(!(iss >> m)){
		cerr << "Error: First argument is not a valid integer." << endl;
		return 1;
	}

	iss.clear();
	iss.str(argv[2]);
	if(!(iss >> n)){
			cerr << "Error: Second argument is not a valid integer." << endl;
			return 1;
		}

cout << "max(" << m << "," << n << ") = " << max(m, n) << endl;
	return 0;
}




