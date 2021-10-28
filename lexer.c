#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define KEYWORD_AMOUNT 2
bool isKeyword(char* str){
    char keywords[KEYWORD_AMOUNT][10] = {
    "if", "else"};

    int i;
    for (i = 0; i < KEYWORD_AMOUNT; ++i){
        if (strcmp(keywords[i], str) == 0){
            return(true);
        }
    }
    return (false);

}

#define OPERATOR_AMOUNT 8
bool isOperator(char ch){
    char operators[OPERATOR_AMOUNT][1] = {
    '+', '-', '/', '*', '%', '<', '>', '='};

    int i;
    for (i = 0; i < OPERATOR_AMOUNT; ++i){
        if (ch == *operators[i]){
            return(true);
        }
    }
    return (false);
}

#define DELIMITER_AMOUNT 20
bool isDelimiter(char ch){
    char delimiter[DELIMITER_AMOUNT][1] = {
    ' ', '+', '-', '*', '/', ',', ';', '<',
    '>', '=', '(', ')', '[', ']', '{', '}',
    '\n', '\t', '\"', '\''};

    int i;
    for (i = 0; i < DELIMITER_AMOUNT; ++i){
        if (ch == *delimiter[i]){
            return(true);
        }
    }
    return (false);
}

#define BUFFER_SIZE 25
int main(){
    FILE *sourceFile = fopen("program.newlanguage", "r");
    if(sourceFile == NULL){
        printf("ERROR: CANNOT OPEN FILE\n");
        exit(0);
    }

    char ch, buffer[BUFFER_SIZE];
    int i = 0;
    int line = 1;
    printf("%s |  %s  | %s\n", "LINE", "TYPE", "TOKEN");
    while ((ch = fgetc(sourceFile)) != EOF){

        if (isalnum(ch)){
            buffer[i++] = ch;
        }
        else if (isOperator(ch) == true){
            printf("%d |\t%s:\t %c\n", line, "OPERATOR", ch, line);
        }

        if (isDelimiter(ch) == true && i != 0){
            buffer[i] = '\0';
            i = 0;
            if (isKeyword(buffer) == true){
                printf("%d |\t%s:\t %s\n", line, "KEYWORD", buffer);
            }
            else{
                printf("%d |\t%s:\t %s\n", line, "IDENTIFIER", buffer); 
            }
        }

        if (ch == '\n'){
            ++line;
        }
    }
    fclose(sourceFile);
    return 0;
}

