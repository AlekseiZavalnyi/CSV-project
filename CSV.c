/*
 * File CSV.c
 * Realization of a C library
 * Done by Oleksii Zavalnyi (computer mathematics 2)
 * Date 07.12.2021
 *
 */


#include "CSV.h"


char ARR_CSV[1024][256];
int COLS = 0, ROWS = 0;


void arr_print(){
    for (int i = 0; i < ROWS; i++)
    printf("%s", ARR_CSV[i]);
}

void writeToAnotherFile(char filename1[], char filename2[]){
    FILE *file1 = fopen(filename1, "r");
    FILE *file2 = fopen(filename2, "w");
    char line[256];
    while(fgets(line, sizeof(line), file1) != NULL){
        fputs(line, file2);
    }
    fclose(file1);
    fclose(file2);
}


void file_write(char filename[]){
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < ROWS; i++)
        fputs(ARR_CSV[i], file);
    fclose(file);
}


void fill_arr(char filename[]){ // fill the array with data from the file
    FILE *file = fopen(filename, "r");
    int i = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)){
        strcpy(ARR_CSV[i], line);
        i++;
    }
    fclose(file);
}


int num_of_cols(char *s) {
    int count = 0;
    for(int i = 0; i < s[i]; i++){
    	if(s[i] == ';')
          count++;
 	}
 	count++;
 	return count;
}


void get_size(char filename[]){ // find the value of ROWS and COLS
    FILE *file = fopen(filename, "r");
    if (!file) exit(1);
    int flag = 1;
    char line[256];
    while(fgets(line, sizeof(line), file) != NULL){
         ROWS++;
         if (flag){
             COLS = num_of_cols(line);
             flag = 0;
         }
    }
    fclose(file);
}

void start(char filename[]){ // to avoid calling two functions
    get_size(filename);
    fill_arr(filename);
}

const char* getfield(char* line, int num){ // returns the word by its number in the line
    const char* tok;
    for (tok = strtok(line, ";");
            tok && *tok;
            tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}


void print(char filename[]){ // prints data from the file
    FILE* file = fopen(filename, "r");
    char line[256];
    while (fgets(line, sizeof(line), file)){
        for (int i = 0; i < COLS; i++){
            char* tmp = strdup(line);
            printf("%s\t", getfield(tmp, i+1));
            free(tmp);
        }
        printf("\n");
    }
    fclose(file);
}

char* concat(char *s1, char *s2){ // connects two lines
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    return result;
}


void changeRow(char filename[], char string[], int number){
    int n = num_of_cols(string);
    if (n != COLS) {
        printf("The number of columns in the row is incorrect!");
        exit(2);
    }

    if (number > ROWS || number < 1){
        printf("The number is incorrect! There is no row with this number");
        exit(1);
    }

    string = concat(string, "\n");
    strcpy(ARR_CSV[number-1], string);
    file_write(filename);
}

void removeRow(char filename[], int number){
    if (COLS == 0){
        printf("You cannot delete a row. The number of rows is zero\n");
        exit(2);
    }

    if (number > ROWS || number < 1){
        printf("The number is incorrect! There is no row with this number");
        exit(1);
    }
    for (int i = number-1; i < ROWS-1; i++){
        strcpy(ARR_CSV[i], ARR_CSV[i+1]);
    }
    strcpy(ARR_CSV[ROWS-1], "\0");
    file_write(filename);
    ROWS--;
}

void rowToEOF(char filename[], char string[]){
    int n = num_of_cols(string);
    if (n != COLS) {
        printf("The number of columns in your row is incorrect!");
        exit(1);
    }

    strcpy(ARR_CSV[ROWS], string);
    ROWS++;
    file_write(filename);
}


char* replace_word(const char* s, const char* oldW, const char* newW){ // changes the occurrence of one one word
    char* result;                                                      // by another
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;
            i += oldWlen - 1;
        }
    }
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
    i = 0;
    while (*s) {
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }
    result[i] = '\0';
    return result;
}


void changeColumn(char filename[], char **columns, int n){
    if (n > COLS || n < 1){
        printf("The number of column = %d is incorrect!", n);
        exit(2);
    }

    int k = 0;
    FILE *file = fopen(filename, "r");

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL){
        char dst[256];
        strcpy(dst, line);
        char *f = getfield(dst, n);
        char *string = replace_word(line, f, columns[k]); // replaces old value with new value
        strcpy(ARR_CSV[k], string);
        k++;
    }
    fclose(file);
    file_write(filename);
}

