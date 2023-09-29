#include <iostream>
using namespace std;

void backtrack(vector<int> &state, int target, int total, vector<int> choices, vector<vector<int>> &res) {
    // 子集和等于target时， 记录解
    if (total == target) {
        res.push_back(state);
        return ;
    }
    // 遍历所有选择
    for (size_t i = 0; i < choices.size(); i++) {
        // 剪枝：若子集和超过target，则跳过该选择
        if (total + choices[i] > target) {
            continue;
        }
        // 尝试：做出选择；更新元素和total
        state.push_back(choices[i]);
        // 进行下一轮选择
        backtrack(state, target, total + choices[i], choices, res);
        // 回退：撤销选择，恢复到之前的状态
        state.pop_back();
    }
}

vector<vector<int>> subsetSumINavie(vector<int> &nums, int target) {
    vector<int> state; // 状态(子集)
    int total = 0; // 子集和
    vector<vector<int>> res; // 结果列表(子集列表)
    backtrack(state, target, total, nums, res);

    return res;
}

/* 回溯算法：子集和I 剪枝重复子集，Eg：（4,3）和（3,4）为重复子集 */
void backtrack(vector<int> &state, int target, vector<int> &choices, int start, vector<vector<int>> &res) {
    // 子集和等于target时，记录解
    if (target == 0) {
        res.push_back(state);
        return ;
    }
    // 遍历所有选择
    // 剪枝二：从start开始遍历，避免生成重复子集
    for (int i = start; i < choices.size(); i++) {
        // 剪枝一：若子集和超过target，则直接结束循环
        // 这是因为数组已排序，后边元素更大，子集和一定超过target
        if (target - choices[i] < 0) {
            break;
        }
        // 尝试：做出选择，更新target，start
        state.push_back(choices[i]);
        // 进行下一轮选择
        backtrack(state, target - choices[i], chioces, i, res);
        // 回退：撤销选择，恢复到之前的状态
        state.pop_back();
    }

}

vector<vector<int>> subsetSumI(vector<int> &nums, int target) {
    vector<int> state;
    sort(nums.begin(), nums.end());
    int start = 0;
    vector<vector<int>> res;
    backtrack1(state, target, nums, start, res);

    return res;
}

void backtrack(vector<int> &state, int target, vector<int> &choices, int start, vector<vector<int>> &res) {
    // 子集和等于target时，记录解
    if (target == 0) {
        res.push_back(state);
        return ;
    }
    // 遍历所有选择
    // 剪枝二：从start开始遍历，避免生成重复子集
    // 剪枝三：从start开始遍历，避免重复选择同一元素
    for (int i = start; i < choices.size(); i++) {
        // 剪枝一：若子集和超过target，则直接结束循环
        // 这是因为数组已排序，后边元素更大，子集和一定超过target
        if (target - choices[i] < 0) {
            break;
        }
        // 剪枝四：如果该元素与左边元素相等，说明该搜索分支重复，直接跳过
        if (i > start && choices[i] == choices[i - 1]) {
            continue;
        }
        // 尝试：做出选择，更新target，start
        state.push_back(choices[i]);
        // 进行下一轮选择
        backtrack(state, target - choices[i], choices, i + 1, res);
        // 回退：撤销选择，恢复到之前的状态
        state.pop_back();
    }
}

