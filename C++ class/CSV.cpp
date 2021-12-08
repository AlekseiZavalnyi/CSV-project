/*
 * File CSV.cpp
 * Version with dynamic array
 * Realization of a C++ class
 * Done by Oleksii Zavalnyi (computer mathematics 2)
 * Date 07.12.2021
 *
 */


#include "CSV.h"
using namespace std;


csvFile::csvFile(string fname, string fname_out){
        filename = fname;
        fn_out = fname_out;
        find_size();
        current_row = (rand() % rows) + 1;
        arr_csv = make_arr();
        fill_arr();
}

string** csvFile:: make_arr(){
        string** array2D = NULL;
        array2D = new string*[rows];
        for (int h = 0; h < rows; h++){
            array2D[h] = new string[cols];
        }
        return array2D;
}

void csvFile::delete_arr(string **arr, int n){
    for(int i = 0; i < n; i++)
        delete[] arr[i];
    delete[] arr;
}

void csvFile::fill_arr(){
        ifstream in(filename);
        string line, word;
        int n = 0;
        if (in.is_open()){
            while (getline(in, line)){
                stringstream str(line);
                int k = 0;
                while(getline(str, word, ';')){ // read all words through the separator
                    arr_csv[n][k] = word;
                    k++;
                }
                n++;
            }
        }
        in.close();
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
                    flag = false; // you can only count from the first line
                }
            }
        }
        in.close();
}

void csvFile :: row_by_number(int number){
        if (number < 1 || number > rows){ // the value must not exceed the file size
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
            cout << "You cannot delete a row. The number of rows is zero!" << endl;
            exit(1);
        }

        if (number < 1 || number > rows){
            cout << "Enter row number between 1 and " << rows << endl;
            exit(1);
        }

        rows--;
        string** arr_temp = make_arr();
        for (int i = number-1; i < rows; i++){ // using writing to another array
            for (int j = 0; j < cols; j++)
                arr_csv[i][j] = arr_csv[i + 1][j];
        }
        for(int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++)
                arr_temp[i][j] = arr_csv[i][j];
        }

        delete_arr(arr_csv, rows+1); // delete array with not appropriate size

        arr_csv = make_arr(); // create an array of the right size

        for (int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++)
                arr_csv[i][j] = arr_temp[i][j];
        }

        delete_arr(arr_temp, rows); // delete auxiliary array
        change_data();
}

void csvFile::change_row(string line, int number){
        if (number < 1 || number > rows){
            cout << "Enter number between 1 and " << rows << endl;
            exit(1);
        }
        stringstream str(line);
        string word;
        int k = 0;
        while(getline(str, word, ';')){
            arr_csv[number-1][k] = word;
            k++;
        }
        change_data();
}

void csvFile::append_row(string line){
        int n = 0;
        for (int i = 0; i < line.size(); i++){ // count the number of columns in line
            if (line[i] == ';') n++;
        }

        if (n != cols-1){
            cout << "The number of columns in line is not equal to the number of columns in file!" << endl;
            exit(2);
        }

        rows++;
        string** arr_temp = make_arr();

        for(int i = 0; i < rows-1; i++){
            for (int j = 0; j < cols; j++)
                arr_temp[i][j] = arr_csv[i][j];
        }

        delete_arr(arr_csv, rows-1);

        arr_csv = make_arr(); // make an array with the value of the rows+1

        for(int i = 0; i < rows-1; i++){
            for (int j = 0; j < cols; j++)
                arr_csv[i][j] = arr_temp[i][j];
        }

        delete_arr(arr_temp, rows-1);

        change_row(line, rows);
        change_data();
}

void csvFile::read_field_by_name(string name){
        int k = 0;
        for(int i = 0; i < cols; i++){
            if(name == arr_csv[0][i]){ // find the number of the word in the line
                k = i;
                break;
            }
        }
        for (int i = 0; i < rows; i++)
            cout << arr_csv[i][k] << endl;
}

void csvFile::change_field(string *column, int num){
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
        if (row < 2 || row > rows){ // there another function to change the value in the first row
            cout << "Enter row number between 2 and " << rows << endl;
            exit(1);
        }
        if (col < 1 || col > cols){
            cout << "Enter column number between 2 and " << rows << endl;
            exit(2);
        }
        arr_csv[row-1][col-1] = name;
        change_data();
}

void csvFile::append_field(string *column){
        string** arr_temp = make_arr();

        for(int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++)
                arr_temp[i][j] = arr_csv[i][j];
        }

        delete_arr(arr_csv, rows-1);

        cols++;
        arr_csv = make_arr();

        for(int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                if (j < cols-1)
                    arr_csv[i][j] = arr_temp[i][j];
                else
                    arr_csv[i][j] = column[i];
            }
        }

        delete_arr(arr_temp, rows);

        change_data();
}

void csvFile::delete_field(int number){
        if (cols == 0){
            cout << "You cannot delete a column. The number of columns is zero!" << endl;
            exit(2);
        }

        if (number < 1 || number > cols){
            cout << "Enter column number between 1 and " << rows << endl;
            exit(2);
        }

        cols--;
        string** arr_temp = make_arr();

        for(int i = 0; i < rows; i++){
            for(int j = 0; j < number-1; j++)
                arr_temp[i][j] = arr_csv[i][j];

            for(int j = number; j < cols+1; j++)
                arr_temp[i][j-1] = arr_csv[i][j];
        }

        delete_arr(arr_csv, rows);

        arr_csv = make_arr();
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++)
                arr_csv[i][j] = arr_temp[i][j];
        }
        delete_arr(arr_temp, rows);

        change_data();
}

void csvFile::print_data(){
        for (int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++)
                cout << arr_csv[i][j] << "\t";
            cout << endl;
        }
        cout << endl;
}


void csvFile::change_data(){ // write the new data in the file from the array
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
