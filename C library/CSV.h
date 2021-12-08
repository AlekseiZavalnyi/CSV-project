/*
 * File CSV.h
 * Header of a C library
 * Done by Oleksii Zavalnyi (computer mathematics 2)
 * Date 07.12.2021
 *
 */


#ifndef CSV_H_INCLUDED
#define CSV_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** \ This is where the values of the CSV file. To avoid to open the file all the time
 * \param ARR_CSV
 */
extern char ARR_CSV[1024][256];


/** The number of rows and columns of the file
 *
 * \param ROWS - number of rows in the file
 * \param COLS - number of columns in the file
 *
 */
extern int COLS, ROWS;

void arr_print();

/** Writes the data from one file to another
 *
 * \param filename1 - information is taken from this file
 * \param filename2 - information is written to this file
 *
 */
void writeToAnotherFile(char filename1[], char filename2[]);


/** \ This is where the values from the array are written to the function. Do not use the function
 *
 * \param filename
 *
 */
void file_write(char filename[]);


/** This function fills the array from the source file. Do not use the function
 *
 * \param filename
 *
 */
void fill_arr(char filename[]);


/** The function finds the number of columns in the row. Do not use the function
 *
 * \param s - string(row)
 * \return number of columns
 *
 */
int num_of_cols(char *s);


/** The function finds ROWS and COLS values
 *
 * \param filename
 */
void get_size(char filename[]);


/** The function calls functions fill_arr and get_size.
 * Be sure to call the function after entering the file name
 */
void start(char filename[]);


/** Finds the field by the given number in the row.
 *
 * \param line - a line with separators ';'
 * \param num - number of the word (from 1 to line.size())
 * \return field
 *
 */
const char* getfield(char* line, int num);


/** Outputs the file value to the console
 *
 * \param filename
 *
 */
void print(char filename[]);


/** Connects the two strings
 *
 * \param s1
 * \param s2
 * \return result - s1+s2
 *
 */
char* concat(char *s1, char *s2);


/** Changes the row from file to the value of string
 *
 * \param filename
 * \param string - new line
 * \param number - the number of the row we want to change
 *
 */
void changeRow(char filename[], char string[], int number);


/** Removes the row from file by number
 *
 * \param filename
 * \param number - the number of the row we want to delete
 *
 */
void removeRow(char filename[], int number);


/** Appends a new line to the end of the file
 *
 * \param filename
 * \param string - the line we append
 *
 */
void rowToEOF(char filename[], char string[]);


/** Replaces the occurrence of one word with another
 *
 * \param s - string
 * \param oldW - an old word
 * \param newW - a new word
 * \return a string with a new word in place of the old word
 *
 */
char* replace_word(const char* s, const char* oldW, const char* newW);


/** Changes one column of the file to another
 *
 * \param columns - an array of words to insert
 * \param filename
 * \param n - number of the column we wish to change
 *
 */
void changeColumn(char filename[], char **columns, int n);


/** Changes one column of the file to another
 *
 * \param filename
 * \param columns - an array of words to insert
 * \param name - name of the column we wish to change
 *
 */
void changeColumnByName(char filename[], char **columns, char name[]);



/** Deletes a substring in the string
 *
 * \param str - string
 * \param sub - substring
 *
 */
void remove_substring(char *str, char *sub);


/** Deletes a column from the file by number
 *
 * \param filename
 * \param n - number of the column
 *
 */
void removeColumnByNumber(char filename[], int n);


/** Deletes a column from the file by name of the first field
 *
 * \param filename
 * \param name - name of the first field
 * \return
 *
 */
void removeColumnByName(char filename[], char name[]);


/** Changes the name of the field in the first row
 *
 * \param filename
 * \param name - new name of the field
 * \param n - number of the field we wish to change
 *
 */
void changeGeneralFieldName(char filename[], char name[], int n);


/** Changes the value of the one square
 *
 * \param name - new name of the square
 * \param row - the number of the row where the word is located (1 <= row <= ROWS)
 * \param col - the number of the column where the word is located (1 <= row <= COLS)
 *
 */
void changeSquareName(char filename[], char name[], int row, int col);


/** Outputs a row by number to the console
 *
 * \param n - number of the row we want to print
 *
 */
void printRowByNumber(int n);


/** Outputs a column by number to the console
 *
 * \param n - number of the column we want to print
 *
 */
void printFieldByNumber(int n);


/** Outputs one square by number to the console
 *
 * \param n - number of the row of the square
 * \param m - number of the column of the square
 */
void printSquareByNumber(int n, int m);

/** Adds a new column to the file on the right
 *
 * \param filename - file
 * \param column - an array of the values (the column size is limited by the ROWS value)
 *
 */
void appendColumn(char filename[], char **column);


#endif // CSV_H_INCLUDED
