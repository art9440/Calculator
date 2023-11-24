#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Stack.h"


int isoperand(char sym){
    char operation[6] = "+-/*()";
    if (strchr(operation, sym) == NULL)
        return 0;
    return 1;
}


int checknear(char first, char second){
    if (isoperand(first) && isoperand(second) && strchr("()", first) == NULL
    && strchr("()", second) == NULL)
        return 0;
    if (first == '(' && second == ')' || first == ')' && second == '(')
        return 0;
    if (first == '(' && second == '(')
        return 1;
    if (first == ')' && second == ')')
        return 1;
}


int priority(char sym){
    switch (sym) {
        case '+':
        case '-':
            return 3;
        case '*':
        case '/':
            return 4;
        case '(':
            return 1;
        case ')':
            return 2;
        default:
            return 0;
    }
}


char* PostFixPolka(char *calc_str, STACK * calculator) {
    char *post_calc_str;
    int calc_len = strlen(calc_str);
    post_calc_str = (char *) malloc((calc_len + 1) * sizeof(char));
    int k_num = 0;
    char symbol;
    for (int i = 0; i < calc_len; i++) {
        /*if (isalpha(calc_str[i]) || isoperand(calc_str[i]) == 0)
            return "syntax error";
        if (checknear(calc_str[i], calc_str[i + 1]) == 0)
            return "syntax error";*/

        if (isdigit(calc_str[i])) {
            post_calc_str[k_num++] = calc_str[i];
        }
        else if (isoperand(calc_str[i])) {
            post_calc_str[k_num++] = ' ';

            if (empty(calculator)) {
                push(calculator, create(calc_str[i]));
            }
            else {
                if (calc_str[i] == '(') {
                    push(calculator, create(calc_str[i]));
                } else if (calc_str[i] == ')') {
                    symbol = (char) pop(calculator);
                    while (symbol != '(') {
                        post_calc_str[k_num++] = symbol;
                        symbol = (char) pop(calculator);
                    }
                } else if (priority(calc_str[i]) > priority((char) get(calculator))) {
                    push(calculator, create(calc_str[i]));
                } else {
                    while (priority(calc_str[i]) <= priority((char) get(calculator))) {
                        post_calc_str[k_num++] = (char) pop(calculator);
                        if (empty(calculator))
                            break;
                    }
                    push(calculator, create(calc_str[i]));
                }
            }
        }

    }

    while (!empty(calculator)) {
        post_calc_str[k_num++] = (char)pop(calculator);
    }

    post_calc_str[k_num] = '\0';
    return post_calc_str;
}



int main(){
    char* calc_str;
    STACK * calculator;
    calculator = create(0);
    calc_str = (char*)malloc(sizeof(char));
    gets(calc_str);
    char* post_calc_str = PostFixPolka(calc_str, calculator);
    /*if (strcmp(post_calc_str, "syntax error")) {
        puts("syntax error");
        return 0;
    }*/
    printf("%s", post_calc_str);

    free(post_calc_str);
    free(calc_str);
    return 0;
}
