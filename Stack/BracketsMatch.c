#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "SequenceStack.h"

int main()
{
    char *matchStr = "{qwe[err(qwa)]";
    int strLength = strlen(matchStr);
    
    // 判断是否匹配失败, eg: [ 匹配到 )
    int matchFlag = 0;
    SStack *stack = createStack();

    for (int i = 0; i < strLength; i++){
        // 遇到左括号就入栈
        if (matchStr[i] == '(' || matchStr[i] == '{' || matchStr[i] == '['){
            push(stack, matchStr[i]);
        }
        // 遇到右括号, 出栈判断
        else if (matchStr[i] == ')' || matchStr[i] == '}' || matchStr[i] == ']'){
            char currentBracket = pop(stack);
            int asciiDiff = (int)matchStr[i] - (int)currentBracket;
            
            // 根据ASCII表可知, 相匹配的括号ASCII码相差1或2
            if (asciiDiff != 1 || asciiDiff != 2){
                matchFlag = 0;
                break;
            }
            matchFlag++;
        }

    }

    if (matchFlag && isEmpty(stack))
        printf("Bracket match success\n");
    else
        printf("Bracket match failed\n");

    destructStack(stack);

    return 0;
}