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

    long **matrix1;
    long **matrix2;
    char **ivertices;

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
                        matrix1[i][k] = 0;
                        matrix2[i][k] = 0;
                        ivertices[i][k] = '-';
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
                        matrix1[row][col] = arg3;
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

            //fill diagonal with 0's and any unreachable with infinitys (represented with max long)
            for(int i = 0; i < vertices; i++){
                for(int k = 0; k < vertices; k++){
                    if(i == k){
                        matrix1[i][k] = 0;
                        matrix2[i][k] = 0;
                    }
                    else if(matrix1[i][k] == 0){
                        matrix1[i][k] = INT_MAX;
                        matrix2[i][k] = INT_MAX;
                    }
                }
            }
        }
        // Don't forget to close the file.
        input_file.close();

        cout << "Distance matrix initial: " << endl;
        for(int i = 0; i < vertices; i++){
            for(int k = 0; k < vertices; k++){
                if(matrix1[i][k] == INT_MAX){
                    cout << "-  ";
                }
                else{
                    cout << matrix1[i][k] << "  ";
                }
            }
            cout << endl;
        }

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
            cout << "Distance matrix new:" << endl;
            for(int i = 0; i < vertices; i++){
                for(int k = 0; k < vertices; k++){
                    if(matrix1[i][k] == INT_MAX){
                        cout << "-  ";
                    }
                    else{
                        cout << matrix1[i][k] << "  ";
                    }
                }
                cout << endl;
            }
        }

        cout << "Intermediate vertices matrix initial: " << endl;
        for(int i = 0; i < vertices; i++){
            for(int k = 0; k < vertices; k++){
                if(ivertices[i][k] == '-'){
                    cout << "-  ";
                }
                else{
                    cout << ivertices[i][k] << "  ";
                }
            }
            cout << endl;
        }

        cout << "Paths" << endl;
        for(int i = 0; i < vertices; i++){
            for(int k = 0; k < vertices; k++){
                if(matrix2[i][k] != INT_MAX){
                    cout << char(65+i) << " -> " << char(65+k) << ", distance: " << matrix2[i][k] << ", path: " << char(65+i);
                    char current = char(65+i);
                    while(current != '-' && matrix2[int(current) - 65][k] != INT_MAX && i != k){
                        current = ivertices[int(current) - 65][k];
                        if(current == '-'){
                            cout << " -> " << char(65+k);
                        }
                        else{
                            cout << " -> " << current;
                        }
                    }
                    cout << endl;
                }
            }
        }
        
        for (int i = 0; i < vertices; ++i) {
            delete [] matrix1[i];
            delete [] matrix2[i];
            delete [] ivertices[i];
        }           
        // Delete the array itself.
        delete [] matrix1;
        delete [] matrix2;
        delete [] ivertices;

    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    return 0;
}