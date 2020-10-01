/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Jacob Gerega
 * Date        : 9/30/20
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	vector<vector<int>> ways;
	if (num_stairs <= 0){
		vector<int> empty;
		ways.push_back(empty);
	}
	else{
		for(unsigned int i = 1; i < 4; i++){
			if( (unsigned)num_stairs >= i){
				vector<vector<int>> result = get_ways(num_stairs - i);
				for(unsigned int j = 0; j < result.size(); j++){
					vector<int> temp = result.at(j);
					temp.insert(temp.begin(), i);
					result.at(j) = temp;
				}
				ways.insert(ways.end(), result.begin(), result.end());
			}
		}
	}
	return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	int digits = 0;
	int size = ways.size();
	while (size != 0) {
		size /= 10;
		digits++;
	}
		
	int counter = 1;
	unsigned int r, c;
	for(r = 0; r < ways.size(); r++){
		cout << setw(digits) << counter << ". [";
		for(c = 0; c < ways[r].size()-1; c++){
			cout << ways[r][c] << ", ";
		}
		cout << ways[r][c] << "]" << endl;
		counter++;
	}
}

int main(int argc, char * const argv[]) {
	if(argc <= 1 || argc > 2){
		cout << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 0;
	}
	else if(!atoi(argv[1]) || atoi(argv[1]) <= 0){
		cout << "Error: Number of stairs must be a positive integer." << endl;
		return 0;
	}
	int stairCount = atoi(argv[1]);
	vector<vector<int>> knownWays = get_ways(stairCount);
	if(stairCount == 1){
		cout << knownWays.size() << " way to climb " << stairCount << " stair." << endl;
	}
	else{
		cout << knownWays.size() << " ways to climb " << stairCount << " stairs." << endl;
	}
	display_ways(knownWays);
	return 0;
}