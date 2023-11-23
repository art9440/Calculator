#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Stack.h"


int isoperand(char sym){
    char operation[4] = "+-/*()";
    if (strchr(operation, sym) == NULL)
        return 0;
    return 1;
}


int checknear(char first, char second){
    if (isoperand(first) && isoperand(second) && strchr("()", first) == NULL
    && strchr("()", second) == NULL)
        return 0;
    if (first == "(" && second == ")" || first == ")" && second == "(")
        return 0;
    if (first == "(" && second == "(")
        return 1;
    if (first == ")" && second == ")")
        return 1;
}

int priority(char sym){
    switch (sym) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
            return 3;
        case ')':
            return 4;
    }
    return 0;
}


char* PostFixPolka(char *calc_str, STACK * calculator){
    char *post_calc_str;
    int calc_len = strlen(calc_str);
    post_calc_str = (char*)malloc(sizeof(char));
    int k_num = 0;
    for (int i = 0; i < strlen(calc_str); i++){
        if (isalpha(calc_str[i]) || isoperand(calc_str[i]) == 0)
            return "syntax error";
        if (checknear(calc_str[i], calc_str[i + 1]) == 0)
            return "syntax error";
        if (isdigit(calc_str[i])) {
            post_calc_str[k_num] == calc_str[i];
            k_num++;
        }
        if (isoperand(calc_str[i])){
            k_num++;
            if (empty(calculator) == 0 || get(calculator) == "(")
                push(calculator, create(calc_str[i]));
        }
    }
}


int main(){
    char* calc_str;
    STACK * calculator;
    calculator = create(0);
    calc_str = (char*)malloc(sizeof(char));
    scanf("%s", calc_str);
    char* post_calc_str = PostFixPolka(calc_str, calculator);
    if (strcmp(post_calc_str, "syntax error")) {
        puts("syntax error");
        return 0;
    }


    return 0;
}
