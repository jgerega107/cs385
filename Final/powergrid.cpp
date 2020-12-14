/*******************************************************************************
 * Name        : powergrid.cpp
 * Author      : Jacob Gerega
 * Version     : 1.0
 * Date        : 12/13/20
 * Description : Implementation of Prim's Algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>
#include <iomanip>
#include <algorithm>

using namespace std;
struct edge{
    int from;
    int to;
    int weight;
    string name;
};

edge minedge(edge a, edge b){
        if(a.weight < b.weight){
            return a;
        }
        else{
            return b;
        }
    }
bool equaledge(edge a,edge b){
        return a.from == b.from && a.to == b.to && a.weight == b.weight && a.name == b.name;
    }

bool sortnames(vector<edge> a, vector<edge> b){
    return a.at(0).name > b.at(0).name;
}

int vertices;
edge **adjmatrix;

void cleanup(){
    for (int i = 0; i < vertices; ++i) {
            delete [] adjmatrix[i];
        }           
        // Delete the array itself.
        delete [] adjmatrix;
}
int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line)) {
            if(line_number == 1){
                stringstream vert(line);
                vert >> vertices;
                if(vertices < 1 || vertices > 1000){
                    cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << ".";
                    return 1;
                }
                //create adj matrix
                adjmatrix = new edge*[vertices];
                for(int i = 0; i < vertices; i++){
                    adjmatrix[i] = new edge[vertices];
                    for(int k = 0; k < vertices; k++){
                        edge e;
                        e.from = i+1;
                        e.to = k+1;
                        e.weight = INT_MAX;
                        adjmatrix[i][k] = e;
                    }
                }
            }
            else{
                vector<string> arr;
                stringstream data(line);
                string arg;
                while(getline(data, arg, ',')){
                    arr.push_back(arg);
                }
                if(arr.size() != 4){
                    cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << ".";
                    cleanup();
                    return 1;
                }
                stringstream from(arr.at(0));
                stringstream to(arr.at(1));
                stringstream weight(arr.at(2));
                int fromi;
                int toi;
                int weighti;
                from >> fromi;
                to >> toi;
                weight >> weighti;
                if(fromi < 1 || fromi > vertices){
                    cerr << "Error: Starting vertex '" << arr.at(0) << "' on line " << line_number << " is not among valid values 1-" << vertices << ".";
                    cleanup();
                    return 1;
                }
                else if(toi < 1 || toi > vertices){
                    cerr << "Error: Ending vertex '" << arr.at(1) << "' on line " << line_number << " is not among valid values 1-" << vertices << ".";
                    cleanup();
                    return 1;
                }
                else if(weighti <= 0){
                    cerr << "Error: Invalid edge weight '" << arr.at(2) << "' on line " << line_number << ".";
                    cleanup();
                    return 1;
                }
                //if we've made it past here, we're good to go with adding it to the adjacency matrix
                edge e;
                e.from = fromi;
                e.to = toi;
                e.weight = weighti;
                e.name = arr.at(3);
                adjmatrix[fromi - 1][toi - 1] = e;
                adjmatrix[toi - 1][fromi - 1] = e;
            }
            ++line_number;
        }
        // Don't forget to close the file.
        input_file.close();

    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }
    //check for no solution
    for(int r = 0; r < vertices; r++){
        bool alone = true;
        for(int c = 0; c < vertices; c++){
            if(adjmatrix[r][c].weight != INT_MAX){
                alone = false;
            }
        }
        if(alone){
            cout << "No solution." << endl;
            cleanup();
            return 0;
        }
    }

    vector<vector<edge>> adjlist;
    //generate first row of adjlist with first item being the start always
    vector<edge> trow;
    for(int c = 0; c < vertices; c++){
        trow.push_back(adjmatrix[0][c]);
    }
    adjlist.push_back(trow);
    while(trow.size() > 1){
        //first find the shortest path
        int minweight = INT_MAX;
        edge min;
        for(auto it = trow.cbegin() + 1; it != trow.cend(); ++it){
            if(it->weight < minweight){
                minweight = it->weight;
                min = *it;
            }
        }
        vector<edge> newrow;
        newrow.push_back(min);
        for(auto it = trow.cbegin() + 1; it != trow.cend(); ++it){
            if(!equaledge(*it, newrow.at(0))){
                newrow.push_back(minedge(*it, adjmatrix[newrow.at(0).to-1][it->to-1]));
            }
        }
        trow = newrow;
        adjlist.push_back(newrow);
    }

    int sumlength = 0;
    for(auto it1 = adjlist.cend()-1; it1 != adjlist.cbegin(); --it1){
        sumlength += it1->at(0).weight;
    }
    sort(adjlist.begin(), adjlist.end(), sortnames); //sort by name
    cout << "Total wire length (meters): " << sumlength << endl;
    for(auto it1 = adjlist.cend()-2; it1 != adjlist.cbegin()-1; --it1){
        cout << it1->at(0).name << " [" << it1->at(0).weight << "]" << endl;
    }
    cleanup();
    return 0;
}