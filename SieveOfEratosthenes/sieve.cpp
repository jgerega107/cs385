/*******************************************************************************
 * Name    : sieve.cpp
 * Author  : Jacob Gerega
 * Version : 1.0
 * Date    : September 15th, 2020
 * Description : Sieve of Eratosthenes
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class PrimesSieve {
public:
	PrimesSieve(int limit);

	~PrimesSieve() {
		delete[] is_prime_;
	}

	int num_primes() const {
		return num_primes_;
	}

	void display_primes() const;

private:
	// Instance variables
	bool *const is_prime_;
	const int limit_;
	int num_primes_, max_prime_;

	// Method declarations
	int count_num_primes() const;
	void sieve();
	static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
		is_prime_ { new bool[limit + 1] }, limit_ { limit } {
	sieve();
}

void PrimesSieve::display_primes() const {
	// TODO: write code to display the primes in the format specified in the
	// requirements document.
	const int max_prime_width = num_digits(max_prime_);
	const int primes_per_row = 80 / (max_prime_width + 1);
	cout << endl;
	cout << "Number of primes found: " << count_num_primes() << endl;
	cout << "Primes up to " << limit_ << ":" << endl;

	int totalPrimeCounter = 0;
	int linePrimeCounter = 0;
	int confirmedPrimeCount = count_num_primes();
	for (int i = 2; i <= limit_; i++) {
		if (is_prime_[i]) {
			if (confirmedPrimeCount < primes_per_row) {
				if (totalPrimeCounter < confirmedPrimeCount) {
					cout << i << " ";
				} else {
					cout << i;
				}
			} else {
				if (linePrimeCounter < primes_per_row) {
					if (totalPrimeCounter < confirmedPrimeCount) {
						cout << setw(max_prime_width) << i << " ";
					} else {
						cout << setw(max_prime_width) << i;
					}
				} else {
					linePrimeCounter = 0;
					cout << endl;
					if (totalPrimeCounter < confirmedPrimeCount) {
						cout << setw(max_prime_width) << i << " ";
					} else {
						cout << setw(max_prime_width) << i;
					}
				}
			}
			totalPrimeCounter++;
			linePrimeCounter++;
		}
	}
}

int PrimesSieve::count_num_primes() const {
	// TODO: write code to count the number of primes found
	int counter = 0;
	for (int i = 2; i <= limit_; i++) {
		if (is_prime_[i]) {
			counter++;
		}
	}
	return counter;
}

void PrimesSieve::sieve() {
	// TODO: write sieve algorithm

	//fill arrays first
	vector<int> intList;
	for (int i = 2; i <= limit_; i++) {
		intList.push_back(i);
		is_prime_[i] = true;
	}

	//run sieve algorithm
	for (int i = 2; i <= sqrt(limit_); i++) {
		if (is_prime_[i]) {
			for (int j = i + i; j <= limit_; j += i) {
				is_prime_[j] = false;
			}
		}
	}

	//find max prime
	for (int i = 2; i <= limit_; i++) {
		if (is_prime_[i]) {
			max_prime_ = i;
		}
	}

}

int PrimesSieve::num_digits(int num) {
	// TODO: write code to determine how many digits are in an integer
	// Hint: No strings are needed. Keep dividing by 10.

	int digits = 0;
	while (num != 0) {
		num /= 10;
		digits++;
	}
	return digits;
}

int main() {
	cout << "**************************** " << "Sieve of Eratosthenes"
			<< " ****************************" << endl;
	cout << "Search for primes up to: ";
	string limit_str;
	cin >> limit_str;
	int limit;

	// Use stringstream for conversion. Don't forget to #include <sstream>
	istringstream iss(limit_str);

	// Check for error.
	if (!(iss >> limit)) {
		cerr << "Error: Input is not an integer." << endl;
		return 1;
	}
	if (limit < 2) {
		cerr << "Error: Input must be an integer >= 2." << endl;
		return 1;
	}

	PrimesSieve sieve = PrimesSieve(limit);
	sieve.display_primes();
	// TODO: write code that uses your class to produce the desired output.
	return 0;
}
