/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Authors     : Adham Abdelwahab and Jacob Gerega
 * Date        : 10/ 19 / 2020
 * Description : Use BFS recursively to solve the water jug puzzle.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <cctype>
#include <string>
#include <queue>
#include <vector>

using namespace std;

int values[6];

struct State {
	int a, b, c;
	string directions;
	State *parent;
	State(int _a, int _b, int _c, string _directions) :
			a { _a }, b { _b }, c { _c }, directions { _directions }, parent {
					nullptr } {
	}
	string to_string() {
		ostringstream oss;
		oss << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}

	bool equals(State s) {
		return (s.a == a && s.b == b && s.c == c);
	}

};

//jug == 0 for a, 1 for b, 2 for c
queue<State> pour(State p1, State *p1r) {
	queue<State> newstates;
	//c to a
	if (p1.a != values[0]) {
		State newjug = State(p1.a, p1.b, p1.c, "C to A");
		newjug.a += p1.c;
		newjug.c = 0;
		int topoff = newjug.a - values[0];
		if (topoff > 0) {
			newjug.a -= topoff;
			newjug.c += topoff;
		}
		newjug.parent = p1r;
		if (!newjug.equals(p1)) {
			newstates.push(newjug);
		}
	}
	//b to a
	if (p1.a != values[0]) {
		State newjug = State(p1.a, p1.b, p1.c, "B to A");
		newjug.a += p1.b;
		newjug.b = 0;
		int topoff = newjug.a - values[0];
		if (topoff > 0) {
			newjug.a -= topoff;
			newjug.b += topoff;
		}
		newjug.parent = p1r;
		if (!newjug.equals(p1)) {
			newstates.push(newjug);
		}
	}
	//c to b
	if (p1.b != values[1]) {
		State newjug = State(p1.a, p1.b, p1.c, "C to B");
		newjug.b += p1.c;
		newjug.c = 0;
		int topoff = newjug.b - values[1];
		if (topoff > 0) {
			newjug.b -= topoff;
			newjug.c += topoff;
		}
		newjug.parent = p1r;
		if (!newjug.equals(p1)) {
			newstates.push(newjug);
		}
	}
	//a to b
	if (p1.b != values[1]) {
		State newjug = State(p1.a, p1.b, p1.c, "A to B");
		newjug.b += p1.a;
		newjug.a = 0;
		int topoff = newjug.b - values[1];
		if (topoff > 0) {
			newjug.b -= topoff;
			newjug.a += topoff;
		}
		newjug.parent = p1r;
		if (!newjug.equals(p1)) {
			newstates.push(newjug);
		}
	}
	//b to c
	if (p1.c != values[2]) {
		State newjug = State(p1.a, p1.b, p1.c, "B to C");
		newjug.c += p1.b;
		newjug.b = 0;
		int topoff = newjug.c - values[2];
		if (topoff > 0) {
			newjug.c -= topoff;
			newjug.b += topoff;
		}
		newjug.parent = p1r;
		if (!newjug.equals(p1)) {
			newstates.push(newjug);
		}
	}
	//a to c
	if (p1.c != values[2]) {
		State newjug = State(p1.a, p1.b, p1.c, "A to C");
		newjug.c += p1.a;
		newjug.a = 0;
		int topoff = newjug.c - values[2];
		if (topoff > 0) {
			newjug.c -= topoff;
			newjug.a += topoff;
		}
		newjug.parent = p1r;
		if (!newjug.equals(p1)) {
			newstates.push(newjug);
		}
	}
	return newstates;
}

string bfs(int a, int b, int c) {
	queue<State> Q;
	State is = State(a, b, c, "Initial state");
	State gs = State(values[3], values[4], values[5], "Goal state");
	Q.push(is);
	while (!Q.empty()) {
		State current = Q.front();
		Q.pop();
		if (current.equals(gs)) {
			return "";
		}
		//try to pour and add each possible state to queue
		queue<State> newpours = pour(current, &current);
		while (!newpours.empty()) {
			if(!newpours.front().equals(is)){
				Q.push(newpours.front());
							cout << newpours.front().to_string() << endl;
							cout
									<< "Parent of previous: "
											+ newpours.front().parent->to_string() << endl;
			}
			newpours.pop();
		}
	}
	return "";
}

int main(int argc, char *const argv[]) {
	// TODO: reads and parses command line arguments.
	// Calls other functions to produce correct output.

	if (argc != 7) {
		cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> "
				"<goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	istringstream iss;

	for (int i = 1; i <= 6; i++) {
		iss.str(argv[i]);
		if (!(iss >> values[i - 1]) || values[i - 1] < 0
				|| (i == 3 && values[i - 1] == 0)) {
			if (i <= 3) {
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug "
						<< char(64 + i) << "." << endl;
			} else {
				cerr << "Error: Invalid goal '" << argv[i] << "' for jug "
						<< char(61 + i) << "." << endl;
			}
			return 1;
		}
		iss.clear();
	}

	for (int i = 0; i < 3; i++) {
		if (values[i] < values[i + 3]) {
			cerr << "Error: Goal cannot exceed capacity of jug " << char(65 + i)
					<< "." << endl;
			return 1;
		}
	}

	if (values[2] != values[3] + values[4] + values[5]) {
		cerr
				<< "Error: Total gallons in goal state must be equal to the capacity of jug C."
				<< endl;
		return 1;
	}
	cout << bfs(0, 0, values[2]) << endl;
	return 0;
}
