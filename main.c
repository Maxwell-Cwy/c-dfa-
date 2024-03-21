#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef enum {
    START,
    DIGIT,
    OP,
    L,
    R,
    ERROR
} State;

typedef struct {
    char value[20];
    int id;
}Token;

Token token[100];
char chbuf[100];
char* p;
int count = 0;
int num = 0;
Token* t = token;
int isdigit(char ch);
State DFA(char* input);
void analays(char* p, State current);

int exp();
int exp_p(int temp);
int term();
int term_p(int temp);
int factor();

/*
int main() {
    char expression[100];
    State current = START;
    p = expression;
    printf("请输入一个四则运算表达式:");
    scanf("%s", expression);
    analays(p, current);

    for (int j = 0; token[j].id != 0; j++) {
        printf("%s   ", token[j].value);
    }
    while (1);
}
*/

int main() {
    char expression[100];
    State current = START;
    p = expression;
    int result = 0;
    printf("请输入一个四则运算表达式:");
    scanf("%s", expression);
    analays(p, current);
    result = exp(t);
    printf("result:%d", result);
}




int isdigit(char ch) {
    if (ch < 58 && ch>47) {
        return 1;
    }
    else {
        return 0;
    }
}

State DFA(char* input) {
    if (isdigit(*input)) {
        chbuf[count] = *input;
        count++;
        return DIGIT;
    }
    if ((*input) == '(') {
        chbuf[count] = *input;
        count++;
        return L;
    }

    if ((*input) == ')') {
        chbuf[count] = *input;
        count++;
        return R;
    }
    if (*input == '+' || *input == '-' || *input == '*' || *input == '/' || *input == '\0') {
        chbuf[count] = *input;
        count++;
        return OP;
    }

    else {
        return ERROR;
    }

}
void cpy(char* p1, char* p2) {
    int i;
    for (i = 0; p1[i] != '\0'; i++) {
        p1[i] = p2[i];
    }
}


void analays(char* p, State current) {
    int i;
    for (i = 0; *p != '\0'; i++) {
        current = DFA(p);
        if (current == DIGIT && (!isdigit(*(p + 1)))) {
            printf("digit:%s\n", chbuf);
            strcpy(token[num].value, chbuf);
            token[num].id = 1;
            num++;
            memset(chbuf, 0, sizeof(chbuf));
            count = 0;
        }
        if (current == OP) {
            printf("OP:%s\n", chbuf);
            strcpy(token[num].value, chbuf);
            token[num].id = 2;
            num++;
            memset(chbuf, 0, sizeof(chbuf));
            count = 0;
        }
        if (current == L) {
            printf("L:%s\n", chbuf);
            strcpy(token[num].value, chbuf);
            token[num].id = 3;
            num++;
            memset(chbuf, 0, sizeof(chbuf));
            count = 0;
        }
        if (current == R) {
            printf("R:%s\n", chbuf);
            strcpy(token[num].value, chbuf);
            token[num].id = 4;
            num++;
            memset(chbuf, 0, sizeof(chbuf));
            count = 0;
        }
        if (current == ERROR) {
            printf("invalid!\n");
            memset(chbuf, 0, sizeof(chbuf));
            count = 0;
            break;
        }
        p++;
    }
}

int exp() {
    int result_e,t1;
    t1=term();
    result_e=exp_p(t1);
    return result_e;
}

int exp_p(int temp) {//A(+B)(+C)
    int result_ep,t1,t2;
    if (t->id == 2 && t->value[0] == '+') {
        t++;
        t1=term();
        t2 = temp + t1;
        result_ep = exp_p(t2);
        return result_ep;
    }
    if (t->id == 2 && t->value[0] == '-') {
        t++;
        t1 = term();
        t2 = temp - t1;
        result_ep = exp_p(t2);
        return result_ep;
    }
    else {
        result_ep = temp;
        return result_ep;
    }
}

int term() {//A(*B)
    int result_t,t1;
    t1=factor();
    result_t =term_p(t1);
    return result_t;
}

int term_p(int temp) {//A*B(*C)
    int result_tp, t1;
    if (t->id == 2 && t->value[0] == '*') {
        t++;
        t1 = temp*factor();
        result_tp = term_p(t1);
        return result_tp;
    }

    if (t->id == 2 && t->value[0] == '/') {
        t++;
        t1 = temp / factor();
        result_tp = term_p(t1);
        return result_tp;
    }

    else {
        result_tp= temp;
        return result_tp;
    }
}

int factor() {
    int result_f;
    if (t->id == 1) {
        result_f = atoi(t->value);//识别出数字字符
        t++;
        return result_f;
    }
    if (t->id == 3) {//识别出左括号字符
        t++;
        result_f =exp();//识别出表达式，指针+1;
        if (t->id == 4) //识别出右括号字符
            t++;
        return result_f;
    }
    else {
        printf("parse error!");
        exit(1);
    }
}