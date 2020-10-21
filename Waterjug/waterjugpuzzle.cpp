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

	bool equals(State *s) {
		return (s->a == a && s->b == b && s->c == c);
	}

};

queue<State*> pour(State *p1) {
	queue<State*> newstates;
	//c to a
	if (p1->a != values[0]) {
		State *newjug = new State(p1->a, p1->b, p1->c, "");
		newjug->a += p1->c;
		newjug->c = 0;
		int topoff = newjug->a - values[0];
		if (topoff > 0) {
			newjug->a -= topoff;
			newjug->c += topoff;
		}
		newjug->parent = p1;
		int amount = p1->c - newjug->c;
		if (amount == 1) {
			newjug->directions = "Pour " + to_string(amount)
					+ " gallon from C to A.";
		} else {
			newjug->directions = "Pour " + to_string(amount)
					+ " gallons from C to A.";
		}

		if (!newjug->equals(p1)) {
			newstates.push(newjug);
		}
		else{
			delete newjug;
		}
	}
	//b to a
	if (p1->a != values[0]) {
		State *newjug = new State(p1->a, p1->b, p1->c, "");
		newjug->a += p1->b;
		newjug->b = 0;
		int topoff = newjug->a - values[0];
		if (topoff > 0) {
			newjug->a -= topoff;
			newjug->b += topoff;
		}
		newjug->parent = p1;
		int amount = p1->b - newjug->b;
		if (amount == 1) {
			newjug->directions = "Pour " + to_string(amount)
					+ " gallon from B to A.";

		} else {
			newjug->directions = "Pour " + to_string(amount)
					+ " gallons from B to A.";
		}
		if (!newjug->equals(p1)) {
			newstates.push(newjug);
		}
		else{
			delete newjug;
		}
	}
	//c to b
	if (p1->b != values[1]) {
		State *newjug = new State(p1->a, p1->b, p1->c, "");
		newjug->b += p1->c;
		newjug->c = 0;
		int topoff = newjug->b - values[1];
		if (topoff > 0) {
			newjug->b -= topoff;
			newjug->c += topoff;
		}
		newjug->parent = p1;
		int amount = p1->c - newjug->c;
		if (amount == 1) {
			newjug->directions = "Pour " + to_string(amount)
					+ " gallon from C to B.";
		} else {
			newjug->directions = "Pour " + to_string(amount)
					+ " gallons from C to B.";
		}
		if (!newjug->equals(p1)) {
			newstates.push(newjug);
		}
		else{
			delete newjug;
		}
	}
	//a to b
	if (p1->b != values[1]) {
		State *newjug = new State(p1->a, p1->b, p1->c, "");
		newjug->b += p1->a;
		newjug->a = 0;
		int topoff = newjug->b - values[1];
		if (topoff > 0) {
			newjug->b -= topoff;
			newjug->a += topoff;
		}
		newjug->parent = p1;
		int amount = p1->a - newjug->a;
		if (amount == 1) {
			newjug->directions = "Pour " + to_string(amount)
					+ " gallon from A to B.";
		} else {
			newjug->directions = "Pour " + to_string(amount)
					+ " gallons from A to B.";
		}

		if (!newjug->equals(p1)) {
			newstates.push(newjug);
		}
		else{
			delete newjug;
		}
	}
	//b to c
	if (p1->c != values[2]) {
		State *newjug = new State(p1->a, p1->b, p1->c, "");
		newjug->c += p1->b;
		newjug->b = 0;
		int topoff = newjug->c - values[2];
		if (topoff > 0) {
			newjug->c -= topoff;
			newjug->b += topoff;
		}
		newjug->parent = p1;
		int amount = p1->b - newjug->b;
		if (amount == 1) {
			newjug->directions = "Pour " + to_string(amount)
					+ " gallons from B to C.";
		} else {
			newjug->directions = "Pour " + to_string(amount)
					+ " gallons from B to C.";
		}
		if (!newjug->equals(p1)) {
			newstates.push(newjug);
		}
		else{
			delete newjug;
		}
	}
	//a to c
	if (p1->c != values[2]) {
		State *newjug = new State(p1->a, p1->b, p1->c, "");
		newjug->c += p1->a;
		newjug->a = 0;
		int topoff = newjug->c - values[2];
		if (topoff > 0) {
			newjug->c -= topoff;
			newjug->a += topoff;
		}
		newjug->parent = p1;
		int amount = p1->a - newjug->a;
		if (amount == 1) {
			newjug->directions = "Pour " + to_string(amount)
					+ " gallon from A to C.";
		} else {
			newjug->directions = "Pour " + to_string(amount)
					+ " gallons from A to C.";
		}
		if (!newjug->equals(p1)) {
			newstates.push(newjug);
		}
		else{
			delete newjug;
		}
	}
	return newstates;
}

string bfs(int a, int b, int c) {
	queue<State*> Q;
	State *is = new State(a, b, c, "Initial state.");
	State *gs = new State(values[3], values[4], values[5], "Goal state.");
	int rows = values[0] + 1;
	int cols = values[1] + 1;
	bool **array = new bool*[rows];
	for (int i = 0; i < rows; ++i) {
		array[i] = new bool[cols];
		fill(array[i], array[i] + cols, false);
	}
	Q.push(is);
	while (!Q.empty()) {
		State *current = Q.front();
		Q.pop();
		if (current->equals(gs)) {
			string solution = "";
			vector < string > path;
			while (current->parent != nullptr) {
				string cpath = current->directions + " " + current->to_string();
				path.push_back(cpath);
				State* parent = current->parent;
				delete current;
				current = parent;
			}
			string ipath = is->directions + " " + is->to_string();
			path.push_back(ipath);
			auto it = path.rbegin();
			while (it != path.rend() - 1) {
				solution += *it + "\n";
				++it;
			}
			solution += *it;
			//cleanup
			delete is;
			delete gs;
			for (int i = 0; i < rows; ++i) {
				delete[] array[i];
			}
			delete[] array;
			while(!Q.empty()){
				delete Q.front();
				Q.pop();
			}
			return solution;
		}
		//try to pour and add each possible state to queue
		if (!array[current->a][current->b]) {
			array[current->a][current->b] = true;
			queue<State*> newpours = pour(current);
			if(newpours.empty()){
				delete current;
			}
			else{
				while (!newpours.empty()) {
				Q.push(newpours.front());
				newpours.pop();
			}
			}
		}
		else{
			delete current;
		}
	}
	return "No solution.";
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
