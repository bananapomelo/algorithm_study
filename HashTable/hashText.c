#include <stdio.h>
#include <stdlib.h>

int hashFunc(int key) {
    return key - 1;
}

void saveByHash(int *a, int key, int value) {
    a[hashFunc(key)] = value;

    return ;
}

int findValue(int *studentGrade, int key) {
    return studentGrade[hashFunc(key)];
}

int main()
{
    int *studentGrade = (int *)malloc(sizeof(*studentGrade) * 100);
    
    while (1) {
        printf("请输入年龄和对应人口: ");
        int age, population = 0;
        scanf("%d%d", &age, &population);
        if (age <= 0 || age > 100)
            break;

        saveByHash(studentGrade, age, population);
    }

    while (1) {
        printf("请输入查找的年龄:");
        int age = -1;
        scanf("%d", &age);
        if (age > 100 || age <= 0)
            break;
        
        printf("年龄为 %d, 人口为 %d\n", age, findValue(studentGrade, age));

    }


    free(studentGrade);
    studentGrade = NULL;

    return 0;
}