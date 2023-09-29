#include <iostream>
#include <vector>
using namespace std;

void backtrack(int &state, vector<int> &choices, int &res, int &n) {
    if (state == n) {
        res++;
        return ;
    }

    for (int i = 0; i < choices.size(); i++) {
        // 剪枝：
        if (state + choices[i] > n) {
            break;
        }
        // 尝试：更新状态
        state += choices[i];
        // 进行下一次选择
        backtrack(state, choices, res, n);
        // 回退：撤销当前选择
        state -= choices[i];
    }

}

int climbingStairsBacktrack(int &n){
    int state = 0;
    vector<int> choices = {1, 2};
    int res = 0;
    backtrack(state, choices, res, n);

    return res;
}

// 暴力递归, 缺点，时间复杂度程指数增长
int dfs(int i) {
    if (i == 1 || i == 2) {
        return i;
    }
    int count = dfs(i - 1) + dfs(i - 2);

    return count;
}

// 记忆化搜索：
int dfs1(int i, vector<int> &mem) {
    if (i == 1 || i == 2) {
        return i;
    }
    // 剪枝： 避免出现重复问题
    if (mem[i] != -1) {
        return mem[i];
    }
    int count = dfs1(i - 1, mem) + dfs1(i - 2, mem);

    return count;
}

/* 爬楼梯：搜索 */
int climbingStartingDFS(int n) {
    vector<int> mem(n + 1, -1);
    // return dfs(n);
    return dfs1(n, mem);
}

/* 爬楼梯：动态规划 */
int climbingStairsDP(int n) {
    if (n == 1 || n == 2) {
        return n;
    }

    // vector<int> dp(n + 1, -1);
    // dp[1] = 1;
    // dp[2] = 2;
    // for (int i = 3; i <= n; i++) {
    //     dp[i] = dp[i - 1] + dp[i - 2];
    // }

    // return dp[n];

    /* 空间优化：滚动赋值 */
    int a = 1, b = 2;
    for (int i = 3; i <= n; i++) {
        int tmp = b;
        b = a + b;
        a = tmp;
    }

    return b;
}

/* 爬楼梯最小代价：动态规划 */
int minCostClimbingStairsDP(vector<int> &cost) {
    int n = cost.size() - 1;
    if (n == 1 || n == 2) {
        return cost[n];
    }

    // vector<int> dp(n + 1, -1);
    // dp[1] = cost[1];
    // dp[2] = cost[2];
    // for (int i = 3; i <= n; i++) {
    //     dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
    // }

    // return dp[n];

    // 滚动变量优化空间复杂度
    int a = cost[1], b = cost[2];
    for (int i = 3; i <= n; i++) {
        int tmp = b;
        b = min(a, b) + cost[i];
        a = tmp;
    }

    return b;
}

/* 带约束爬楼梯：动态规划，约束条件为不可以连续跳两次一台阶 */
int climbingStairsConstraintDP(int n) {
    if (n == 1 || n == 2) {
        return 1;
    }
    vector<vector<int>> dp(n + 1, vector<int> (3, 0));
    dp[1][1] = 1;
    dp[1][2] = 0;
    dp[2][1] = 0;
    dp[2][2] = 1;
    for (int i = 3; i <= n; i++) {
        dp[i][1] = dp[i - 1][2];
        dp[i][2] = dp[i - 2][1] + dp[i - 2][2];
    }

    return dp[n][1] + dp[n][2];
}

int main()
{
    int n = 10;
    int cnt = climbingStairsBacktrack(n);
    cout << "backtrack: " << cnt << endl;

    cnt = climbingStartingDFS(n);
    cout << "DFS: " << cnt << endl;

    cnt = climbingStairsDP(n);
    cout << "DP: " << cnt << endl;

    vector<int> cost = {0, 1, 10, 2, 5, 4, 3, 9, 8, 6, 2};
    cnt = minCostClimbingStairsDP(cost);
    cout << "min Cost: " << cnt << endl;

}