void changeColumnByName(char filename[], char *columns[], char name[]){
    FILE *file = fopen(filename, "r");
    char line[1024];
    fgets(line, sizeof(line), file);
    int cols = num_of_cols(line);
    int n = 0;

    for(int i = 0; i < cols; i++){
        char dst[256];
        strcpy(dst, line);
        char *f = getfield(dst, i+1);
        if (!strcmp(f, name)){
            n = i+1;
            break;
        }
    }
    changeColumn(filename, columns, n);
    file_write(filename);
}

void remove_substring(char *str, char *sub){ // removes word from the line. Used to remove one column
    int length = strlen(sub);                                                    // from the file data
    while((str = strstr(str, sub))){
        memmove(str, str + length, 1 + strlen(str + length));
    }
}

void removeColumnByNumber(char filename[], int n){
    if (COLS == 0){
        printf("You cannot delete a column. The number of columns is zero\n");
        exit(2);
    }

    if (n > COLS || n < 1){
        printf("The number of column = %d is incorrect!\n", n);
        exit(2);
    }

    FILE *file = fopen(filename, "r");
    char line[256];
    for (int i = 0; i < ROWS; i++){
        fgets(line, sizeof(line), file);
        char dst[256];
        strcpy(dst, line);
        char *word = getfield(dst, n);
        if (n == 1){ // if we removes first word from the row. First word does not have ';' at the beginning
            word = concat(word, ";");
            remove_substring(line, word);
        }
        else{
            word = concat(";", word);
            remove_substring(line, word);
        }
        strcpy(ARR_CSV[i], line);
    }
    fclose(file);
    COLS--;
    file_write(filename);
}

void removeColumnByName(char filename[], char name[]){
    int n = NULL;
    for(int j = 1; j <= COLS; j++){
        char string[256];
        strcpy(string, ARR_CSV[0]);
        char *word = getfield(string, j);
        if (!strcmp(word, name)){
            int n = j;
            break;
        }
    }
    if (n != NULL) removeColumnByNumber(filename, n);
}

void changeGeneralFieldName(char filename[], char name[], int n){
    if (n > COLS || n < 1){
        printf("The number of column = %d is incorrect!", n);
        exit(2);
    }

    char string[256];
    strcpy(string, ARR_CSV[0]);
    char *word = getfield(string, n);
    strcpy(ARR_CSV[0], replace_word(ARR_CSV[0], word, name));
    file_write(filename);
}

void changeSquareName(char filename[], char name[], int row, int col){
    if (row > ROWS || row < 2){
        printf("The number of row = %d is incorrect!", row);
        exit(1);
    }
        if (col > COLS || col < 1){
        printf("The number of column = %d is incorrect!", col);
        exit(2);
    }

    char string[256];
    strcpy(string, ARR_CSV[row-1]);
    char *word = getfield(string, col);
    strcpy(ARR_CSV[row-1], replace_word(ARR_CSV[row-1], word, name));
    file_write(filename);
}

void printRowByNumber(int n){
    if (n < 1 || n > ROWS){
        printf("The number of row = %d is incorrect!", n);
        exit(1);
    }
    printf("%s\n", ARR_CSV[n-1]);
}

void printFieldByNumber(int n){
    if (n > COLS || n < 1){
        printf("The number of column = %d is incorrect!", n);
        exit(2);
    }

    for(int i = 0; i < ROWS; i++){
        char dst[256];
        strcpy(dst, ARR_CSV[i]);
        char *word = getfield(dst, n);
        printf("%s\n", word);
    }
    printf("\n");
}

void printSquareByNumber(int n, int m){
    if (m > COLS || m < 1){
        printf("The number of column = %d is incorrect!\n", n);
        exit(2);
    }
    if (n < 1 || n > ROWS){
        printf("The number of row = %d is incorrect!\n", n);
        exit(1);
    }
    char string[256];
    strcpy(string, ARR_CSV[n-1]);
    printf("square(%d, %d) is %s\n", n, m, getfield(string, m));
}


void appendColumn(char filename[], char *column[]){
    COLS++;
    for (int i = 0; i < ROWS; i++){
        char *word = concat(";", column[i]);
        ARR_CSV[i][strlen(ARR_CSV[i])-1] = '\0';
        word = concat(word, "\n");
        strcpy(ARR_CSV[i], concat(ARR_CSV[i], word));
    }
    file_write(filename);
}

