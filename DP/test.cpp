#include <iostream>
#include <vector>
using namespace std;

void DFS(vector<int> &state, int n, int r, vector<bool> &selected, vector<vector<int>> &res, int &ans) {
    if (state.size() == r) {
        res.push_back(state);
        ans++;
        return ;
    }

    for (int i = 1; i <= n; i++) {
        if (!selected[i]) {
            selected[i] = true;
            state.push_back(i);
            DFS(state, n, r, selected, res, ans);
            selected[i] = false;
            state.pop_back();
        }
    }
}

void DFS1(string &state, string &choices, int n, vector<string> &res, int left, int right) {
    if (state.size() == 2 * n) {
        res.push_back(state);
        return ;
    }
    for (int j = 0; j < 2; j++) {
        if ( ((j == 0) && (left < n)) || ( (j == 1) && (right < left) ) ){
            if (j == 0) {
                cout << "left" << endl;
                left++;
            } else if (j == 1) {
                cout << "right" << endl;
                right++;
            }
            state.push_back(choices[j]);
            DFS1(state, choices, n, res, left, right);
            if (state[state.size() - 1] == '(') {
                left--;
            } else if (state[state.size() - 1] == ')') {
                right--;
            }
            state.pop_back();
            
        }
    }

}

vector<string> generateParenthesis(int n) {
    // if (n == 1) {
    //     vector<string> res = {"()"};
    //     return res;
    // }
    string choices = {'(', ')'};
    string state;
    vector<string> res;
    DFS1(state, choices, n, res, 0, 0);

    return res;
}



int main()
{
    int n = 4, r = 3, ans = 0;
    vector<int> state;
    vector<bool> selected(r, false);
    vector<vector<int>> res;
    DFS(state, n, r, selected, res, ans);
    for (int i = 0; i < ans; i++) {
        for (int j = 0; j < r; j++) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    cout << "ans: "<< ans << endl;
    string a = {'(', ')'};
    // cout << a[a.size() - 1];

    vector<string> b = generateParenthesis(3);
    for (int i = 0; i < b.size(); i++) {
        cout << b[i] << endl;
    }

}
