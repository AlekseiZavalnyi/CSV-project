/*
 * File CSV_VERSION2.h
 * Header of a C++ class with vectors and iterator
 * Done by Oleksii Zavalnyi (computer mathematics 2)
 * Date 07.12.2021
 *
 */



#ifndef CSV_VERSION2_H_INCLUDED
#define CSV_VERSION2_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

/*
    ATTENTION! ACHTUNG!
    ALL FUNCTIONS ARE DESCRIBED IN THE CSV.h HEADER FILE
    WITH THE DYNAMIC ARRAY VERSION.
    NONE OF THE FUNCTION ARE CHANGED.
    EXCEPT FOR THE CONSOLE OUTPUT FUNCTION.
    THIS VERSION USES AN ITERATOR
*/

class csvFile{
public:


    csvFile(string fname, string fname_out);


    void fill_arr();


    void find_size();


    void row_by_number(int number);


    void read_current_row();


    void delete_row(int number);


    void change_row(string line, int number);


    void append_row(string line);


    void read_field_by_name(string name);


    void change_field(vector<string> column, int num);


    void read_square(int row, int col);


    void change_square(string name, int row, int col);


    void append_field(vector<string> column);


    void delete_field(int number);


    void print_data();


    string filename, fn_out;
    int rows, cols;
    int current_row ;
    vector<vector<string>> arr_csv;

    void change_data();

};

#endif // CSV_VERSION2_H_INCLUDED
