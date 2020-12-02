#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>

using namespace std;

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
    int vertices = 0;
    int ascii = 65;
    int maxascii = 64;
    long **matrix;
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
                matrix = new long*[vertices];
                for(int i = 0; i < vertices; i++){
                    matrix[i] = new long[vertices];
                    for(int k = 0; k < vertices; k++){
                        matrix[i][k] = 0;
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
                            cerr << "Error: Starting vertex '" << arg << "' on line " << line_number << " is not amoung valid values " << char(ascii) << "-" << char(maxascii) << ".";
                            return 1;
                        }
                        row = (int(arg[0]) - 65);
                    }
                    else if(counter == 1){
                        if(int(arg[0]) > maxascii || int(arg[0]) < ascii){
                            cerr << "Error: Ending vertex '" << arg << "' on line " << line_number << " is not amoung valid values " << char(ascii) << "-" << char(maxascii) << ".";
                            return 1;
                        }
                        col = (int(arg[0]) - 65);
                    }
                    else if(counter == 2){
                        stringstream weight(arg);
                        int arg3;
                        weight >> arg3;
                        if(arg3 < 0){
                            cerr << "Error: Invalid edge weight '" << arg << "' on line " << line_number << ".";
                            return 1;
                        }
                        matrix[row][col] = arg3;
                    }
                    arr.push_back(arg);
                    counter++;
                }
                if(arr.size() != 3){
                    cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << ".";
                    return 1;
                }
            }
            ++line_number;

            for(int i = 0; i < vertices; i++){
                for(int k = 0; k < vertices; k++){
                    if(i == k){
                        matrix[i][k] = 0;
                    }
                    else if(matrix[i][k] == 0){
                        matrix[i][k] = LONG_MAX;
                    }
                }
            }
        }
        // Don't forget to close the file.
        input_file.close();

        long **dmatrix = new long*[vertices];
        for(int i = 0; i < vertices; i++){
                dmatrix[i] = new long[vertices];
                for(int k = 0; k < vertices; k++){
                    dmatrix[i][k] = 0;
                }
            }
        
        for(int i = 0; i < vertices; i++){
            for(int k = 0; k < vertices; k++){
                if(i == k){
                    dmatrix[i][k] = 0;
                }
                else if(i == 0 || k == 0){
                    dmatrix[i][k] = matrix[i][k];
                }
            }
        }
        for(int i = 0; i < vertices; i++){
            for(int k = 0; k < vertices; k++){
                if(matrix[i][0] != LONG_MAX && matrix[0][k] != LONG_MAX && dmatrix[i][k] > matrix[i][0] + matrix[0][k]){
                    dmatrix[i][k] = matrix[i][0] + matrix[0][k];
                }
            }
        }
        cout << "Initial Distance Matrix:" << endl;
        for(int i = 0; i < vertices; i++){
            for(int k = 0; k < vertices; k++){
                if(matrix[i][k] == LONG_MAX){
                    cout << "-  ";
                }
                else{
                    cout << matrix[i][k] << "  ";
                }
            }
            cout << endl;
        }
        cout << "Modified Distance Matrix:" << endl;
        for(int i = 0; i < vertices; i++){
            for(int k = 0; k < vertices; k++){
                if(dmatrix[i][k] == LONG_MAX){
                    cout << "-  ";
                }
                else{
                    cout << dmatrix[i][k] << "  ";
                }
            }
            cout << endl;
        }
        for (int i = 0; i < vertices; ++i) {
            delete [] matrix[i];
            delete [] dmatrix[i];
        }           
        // Delete the array itself.
        delete [] matrix;
        delete [] dmatrix;

    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    return 0;
}
