#include <iostream>
#include <vector>
using namespace std;

/* 0-1 背包：暴力搜索 */
int knapsackDFS(vector<int> &wgt, vector<int> &val, int i, int c) {
    // 终止条件
    if (i == 0 || c == 0) {
        return 0;
    }
    // 剪枝：超过剩余容量，不存入
    if (wgt[i - 1] > c) {
        return knapsackDFS(wgt, val, i - 1, c);
    }
    // 判断存入和不存入的价值
    int no = knapsackDFS(wgt, val, i - 1, c);
    int yes = knapsackDFS(wgt, val, i - 1, c - wgt[i - 1]) + val[i - 1];

    return max(no, yes);
}

/* 0-1 背包：记忆化搜索(优化时间复杂度) */
int knapsackDFSMem(vector<vector<int>> &mem, vector<int> &wgt, vector<int> &val, int i, int c) {
    // 终止条件
    if (i == 0 || c == 0) {
        return 0;
    }
    // 若有记录直接返回
    if (mem[i][c] != -1) {
        return mem[i][c];
    }
    // 剪枝：存入容量大于剩余容量
    if (wgt[i - 1] > c) {
        return knapsackDFSMem(mem, wgt, val, i - 1, c);
    }
    int no = knapsackDFSMem(mem, wgt, val, i - 1, c);
    int yes = knapsackDFSMem(mem, wgt, val, i - 1, c - wgt[i - 1]) + val[i - 1];
    mem[i][c] = max(no, yes);

    return mem[i][c];
}

