#include <iostream>
#include <vector>
using namespace std;
#define INT_MAX 65536


/* 最小路径和：暴力搜索 */
int minPathSumDFS( vector<vector<int>> &grid, int i, int j) {
    if (i == 0 && j == 0) {
        return grid[0][0];
    }
    vector<vector<int>>dp;
    //dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j]
    if (i < 0 || j < 0) {
        return INT_MAX;
    }

    int left = minPathSumDFS(grid, i - 1, j);
    int right = minPathSumDFS(grid, i, j - 1);
    return min(left, right) != INT_MAX ? min(left, right) + grid[i][j]: INT_MAX;


}

/* 最小路径和：记忆化搜索 */
int minPathSumDFSMem(vector<vector<int>> &grid, vector<vector<int>> &mem, int i, int j) {
    if (i == 0 && j == 0) {
        return grid[0][0];
    }
    if (i < 0 || j < 0) {
        return INT_MAX;
    }
    if (mem[i][j] != -1) {
        return mem[i][j];
    }
    
    int left = minPathSumDFSMem(grid, mem, i - 1, j);
    int right = minPathSumDFSMem(grid, mem, i, j - 1);
    mem[i][j] = (min(left, right) != INT_MAX ? min(left, right) : INT_MAX) + grid[i][j];

    return mem[i][j];
}

/* 最小路径和：动画规划 */
int minPathSumDP(vector<vector<int>> &grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dp(n, vector<int> (m));
    dp[0][0] = grid[0][0];
    for (int i = 1; i < m; i++) {
        dp[0][i] = dp[0][i - 1] + grid[0][i];
    }
    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }
    
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        }
    }

    return dp[n - 1][m - 1];
}

/* 最小路径和：动态规划（优化空间） */
int minPathSumDPComp(vector<vector<int>> &grid) {
    int n = grid.size(), m = grid[0].size();
    vector<int> bp(m);
    bp[0] = grid[0][0];
    // 初始化首行状态
    for (int i = 1; i < m; i++) {
        bp[i] = bp[i - 1] + grid[0][i];
    }

    for (int i = 1; i < n; i++) {
        bp[0] = bp[0] + grid[i][0];
        for (int j = 1; j < m; j++) {
            bp[j] = min(bp[j - 1], bp[j]) + grid[i][j];
        }
    }

    return bp[m - 1];
}

int main()
{
    vector<vector<int>> grid = {{1, 3, 1, 5}, {2, 2, 4, 2}, {5, 3, 2, 1}, {4, 3, 5, 2}};
    int slowPath = minPathSumDFS(grid, 3, 3);
    cout << "暴力搜索: " << slowPath << endl;

    vector<vector<int>> mem(4, vector<int> (4, -1));
    slowPath = minPathSumDFSMem(grid, mem, 3, 3);
    cout << "记忆化搜索: " << slowPath << endl;

    slowPath = minPathSumDP(grid);
    cout << "动态规划: " << slowPath << endl;

    slowPath = minPathSumDPComp(grid);
    cout << "动态规划(优化空间): " << slowPath << endl;

}
