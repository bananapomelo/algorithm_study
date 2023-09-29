void dfs(int** isConnected, int* visited, int cities, int i) {
    for (int j = 0; j < cities; j++) {
        if (isConnected[i][j] == 1 && !visited[j]) {
            visited[j] = 1;
            dfs(isConnected, visited, cities, j);
        }
    }
}

int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize) {
    int cities = isConnectedSize;
    int visited[cities];
    memset(visited, 0, sizeof(visited));
    int provinces = 0;
    for (int i = 0; i < cities; i++) {
        if (!visited[i]) {
            dfs(isConnected, visited, cities, i);
            provinces++;
        }
    }
    return provinces;
}
