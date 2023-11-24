#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Stack.h"
#include <math.h>

int isoperand(char sym){
    char operation[6] = "+-/*()";
    if (strchr(operation, sym) == NULL)
        return 0;
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
        if (isdigit(calc_str[i]))
            post_calc_str[k_num++] = calc_str[i];

        else if (isoperand(calc_str[i])) {
            post_calc_str[k_num++] = ' ';

            if (empty(calculator))
                push(calculator, create(calc_str[i]));

            else
            {
                if (calc_str[i] == '(')
                    push(calculator, create(calc_str[i]));

                else if (calc_str[i] == ')') {
                    symbol = (char) pop(calculator);

                    while (symbol != '(') {
                        post_calc_str[k_num++] = symbol;
                        symbol = (char) pop(calculator);
                    }
                }

                else if (priority(calc_str[i]) > priority((char) get(calculator)))
                    push(calculator, create(calc_str[i]));

                else {
                    while (priority(calc_str[i]) <=
                    priority((char) get(calculator))){
                        post_calc_str[k_num++] = (char) pop(calculator);
                        if (empty(calculator))
                            break;
                    }
                    push(calculator, create(calc_str[i]));
                }
            }
        }
        else
            return "syntax error";
    }

    while (!empty(calculator)) {
        post_calc_str[k_num++] = (char)pop(calculator);
    }

    post_calc_str[k_num] = '\0';
    return post_calc_str;
}

void calculating(char*post_calc_str, STACK * calculator){
    int post_calc_len = strlen(post_calc_str);
    char *number = (char*) malloc(sizeof (char));
    int num_len = 0;
    for (int i = 0;i < post_calc_len;i++){
        if (isdigit(post_calc_str[i])) {
            number[num_len++] = post_calc_str[i];
            number[num_len] = '\0';
        }
        if (isoperand(post_calc_str[i]) || post_calc_str[i] == ' '){
            int putin = 0;
            int raz = 0;
            for (int j = num_len - 1; j > -1;j--){
                int cur = ((int) number[j]) - 48;
                putin += cur * pow(10, raz);
                raz++;
            }
            if (putin != 0) {
                //printf("%d\n", putin);
                push(calculator, create(putin));
                for (int k = 0; k < num_len; k++)
                    number[k] = '\0';
                num_len = 0;
            }
        }
    }
    print(calculator);
}

int main(){
    char* calc_str;
    STACK * calculator;
    calculator = create(0);
    calc_str = (char*)malloc(sizeof(char));
    gets(calc_str);
    char* post_calc_str = PostFixPolka(calc_str, calculator);
    if (strcmp(post_calc_str, "syntax error") == 0){
        puts("syntax error");
        return 0;
    }
    printf("Polka: %s\n", post_calc_str);
    calculating(post_calc_str, calculator);

    free(post_calc_str);
    free(calc_str);

    return 0;
}
