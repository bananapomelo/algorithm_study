#include <iostream>
using namespace std;
// Question：输入一个整数数组，数组中不包含重复元素，返回所有可能的排列。
/* 回溯算法：全排列 I  */

void backtrack(vector<int> &state, const vector<int> &choices, vector<bool> &selected, vector<vector<int>> &res) {
    // 符合条件，存储
    if (state.size() == choices.size()) {
        res.push_back() = state;
        return ;
    }
    unordered_set<int> duplicated;
    for (int i = 0; i < choices.size(); i++) {
        int choice = choices[i];
        // 剪枝：剪掉遇到过的元素
        if (!selected[i] && duplicated.find(choice) == duplicated.end()) {
            // 尝试：更新状态
            duplicated.emplace(choice);
            selected[i] = true;
            state.push_back(choice);
            // 进行下一次选择
            backtrack(state, choices, selected, res);
            // 回退：撤销选择，恢复到之前的状态
            selected[i] = false;
            state.pop_back();
        }
    }
}










