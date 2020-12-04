/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Jacob Gerega
 * Version     : 1.0
 * Date        : 12/04/20
 * Description : Implementation of Floyd's Algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>
#include <iomanip>

using namespace std;

long **matrix1;
long **matrix2;
char **ivertices;
int vertices;

//returns how many digits are in a long
long len(long n){
    long counter = 0;
    while(n != 0){
        n /= 10;
        counter++;
    }
    return counter;
}

//returns the shortest path between two points
string pathfinder(long** m1, char** ivm, int from, int to){
    if(m1[from][to] == UINT_MAX){
        return "none";
    }
    else if(ivm[from][to] == '-'){
        string s;
        s.push_back(char(to+65));
        return s;
    }
    else{
        string s;
        s.append(pathfinder(m1, ivm, from, int(ivm[from][to])-65));
        s.append(" -> ");
        s.append(pathfinder(m1, ivm, int(ivm[from][to])-65, to));
        return s;
    }
}

//outputs a matrix of vertice weights, given bounds as vertices
void displaymatrix(long** matrix, int vertices){
    long max = 0;
    for(int i = 0; i < vertices; i++){
        for(int k = 0; k < vertices; k++){
            if(max < matrix[i][k] && matrix[i][k] != UINT_MAX)
            max = matrix[i][k];
        }
    }
    long maxw = len(max);
        for(int i = 0; i < vertices+1; i++){
            for(int k = 0; k < vertices+1; k++){
                if(i == 0 && k == 0){
                    cout << " ";
                }
                else if(i == 0 && k != 0){
                    cout << " " << setw(maxw);
                    cout << char(64+k);
                }
                else if(k == 0 && i != 0){
                    cout << char(64+i);
                }
                else if(matrix[i-1][k-1] == UINT_MAX){
                    cout << " " << setw(maxw);
                    cout << "-";
                }
                else{
                    cout << " " << setw(maxw);
                    cout << matrix[i-1][k-1];
                }
            }
            cout << endl;
        }
        cout << endl;
}

//outputs a matrix of vertices, given bounds as vertices
void displaymatrix(char** matrix, int vertices){
        for(int i = 0; i < vertices+1; i++){
            for(int k = 0; k < vertices+1; k++){
                if(i == 0 && k != 0){
                    cout << " " << char(64+k);
                }
                else if(k == 0 && i != 0){
                    cout << char(64+i);
                }
                else if(k == 0 && i == 0){
                    cout <<  " ";
                }
                else if(matrix[i-1][k-1] == '-'){
                    cout << " -";
                }
                else{
                    cout << " " << matrix[i-1][k-1];
                }
            }
            cout << endl;
        }
        cout << endl;
}

//cleans up all heap usage with arrays
void cleanup(){
    for (int i = 0; i < vertices; ++i) {
            delete [] matrix1[i];
            delete [] matrix2[i];
            delete [] ivertices[i];
        }           
        // Delete the array itself.
        delete [] matrix1;
        delete [] matrix2;
        delete [] ivertices;
}
int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
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
    vertices = 0;
    int ascii = 65;
    int maxascii = 64;

    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line)) {
            if(line_number == 1){
                stringstream vert(line);
                vert >> vertices;
                maxascii+=vertices;
                if(vertices < 1 || vertices > 26){
                    cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << ".";
                    return 1;
                }
                matrix1 = new long*[vertices];
                matrix2 = new long*[vertices];
                ivertices = new char*[vertices];
                for(int i = 0; i < vertices; i++){
                    matrix1[i] = new long[vertices];
                    matrix2[i] = new long[vertices];
                    ivertices[i] = new char[vertices];
                    for(int k = 0; k < vertices; k++){
                        fill(matrix1[i], matrix1[i] + vertices, 0);
                        fill(matrix2[i], matrix2[i] + vertices, 0);
                        fill(ivertices[i], ivertices[i] + vertices, '-');
                    }
                }
            }
            else{
                vector<string> arr;
                stringstream data(line);
                string arg;
                int counter = 0;
                int row = 1;
                int col = 1;
                while(data >> arg){
                    if(counter == 0){
                        if(int(arg[0]) > maxascii || int(arg[0]) < ascii){
                            cerr << "Error: Starting vertex '" << arg << "' on line " << line_number << " is not among valid values " << char(ascii) << "-" << char(maxascii) << ".";
                            cleanup();
                            return 1;
                        }
                        row = (int(arg[0]) - 65);
                    }
                    else if(counter == 1){
                        if(int(arg[0]) > maxascii || int(arg[0]) < ascii){
                            cerr << "Error: Ending vertex '" << arg << "' on line " << line_number << " is not among valid values " << char(ascii) << "-" << char(maxascii) << ".";
                            cleanup();
                            return 1;
                        }
                        col = (int(arg[0]) - 65);
                    }
                    else if(counter == 2){
                        stringstream weight(arg);
                        int arg3;
                        weight >> arg3;
                        if(arg3 <= 0){
                            cerr << "Error: Invalid edge weight '" << arg << "' on line " << line_number << ".";
                            cleanup();
                            return 1;
                        }
                        matrix1[row][col] = arg3;
                    }
                    arr.push_back(arg);
                    counter++;
                }
                if(arr.size() != 3){
                    cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << ".";
                    cleanup();
                    return 1;
                }
            }
            ++line_number;

            //fill diagonal with 0's and any unreachable with infinitys (represented with max uint)
            for(int i = 0; i < vertices; i++){
                for(int k = 0; k < vertices; k++){
                    if(i == k){
                        matrix1[i][k] = 0;
                        matrix2[i][k] = 0;
                    }
                    else if(matrix1[i][k] == 0){
                        matrix1[i][k] = UINT_MAX;
                        matrix2[i][k] = UINT_MAX;
                    }
                }
            }
        }
        // Don't forget to close the file.
        input_file.close();

        cout << "Distance matrix:" << endl;
        displaymatrix(matrix1, vertices);

        for(int k = 0; k < vertices; k++){
            for(int i = 0; i < vertices; i++){
                for(int j = 0; j < vertices; j++){
                    matrix2[i][j] = min(matrix1[i][j], matrix1[i][k] + matrix1[k][j]);
                    if(matrix2[i][j] != matrix1[i][j]){
                        ivertices[i][j] = char(65+k);
                    }
                }
            }
            //copy m2 back to m1
            for(int i = 0; i < vertices; i++){
                for(int j = 0; j < vertices; j++){
                    matrix1[i][j] = matrix2[i][j];
                }
            }
        }
        cout << "Path lengths:" << endl;
        displaymatrix(matrix2, vertices);
        cout << "Intermediate vertices:" << endl;
        displaymatrix(ivertices, vertices);


        for(int i = 0; i < vertices; i++){
            for(int k = 0; k < vertices; k++){
                if(matrix2[i][k] == UINT_MAX){
                    cout << char(65+i) << " -> " << char(65+k) << ", distance: infinity, path: none";
                }
                else if(i == k){
                    cout << char(65+i) << " -> " << char(65+k) << ", distance: 0, path: " << char(65+i);
                }
                else{
                    string s;
                    s.push_back(char(65+i));
                    s.append(" -> ");
                    s.append(pathfinder(matrix2, ivertices, i,k));
                    cout << char(65+i) << " -> " << char(65+k) << ", distance: " << matrix2[i][k] << ", path: " << s;
                }
                cout << endl;
            }
            
        }

        cleanup();

    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    return 0;
}