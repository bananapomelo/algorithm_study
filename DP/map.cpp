#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    // 创建一个unordered_map，将姓名映射到年龄
    unordered_map<string, int> ageMap;

    // 插入键值对
    ageMap["Alice"] = 30;
    ageMap["Bob"] = 25;
    ageMap["Charlie"] = 35;

    // 查找年龄
    string name = "Bob";
    if (ageMap.find(name) != ageMap.end()) {
        cout << name << "的年龄是 " << ageMap[name] << " 岁。\n";
    } else {
        cout << name << " 不在年龄映射中。\n";
    }

    // 遍历unordered_map
    for (const auto& pair : ageMap) {
        cout << pair.first << ": " << pair.second << " 岁\n";
    }

    return 0;
}
