/*
 * File CSV.h
 * Version with dynamic array
 * Header for a C++ class
 * Done by Oleksii Zavalnyi (computer mathematics 2)
 * Date 07.12.2021
 *
 */


#ifndef CSV_H_INCLUDED
#define CSV_H_INCLUDED
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class csvFile{
private:

    /** Files we work with
    *
    * \param filename - non empty file with the data
    * \param fn_out - file were the results are written
    *
    */
    string filename, fn_out;


    /** The number of rows and columns of the file
    *
    * \param rows - number of rows in the file
    * \param cols - number of columns in the file
    *
    */
    int rows, cols;


    /** Current row
    *
    * \param current_row - number of the current row
    *
    */
    int current_row;


    /** \ This is where the values of the CSV file are stored.
    * \param arr_csv
    */
    string **arr_csv;

    /** Function to change data in fn_out
    *
    *
    */
    void change_data();


public:
    csvFile(string fname, string fname_out);

    /** Makes a two dimensional dynamic array
    *
    * \return array2D - two dimensional dynamic array[rows][cols]
    *
    */
    string** make_arr();

    /** Deletes a two dimensional dynamic array
     *
     */
    void delete_arr(string **arr, int n);

    /** \ This is where the values from the filename are writes to the arr_csv at the first time
    *
    * \param filename
    *
    */
    void fill_arr();


    /** The function finds rows and cols values
    *
    * \param filename
    */
    void find_size();


    /** Outputs a string by number to the console
    *
    * \param n - number of the row we want to print
    *
    */
    void row_by_number(int number);


    /** Reads row with number current_row
    *
    */
    void read_current_row();


    /** Removes the row from file by number
    *
    * \param number - the number of the row we want to delete
    *
    */
    void delete_row(int number);


    /** Changes the row from file to the value of string
    *
    * \param line - new row
    * \param number - the number of the row we want to change
    *
    */
    void change_row(string line, int number);


    /** Appends a new line to the end of the file
    *
    * \param line - the line we append
    *
    */
    void append_row(string line);


    /** Prints values of the field
    *
    * \param name - name of the field
    *
    */
    void read_field_by_name(string name);


    /** Changes one column of the file to another
    *
    * \param column - an array of words to insert
    * \param nun - nunber of the column we wish to change
    *
    */
    void change_field(string *column, int num);


    /** Prints the value of the square
    *
    * \param row - number of the row on which the value is located
    * \param col - number of the column on which the value is located
    *
    */
    void read_square(int row, int col);


    /** Changes the value of the one square
    *
    * \param name - new name of the square
    * \param row - the number of the row where the word is located (1 <= row <= ROWS)
    * \param col - the number of the column where the word is located (1 <= row <= COLS)
    *
    */
    void change_square(string name, int row, int col);


    /** Adds a new column to the file on the right
    *
    * \param column - an array of the values (the column size is limited by the ROWS value)
    *
    */
    void append_field(string *column);


    /** Deletes a column from the file by number
    *
    * \param number - number of the column
    *
    */
    void delete_field(int number);


    /** Prints all data from the file fn_out
    *
    */
    void print_data();
};

#endif // CSV_H_INCLUDED