/* 0-1 背包：动态规划 */
int knapsackDP(vector<int> &wgt, vector<int> &val, int cap) {
    int n = wgt.size();
    // 创建dp表
    vector<vector<int>> dp(n + 1, vector<int> (cap + 1, 0));
    // 状态转移
    for (int i = 1; i <= n; i++) {
        for (int c = 1; c <= cap; c++) {
            if (wgt[i - 1] > c) {
                dp[i][c] = dp[i - 1][c];
            } else {
                dp[i][c] = max(dp[i - 1][c], dp[i - 1][c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[n][cap];
}

/* 0-1 背包：动态规划(优化空间) */
int knapsackDPComp(vector<int> &wgt, vector<int> &val, int cap) {
    int n = wgt.size();
    // 初始化dp表
    vector<int> dp(cap + 1, 0);
    // 状态转移
    for (int i = 0; i <= n; i++) {
        // 倒序遍历
        for (int c = cap; c >= 1; c--) {
            if (wgt[i - 1] <= c) {
                dp[c] = max(dp[c], dp[c - wgt[i - 1]] + val[i - 1]);
            }
        } 
    }

    return dp[cap];
}

/* 完全背包：动态规划 */
int unboundedKnapsackDP(vector<int> &wgt, vector<int> &val, int cap) {
    int n = wgt.size();
    vector<vector<int>> dp(n + 1, vector<int> (cap + 1, 0));
    // 状态转移方程：dp[i][c] = max(dp[i - 1][c], dp[i][c - wgt[i - 1]] + val[i - 1]);
    for (int i = 1; i <= n; i++) {
        for (int c = 1; c <= cap; c++) {
            if (wgt[i - 1] > c) {
                dp[i][c] = dp[i - 1][c];
            } else {
                dp[i][c] = max(dp[i - 1][c], dp[i][c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }

    return dp[n][cap];
}

/* 完全背包：动态规划(空间优化) */
int unboundedKnapsackDPComp(vector<int> &wgt, vector<int> &val, int cap) {
    int n = wgt.size();
    vector<int> dp(cap + 1, 0);
    // 状态转移
    for (int i = 1; i <= n; i++) {
        for (int c = 1; c <= cap; c++) {
            if (wgt[i - 1] > c) {
                dp[c] = dp[c];
            } else {
                dp[c] = max(dp[c], dp[c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }

    return dp[cap];
}

/* 零钱兑换：动态规划 */
int coinChangeDP(vector<int> &coin, int amt) {
    int n = coin.size();
    int MAX = amt + 1;
    vector<vector<int>> dp(n + 1, vector<int> (amt + 1, 0));
    // 设定无效值
    for (int i = 0; i <= amt; i++) {
        dp[0][i] = MAX;
    }
    // 状态转移
    for (int i = 1; i <= n; i++) {
        for (int c = 1; c <= amt; c++) {
            if (coin[i - 1] > c) {
                // 不选该硬币，继承上一个子问题的解
                dp[i][c] = dp[i - 1][c];
            } else {
                dp[i][c] = min(dp[i - 1][c], dp[i][c - coin[i - 1]] + 1);
            }
        }
    }

    return dp[n][amt] != MAX ? dp[n][amt] : MAX;
}

/* 零钱兑换：动态规划(空间优化) */
int coinChangeDPComp(vector<int> &coins, int amt) {
    int n = coins.size();
    // 状态转移方程 dp[i]= min(dp[a], dp[a - coins[i - 1] + 1])
    int MAX = amt + 1;
    vector<int> dp(amt + 1, MAX);
    dp[0] = 0;
    // 状态转移
    for (int i = 1; i <= n; i++) {
        for (int a = 1; a <= amt; a++) {
            if (coins[i - 1] > a) {
                dp[a] = dp[a];
            } else {
                dp[a] = min(dp[a], dp[a - coins[i - 1]] + 1);
            }
        }
    }

    return dp[amt] != MAX ? dp[amt] : -1;
}

/* 零钱兑换 II：动态规划 */
int coinChangeIIDP(vector<int> &coins, int amt) {
    /*  子问题：前i种硬币组合成金额a的组合数量
        dp表： 一个 (n + 1) * (amt + 1)的矩阵
        状态转移方程：dp[i][a] = dp[i - 1][a] + dp[i][a - coin[i - 1]];
        剪枝: 当硬币金额大于剩余金额, dp[i][a] = dp[i - 1][a]
        边界值：当目标金额为0时，dp[i][0] = 1;
                当无硬币时,dp[0][a] = 0
     */
    int n = coins.size();
    // 建立dp表
    vector<vector<int>> dp(n + 1, vector<int> (amt + 1, 0));
    // 确定边界值
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 1;
    }
    // 状态转移
    for (int i = 1; i <= n; i++) {
        for (int a = 1; a <= amt; a++) {
            if (coins[i - 1] > a) {
                dp[i][a] = dp[i - 1][a];
            } else {
                dp[i][a] = dp[i - 1][a] + dp[i][a - coins[i - 1]];
            }
        }
    }

    return dp[n][amt];
}

/* 零钱兑换 II: 动态规划（空间优化） */
int coinChangeIIDPComp(vector<int> &coins, int amt) {
    /* 
        子问题: 前i种硬币组合成金额a的组合数量
        dp表: 一个(amt + 1)的一维矩阵
        状态转移方程: dp[a] = dp[a] + dp[a - coins[i - 1]]
        剪枝: 当硬币金额大于剩余金额, dp[i][a] = dp[i - 1][a]
        边界值: 初始化后赋值0, 每次轮换数组时dp[0] = 1;
     */
    int n = coins.size();
    // 初始化dp表
    vector<int> dp(amt + 1, 0);
    // 状态转移
    for (int i = 1; i <= n; i++) {
        dp[0] = 1;
        for (int a = 1; a <= amt; a++) {
            if (coins[i - 1] > a) {
                dp[a] = dp[a];
            } else {
                dp[a] = dp[a] + dp[a - coins[i - 1]];
            }
        }
    }

    return dp[amt];
}

/* 编辑距离问题：动态规划 */
int editDistanceDP(string s, string t) {
    /* 
        思考每轮的决策,定义状态,从而得到dp表:
            每轮判断s[i]和t[j]是否相同, 不相同有三种选择(插入/删除/替换)
            子问题: s的前i个字符和t的前j个字符是否相同
            dp表: (i + 1) * (j + 1)的二维矩阵
        找出最优子结构,进而推到出状态转移方程:
            操作后的子问题:
                添加: dp[i][j - 1]
                删除: dp[i - 1][j]
                替换: dp[i - 1][j - 1]
            最优子结构: dp[i][j]的最优子结构应为dp[i][j]的操作加上s前i个字符和t前j个字符的最小操作数
            状态转移方程: dp[i][j] = min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1])
        确定边界条件和状态转移顺序:
            都为空, 操作数为0
            当s为空时, 操作数量为j, 当j为空时, 操作数量为i
            依赖于左,上,左上,所以双层正向循环遍历
     */
    int lenS = s.length(), lenT = t.length();
    // 初始化dp表
    vector<vector<int>> dp(lenS + 1, vector<int> (lenT + 1, 0));
    for (int i = 1; i <= lenS; i++) {
        dp[i][0] = i;
    }
    for (int i = 1; i <= lenT; i++) {
        dp[0][i] = i;
    }
    // 状态转移
    for (int i = 1; i <= lenS; i++) {
        for (int j = 1; j <= lenT; j++) {
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
            }
        }
    }

    return dp[lenS][lenT];
}

/* 编辑距离：动态规划（空间优化） */
int editDistanceDPComp(string s, string t) {
    /* 
        思考每轮决策, 定义状态, 定义dp表:
            每轮判断s[i], t[j]是否相同, 不相同做出操作(添加/删除/替换)
            状态为[i][j]: 将s的前i个字符更改为t的j个字符的最少编辑次数
            dp表: (i + 1) * (j + 1)的二维矩阵
        寻找最优子结构, 得出状态转移方程:
            操作选择:
                添加: dp[i][j - 1]
                删除: dp[i - 1][j]
                替换: dp[i - 1][j - 1]
            最优子结构: 本次的操作数加上之前的操作次数
            状态转移方程: dp[i][j] = min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]) + 1
        确定边界条件和状态转移顺序:
            当s和t长度都为0时,为0
            当s为0,t不为0,操作数为t.length()
            当s不为0,t为0,操作数为s.length()
        空间优化:
            由于需要左上角元素, 且是一维, 会覆盖掉正确的dp[i - 1][j - 1]
     */
    int lenS = s.length(), lenT = t.length();
    // 定义dp表并初始化
    vector<int> dp(lenT + 1, 0);
    for (int i = 0; i <= lenT; i++) {
        dp[i] = i;
    }
    // 状态转移
    for (int i = 1; i <= lenS; i++) {
        int leftUp = dp[0];
        dp[0] = i;
        for (int j = 1; j <= lenT; j++) {
            int tmp = dp[j];
            if (s[i - 1] == t[j - 1]) {
                dp[j] = leftUp;
            } else {
                dp[j] = min(min(dp[j - 1], dp[j]), leftUp) + 1;
            }
            leftUp = tmp;
        }
    }

    return dp[lenT];
}


int main()
{
    vector<int> wgt = {10, 20, 30, 40, 50};
    vector<int> val = {50, 120, 150, 210, 240};
    vector<vector<int>> mem(wgt.size() + 1, vector<int> (51, -1));

    int maxValue = knapsackDFS(wgt, val, 5, 50);
    cout << "背包:暴力搜索 " << maxValue << endl;

    maxValue = knapsackDFSMem(mem, wgt, val, 5, 50);
    cout << "背包: 记忆化搜索 " << maxValue << endl;

    maxValue = knapsackDP(wgt, val, 50);
    cout << "背包: 动态规划 " << maxValue << endl;

    maxValue = knapsackDPComp(wgt, val, 50);
    cout << "背包: 动态规划(空间优化) " << maxValue << endl;

    maxValue = unboundedKnapsackDP(wgt, val, 50);
    cout << "完全背包: 动态规划 " << maxValue << endl;

    maxValue = unboundedKnapsackDPComp(wgt, val, 50);
    cout << "完全背包: 动态规划(优化空间) " << maxValue << endl;

    vector<int> coin = {1, 2, 5};
    int minValue;
    minValue = coinChangeDP(coin, 11);
    cout << "零钱兑换: 动态规划 " << minValue << endl;

    minValue = coinChangeDPComp(coin, 11);
    cout << "零钱兑换: 动态规划(空间优化) " << minValue << endl;

    minValue = coinChangeIIDP(coin, 5);
    cout << "零钱兑换 II: 动态规划 " << minValue << endl;

    minValue = coinChangeIIDPComp(coin, 5);
    cout << "零钱兑换 II: 动态规划(空间优化) " << minValue << endl;

    // string s = "kitten", t = "sitting";
    string s = "hello", t = "algo";
    minValue = editDistanceDP(s, t);
    cout << "编辑距离: 动态规划 " << minValue << endl;

    minValue = editDistanceDPComp(s, t);
    cout << "编辑距离: 动态规划(空间优化) " << minValue << endl;

    return 0;
}

