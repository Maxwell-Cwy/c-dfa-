#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dfa.h"
#include "parse.h"

int main() {
    char expression[100];
    int result = 0;
    int back = 0;
    while (1) {
        State current = START;
        printf("**********���������**********\n");
        printf("������һ������������ʽ:");
        scanf("%s", expression);
        analays(expression, current);
        result = expr();
        printf("result:%d\n", result);
        printf("��1����:");
        scanf("%d", &back);
        if (back == 1) {
            system("cls\n");
        }
        memset(expression, 0, sizeof(expression));
    }
}

