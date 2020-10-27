/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Jacob Gerega
 * Version     : 1.0
 * Date        : 10/27/20
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.

static long mergesort(int array[], int scratch[], int low, int high);
/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
	long inversions = 0;
	for (int i = 0; i < length; i++) {
		for (int j = i; j < length; j++) {
			if (array[i] > array[j]) {
				inversions++;
			}
		}
	}
	return inversions;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */

long count_inversions_fast(int array[], int length) {
	// TODO
	vector<int> scratch;
	scratch.resize(length);
	return mergesort(array, scratch.data(), 0, length-1);
}

static long mergesort(int array[], int scratch[], int low, int high) {
	long inversions = 0;
	if (low < high) {
		int mid = low + (high - low) / 2;
		inversions += mergesort(array, scratch, low, mid);
		inversions += mergesort(array, scratch, mid + 1, high);
		int L = low;
		int H = mid + 1;
		for (int k = low; k <= high; k++) {
			if (L <= mid && (H > high || array[L] <= array[H])) {
				scratch[k] = array[L];
				L++;
			} else {
				scratch[k] = array[H];
				H++;
				inversions += (mid - L + 1);
			}
		}
		for (int k = low; k <= high; k++) {
			array[k] = scratch[k];
		}
	}
	return inversions;
}

int main(int argc, char *argv[]) {
	// TODO: parse command-line argument
	bool slow = false;
	if (argc != 1 && argc != 2) {
		cout << "Usage: ./inversioncounter [slow]" << flush;
		return 1;
	} else if (argc == 2) {
		string speed = argv[1];
		if(speed == "slow"){
			slow = true;
		}
		else{
			cout << "Error: Unrecognized option '" << speed << "'." << endl;
			return 1;
		}
	}
	cout << "Enter sequence of integers, each followed by a space: " << flush;
	istringstream iss;
	int value, index = 0;
	vector<int> values;
	string str;
	str.reserve(11);
	char c;
	while (true) {
		c = getchar();
		const bool eoln = c == '\r' || c == '\n';
		if (isspace(c) || eoln) {
			if (str.length() > 0) {
				iss.str(str);
				if (iss >> value) {
					values.push_back(value);
				} else {
					cerr << "Error: Non-integer value '" << str
							<< "' received at index " << index << "." << endl;
					return 1;
				}
				iss.clear();
				++index;
			}
			if (eoln) {
				break;
			}
			str.clear();
		} else {
			str += c;
		}
	}

	// TODO: produce output
	if(values.empty()){
		cout << "Error: Sequence of integers not received." << endl;
		return 1;
	}
	else if (slow) {
		cout << "Number of inversions: "
				<< count_inversions_slow(values.data(), values.size()) << endl;
	} else {
		cout << "Number of inversions: "
				<< count_inversions_fast(values.data(), values.size()) << endl;
	}
	return 0;
}
