/*
 * File CSV_test.c
 * Realization of a C library testing
 * Done by Oleksii Zavalnyi (computer mathematics 2)
 * Date 07.12.2021
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CSV.h"

void case_1(int n, char f1[], char f2[]){

    writeToAnotherFile(f1, f2);

    start(f2);

    print(f2);

    char *s;
    printf("Enter a row: ");
    scanf("%s", s);
    int num;
    printf("Which line do you want to replace? ");
    scanf("%d", &num);
    changeRow(f2, s, num);
    print(f2);

    printf("Which line do you want to delete? ");
    scanf("%d", &num);
    removeRow(f2, num);
    print(f2);

    char *string;
    printf("Enter a row with separators ';' ");
    scanf("%s", string);
    rowToEOF(f2, string);
    print(f2);

    printf("Which column do you want to delete? ");
    scanf("%d", &num);
    removeColumnByNumber(f2, num);
    print(f2);

    char *column_names[6] = {"D", "d1", "d2", "d3", "d4", "d5"};
    appendColumn(f2, column_names);
    printf("\nAfter adding a column column_names\n");
    print(f2);

    char *name;
    printf("\nWhich general field name do you want to change? Enter a number ");
    scanf("%d", &num);
    printf("Enter a new name: ");
    scanf("%s", name);
    changeGeneralFieldName(f2, name, num);
    print(f2);

}


void case_2(int n, char f1[], char f2[]){
    writeToAnotherFile(f1, f2);

    start(f2);

    print(f2);
    printf("\n");
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
                print(f2);
                printf("\n");
            }
            else if (!strcmp(line,"DELETE_ROW")){
                fscanf(tests, "%s", line);
                int num = atoi(line);
                removeRow(f2, num);
                print(f2);
                printf("\n");
            }
            else if (!strcmp(line, "CHANGE_ROW")){
                fscanf(tests, "%s", line);
                int numb = atoi(line);
                fscanf(tests, "%s", line);
                changeRow(f2, line, numb);
                print(f2);
                printf("\n");
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
                print(f2);
                printf("\n");
            }
            else if (!strcmp(line, "CHANGE_GEN_FIELD_NAME")){
                fscanf(tests, "%s", line);
                int num_of_col = atoi(line);
                fscanf(tests, "%s", line);
                changeGeneralFieldName(f2, line, num_of_col);
                print(f2);
                printf("\n");
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
                print(f2);
                printf("\n");
            }
            else if (!strcmp(line, "DELETE_COLUMN")){
                fscanf(tests, "%s", line);
                int numb_col = atoi(line);
                removeColumnByNumber(f2, numb_col);
            }
        }
    }

}


int main(){

    int n = 0;
    printf("Do you want to enter values from the console or from a file? (1 or 2) ");
    scanf("%d", &n);
    printf("Warning! The values will be output to the console and \nto an information file\n\n");


    //The name of the non-empty data file
    char *fn = "prog.csv";

    //The name of the empty data file
    char *fn_out = "prog_res.csv";

    if (n == 1) case_1(n, fn, fn_out);
    if (n == 2) case_2(n, fn, fn_out);
    return 0;
}
