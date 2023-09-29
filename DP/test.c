#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dfs(int **isConnected, int* visited, int cities, int i) {
    for (int j = 0; j < cities; j++) {
        if (isConnected[i][j] == 1 && !visited[j]) {
            visited[j] = 1;
            dfs(isConnected, visited, cities, j);
        }
    }
}

int friends(int konw[][2], int knowRowSize, int knowColSize, int m, int n) {
    int *tmp = (int *)malloc(sizeof(int) * n * sizeof(int) * n);
    memset(tmp, 0, n * n);
    int **con = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        con[i] = tmp + (sizeof(int) * n * i);
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            con[i][j] = 0;
        }
    }
    
    for (int i = 0; i < knowRowSize; i++) {
        con[konw[i][0]][konw[i][1]] = 1;
        con[konw[i][1]][konw[i][0]] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            printf("%d ", con[i][j]);
        }
        putchar('\n');
    }


    int cities = n;
    int visited[cities];
    
    memset(visited, 0, sizeof(visited));
    int provinces = 0;

    for (int i = 0; i < n; i++) {
        int flag = 1;
        for (int j = 0; j < n; j++) {
            if (con[i][j] != 0)
                flag = 0;
        }
        if (flag) {
            visited[i] = 1;
            provinces++;
        }
    }
    for (int i = 0; i < cities; i++) {
        if (!visited[i]) {
            printf("i= %d\n", i);
            dfs(con, visited, cities, i);
            provinces++;
        }
    }
    return provinces;
}


int main()
{
    int know[3][2] = {{0, 1}, {1, 2}, {3, 4}};
    printf("%d\n", friends(know, 3, 2, 6, 6));

    return 0;
}
