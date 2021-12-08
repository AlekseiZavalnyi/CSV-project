#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include "CSV_VERSION2.h"

void case_1(string fn, string fn_out){
    csvFile q(fn, fn_out);

    string line;
    int n;

    cout << "Which line do you want to replace? ";
    cin >> n;
    cout << "Enter new line with separators ';' : ";
    cin >> line;
    q.change_row(line, n);
    q.print_data();

    cout << "Which line do you want to delete? ";
    cin >> n;
    q.delete_row(n);
    q.print_data();

    cout << "Enter a line with separators ';' to append to the EOF ";
    cin >> line;
    q.append_row(line);
    q.print_data();

    cout << "Which column do you want to delete? ";
    cin >> n;
    q.delete_field(n);
    q.print_data();

    cout << "Enter the number of the columns: ";
    cin >> n;
    vector<string> vec;
    string a;
    cout << "Enter values: " << endl;
    for (int i = 0; i < n; i++){
        cin >> a;
        vec.push_back(a);
    }
    cout << "Enter the number of the column you want to replace ";
    cin >> n;
    q.change_field(vec, n);
    q.print_data();
    vec.clear();

    cout << "Enter the number of the columns: ";

    cout << "Enter values: " << endl;
    for (int i = 0; i < n; i++){
        cin >> a;
        vec.push_back(a);
    }
    q.append_field(vec);
    q.print_data();

}



void case_2(string fn, string fn_out){
    csvFile q(fn, fn_out);
    q.print_data();

    string test_file = "tests.txt";
    /*cout << "Enter test file name: " << endl;
    cin >> test_file;*/
    ifstream tests(test_file);
    string line;
    while (getline(tests, line)){
        if (line[0] != '#'){
            if (line == "APPEND_ROW"){
                getline(tests, line);
                q.append_row(line);
                q.print_data();
            }
            else if (line == "DELETE_ROW"){
                getline(tests, line);
                int n = atoi(line.c_str());
                q.delete_row(n);
                q.print_data();
            }
            else if (line == "CHANGE_ROW"){
                getline(tests, line);
                int n = atoi(line.c_str());
                getline(tests, line);
                q.change_row(line, n);
                q.print_data();
            }
            else if (line == "CHANGE_COLUMN"){
                getline(tests, line);
                int col_num = atoi(line.c_str());
                getline(tests, line);
                int n = atoi(line.c_str());
                vector<string> vec;
                for (int i = 0; i < n; i++){
                    getline(tests, line);
                    vec.push_back(line);
                }
                q.change_field(vec, col_num);
                q.print_data();
            }
            else if (line == "DELETE_COLUMN"){
                getline(tests, line);
                int n = atoi(line.c_str());
                q.delete_field(n);
                q.print_data();
            }
            else if (line == "DELETE_ROW"){
                getline(tests, line);
                int n = atoi(line.c_str());
                q.delete_row(n);
                q.print_data();
            }
            else if (line == "APPEND_COLUMN"){
                getline(tests, line);
                int n = atoi(line.c_str());
                vector<string> vec;
                for (int i = 0; i < n; i++){
                    getline(tests, line);
                    vec.push_back(line);
                }
                q.append_field(vec);
                q.print_data();
            }
        }
    }

}



int main()
{
    //setlocale(LC_ALL, "Russian");
    string fn, fn_out;

    fn = "prog.csv";
    fn_out = "prog_res.csv";

    /*cout << "Enter the name of the non-empty information file: ";
    cin >> fn;

    cout << "Enter the name of an empty existing file: ";
    cin >> fn_out;*/

    int n;
    cout << "Do you want to enter test data from the console of from the text file? (1 or 2): ";
    cin >> n;

    if (n == 1) case_1(fn, fn_out);
    if (n == 2) case_2(fn, fn_out);

    return 0;
}
