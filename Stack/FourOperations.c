#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "SequenceStack.h"


/*
    postfixNotation:  中缀表达式转后缀
*/
void postfixNotation(char *fourStr, int sizeInfi){
    SStack *numStack = createStack();
    SStack *operator = createStack();
    int index = 0;

    // 遍历中缀表达式字符串
    while (fourStr[index]){

        // 如果是数字或者
        if (fourStr[index] >= '0' && fourStr[index] <= '9' || fourStr[index] == ' ' || fourStr[index] == '.'){
            numStack = push(numStack, fourStr[index]);
        }
        else if (fourStr[index] == '('){
            operator = push(operator, fourStr[index]);
        }

        // 遇到右括号时, 一直出栈, 存入数字栈, 直到遇到左括号
        else if (fourStr[index] == ')'){
            while (1){
                char opeChar = pop(operator);

                if (opeChar != '(')
                    numStack = push(numStack, opeChar);
                else
                    break;
            }
        }
        // 遇到运算符
        else{
            // 循环判断入栈运算符
            while (1){
                char topValue = 0;
                if (!isEmpty(operator)){
                    topValue = peek(operator);
                }

                // 当情况为: 字符栈为空(字符随意入栈), 栈顶为( , 栈顶为 + 或者 - 而入栈的位 * 或 /, 直接入字符栈
                // *或/只有在栈顶是+或-或者是(才可入栈
                if (!size(operator) || topValue == '(' || (topValue == '+' || topValue == '-') && (fourStr[index] == '*' || fourStr[index] == '/') ){
                    operator = push(operator, fourStr[index]);
                    break;
                }
                // 其他情况, 则需要先将字符栈的栈顶元素出队在进行判断
                else{
                    if (isEmpty(operator))
                        break;
                    char popChar = pop(operator);
                    numStack = push(numStack, popChar);
                }
            }
        }
        index++;
        
    }

    // 判断是否为空
    while (!isEmpty(operator)){
        push(numStack, pop(operator));
    }

    for (int i = sizeInfi - 1; i >= 0; i--){
        fourStr[i] = '\0';
    }

    for (int i = size(numStack) - 1; i >= 0; i --){
        fourStr[i] = pop(numStack);
    }

    destructStack(numStack);
    destructStack(operator);

}

double fourOperations(char *fourStr){
    // 2 32  5.0 +*72/+4-;
    int index = 0;

    int length = strlen(fourStr);

    double *sum = malloc(sizeof(*sum) * length);
    int sumIndex = 0;

    while (fourStr[index]){
        int startIndex = index;
        // printf("four %c\n", fourStr[index]);
        if (fourStr[index] >= '0' && fourStr[index] <= '9'){
            sum[sumIndex] = fourStr[index] - 48;
            printf("sum2 = %lf\n", sum[sumIndex]);
            // printf("sum1 = %lf\n", sum[sumIndex]);
            sumIndex++;
            index++;
        }
        else if (fourStr[index] == ' '){
            // printf("died\n");
            index++;
            printf("four1 %c\n", fourStr[index]);

            double decimal= 0;
            while (fourStr[index] != ' '){
                printf("four2 %c\n", fourStr[index]);
                if (fourStr[index] == '.')
                    decimal += 10;
                else if(decimal){
                    sum[sumIndex] = sum[sumIndex] + (fourStr[index] - 48) / decimal;
                    decimal *= 10;
                }
                else{
                    sum[sumIndex] = (int)sum[sumIndex] * 10 + (fourStr[index] - 48) + sum[sumIndex] - (int)sum[sumIndex];
                }
                index++;
                printf("sum1.5 = %lf\n", sum[sumIndex]);

            }
            printf("sum2 = %lf\n", sum[sumIndex]);

            
            sumIndex++;
            printf("%d\n", sumIndex);
            index++;
        }
        else{
            if (sumIndex < 2)
                continue;
            
            printf("%d\n", __LINE__);
            if (fourStr[index] == '+')
                sum[sumIndex - 2] = sum[sumIndex - 2] + sum[sumIndex - 1];
            else if (fourStr[index] == '-')
                sum[sumIndex - 2] = sum[sumIndex - 2] - sum[sumIndex - 1];
            else if (fourStr[index] == '*')
                sum[sumIndex - 2] = sum[sumIndex - 2] * sum[sumIndex - 1];
            else if (fourStr[index] == '/')
                sum[sumIndex - 2] = sum[sumIndex - 2] / sum[sumIndex - 1];
            // printf("sum3 = %lf\n", sum[sumIndex - 2]);
            sum[sumIndex - 1] = 0;
            sumIndex--;
            index++;
        }
    }
    return sum[0];
}

int main()
{
    // char infixExpression[] = "9+(3-1)* 3.2 + 10 /2"; // 20.4
    char infixExpression[] = "2*( 32 + 5.1 )+7/2-4"; // 73.7
    // char infixExpression[] = " 2.4 *4+(3+9)/6"; // 11.6

    int sizeInfi = sizeof(infixExpression) / sizeof(infixExpression[0]);

    postfixNotation(infixExpression, sizeInfi);
    printf("%s\n", infixExpression);

    printf("sum = %lf\n", fourOperations(infixExpression));
    

    return 0;
}