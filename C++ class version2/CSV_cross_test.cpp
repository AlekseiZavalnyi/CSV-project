/*
 * File CSV_cross_test.cpp
 * Realization of a comparison between a C library and a C++ class
 * Done by Oleksii Zavalnyi (computer mathematics 2)
 * Date 07.12.2021
 *
 */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include "CSV_VERSION2.h"

extern "C" {
    #include "CSV.h"
}


void test_c(char f1[], char f2[]){
    writeToAnotherFile(f1, f2);
    start(f2);


    char *f_test_name;
    f_test_name = "tests.txt";
    //printf("Enter the name of the file that has the data to be tested: ");
    //scanf("%s", f_test_name);

    FILE *tests = fopen(f_test_name, "r");
    char line[64];
    while(fscanf(tests, "%s", line) != EOF){
        if (line[0] != '#'){
            concat(line, "\n");
            if (!strcmp(line,"APPEND_ROW")){
                fscanf(tests, "%s", line);
                rowToEOF(f2, line);
            }
            else if (!strcmp(line,"DELETE_ROW")){
                fscanf(tests, "%s", line);
                int num = atoi(line);
                removeRow(f2, num);
            }
            else if (!strcmp(line, "CHANGE_ROW")){
                fscanf(tests, "%s", line);
                int numb = atoi(line);
                fscanf(tests, "%s", line);
                changeRow(f2, line, numb);
            }
            else if (!strcmp(line, "CHANGE_COLUMN")){
                fscanf(tests, "%s", line);
                int num_col = atoi(line);
                fscanf(tests, "%s", line);
                int size_cols = atoi(line);
                char *column_names[size_cols];
                for (int i = 0; i < size_cols; i++){
                    fscanf(tests, "%s", line);
                    column_names[i] = (char*)malloc(sizeof(char)* (strlen(line)+1));
                    strcpy(column_names[i], line);
                }
                changeColumn(f2, column_names, num_col);
            }
            else if (!strcmp(line, "CHANGE_GEN_FIELD_NAME")){
                fscanf(tests, "%s", line);
                int num_of_col = atoi(line);
                fscanf(tests, "%s", line);
                changeGeneralFieldName(f2, line, num_of_col);
            }
            else if (!strcmp(line, "APPEND_COLUMN")){
                fscanf(tests, "%s", line);
                int number = atoi(line);
                char *column_val[number];
                for (int i = 0; i < number; i++){
                    fscanf(tests, "%s", line);
                    column_val[i] = (char*)malloc(sizeof(char)* (strlen(line)+1));
                    strcpy(column_val[i], line);
                }
                appendColumn(f2, column_val);
            }
            else if (!strcmp(line, "DELETE_COLUMN")){
                fscanf(tests, "%s", line);
                int numb_col = atoi(line);
                removeColumnByNumber(f2, numb_col);
            }
        }
    }
}

void test_cpp(string fn, string fn_out){
    csvFile q(fn, fn_out);

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
            }
            else if (line == "DELETE_ROW"){
                getline(tests, line);
                int n = atoi(line.c_str());
                q.delete_row(n);
            }
            else if (line == "CHANGE_ROW"){
                getline(tests, line);
                int n = atoi(line.c_str());
                getline(tests, line);
                q.change_row(line, n);
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
            }
            else if (line == "DELETE_COLUMN"){
                getline(tests, line);
                int n = atoi(line.c_str());
                q.delete_field(n);
            }
            else if (line == "DELETE_ROW"){
                getline(tests, line);
                int n = atoi(line.c_str());
                q.delete_row(n);
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
            }
        }
    }

}


int main(){
    char *filename = "prog.csv";
    char *fn_cpp_out = "out_cpp";
    char *fn_c_out = "out_c";

    test_c(filename, fn_c_out);
    test_cpp(filename, fn_cpp_out);

    ifstream check_c(fn_c_out);
    ifstream check_cpp(fn_cpp_out);
    string line_c, line_cpp;

    bool flag = true;
    while (getline(check_cpp, line_cpp)){
        getline(check_c, line_c);
        if(line_c != line_cpp){
            cout << "Something went wrong!" << endl;
            cout << "C: " << line_c << endl;
            cout << "C++: " << line_cpp << endl;
            flag = false;
        }
    }

    if (flag)
        cout << "Well done! The files are the same";
    return 0;
}
