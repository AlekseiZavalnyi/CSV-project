/*
 * File CSV_VERSION2.cpp
 * Realization of a C++ class with vectors and iterator
 * Done by Oleksii Zavalnyi (computer mathematics 2)
 * Date 07.12.2021
 *
 */


#include "CSV_VERSION2.h"

using namespace std;


csvFile::csvFile(string fname, string fname_out){
        filename = fname;
        fn_out = fname_out;
        find_size();
        fill_arr();
        current_row = rand() % rows;
}


void csvFile::change_data(){
        ofstream out(fn_out);
        if(out.is_open()){
            for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                    if (j == cols-1)
                        out << arr_csv[i][j] << endl;
                    else
                        out << arr_csv[i][j] << ';';
                }
            }
        }
        out.close();
}



void csvFile::fill_arr(){
        ifstream in(filename);
        string line, word;
        if (in.is_open()){
            while (getline(in, line)){
                vector<string> v;
                stringstream str(line);
                while(getline(str, word, ';'))
                    v.push_back(word);
                arr_csv.push_back(v);
            }
        }
        in.close();
        find_size();
        change_data();
}

void csvFile::find_size(){
        ifstream in(filename);
        string line;
        rows = 0;
        cols = 0;
        if (in.is_open()){
            bool flag = true;
            cols++;
            while (getline(in, line)){
                rows++;
                if (flag){
                    for(int i = 0; i < line.size(); i++)
                        if (line[i] == ';') cols++;
                    flag = false;
                }
            }
        }
        in.close();
}

void csvFile::row_by_number(int number){
        if (number < 1 || number > rows){
            cout << "Enter number between 1 and " << rows << endl;
            exit(1);
        }
        for (int j = 0; j < cols; j++){
            cout << arr_csv[number-1][j] << " ";
        }
        current_row = number;
        cout << endl;
}

void csvFile::read_current_row(){
        row_by_number(current_row);
}

void csvFile::delete_row(int number){
        if (rows == 0){
            cout << "You cannot delete a row. The number of rows is zero" << endl;
            exit(1);
        }

        if (number < 1 || number > rows){
            cout << "Enter row number between 1 and " << rows << endl;
            exit(1);
        }
        rows--;
        arr_csv.erase(arr_csv.begin()+number-1);
        change_data();
}

void csvFile::change_row(string line, int number){
        if (number < 1 || number > rows){
            cout << "Enter number between 1 and " << rows << endl;
            exit(1);
        }
        string word;
        stringstream str(line);
        int k = 0;
        while (getline(str, word, ';')){
                arr_csv[number-1][k] = word;
                k++;
        }
        change_data();
}

void csvFile::append_row(string line){
        int n = 0;
        vector<string> v;
        string word;

        stringstream str(line);
        while (getline(str, word, ';')){
                v.push_back(word);
        }
        arr_csv.push_back(v);
        change_data();
        rows++;
}

void csvFile::read_field_by_name(string name){
        int k = 0;
        bool ex = false;
        for(int i = 0; i < cols; i++){
            if(name == arr_csv[0][i]){
                k = i;
                ex = true;
                break;
            }
        }
        if (ex){
            for (int i = 0; i < rows; i++)
                cout << arr_csv[i][k] << endl;
        }
}

void csvFile::change_field(vector<string> column, int num){
        if (column.size() != rows){
            cout << "column.size() != rows :" << column.size() << " != " << rows << endl;
            exit(1);
        }

        for(int i = 0; i < rows; i++){
            arr_csv[i][num-1] = column[i];
        }
        change_data();
}

void csvFile::read_square(int row, int col){
        if (row < 1 || row > rows){
            cout << "Enter row number between 1 and " << rows << endl;
            exit(1);
        }
        if (col < 1 || col > cols){
            cout << "Enter column number between 1 and " << rows << endl;
            exit(2);
        }
        cout << arr_csv[row-1][col-1] << endl;
}

void csvFile::change_square(string name, int row, int col){
        if (row < 2 || row > rows){
            cout << "Enter row number between 2 and " << rows << endl;
            exit(1);
        }
        if (col < 1 || col > cols){
            cout << "Enter column number between 1 and " << rows << endl;
            exit(2);
        }
        arr_csv[row-1][col-1] = name;
        change_data();
}

void csvFile::append_field(vector<string> column){
        if (column.size() != rows){
            cout << "column.size() != rows :" << column.size() << " != " << rows << endl;
            exit(1);
        }
        for (int i = 0; i < rows; i++){
            arr_csv[i].push_back(column[i]);
        }
        cols++;
        change_data();
}

void csvFile::delete_field(int number){
        if (cols == 0){
            cout << "You cannot delete a column. The number of columns is zero" << endl;
            exit(1);
        }

        if (number < 1 || number > cols){
            cout << "Enter column number between 1 and " << rows << endl;
            exit(2);
        }
        for (int i = 0; i < rows; i++){
            arr_csv[i].erase(arr_csv[i].begin()+number-1);
        }
        cols--;
        change_data();
}

void csvFile::print_data(){
    vector< vector<string>>::iterator row;
    vector<string>::iterator col;
    for (row = arr_csv.begin(); row != arr_csv.end(); row++) {
        for (col = row->begin(); col != row->end(); col++)
            cout << *col << "\t";
        cout << endl;
    }
    cout << endl;
}






