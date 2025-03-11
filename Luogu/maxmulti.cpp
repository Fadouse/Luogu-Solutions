#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

typedef long long ll;

ll maxProduct = 0;

// 递归函数：pos 保存当前选中的插入位置（范围 1 到 n-1）
// start 为下一个可选位置的起始值，m 为需要插入的乘号个数，s 为原字符串
void dfs(const string &s, int m, int start, vector<int>& pos) {
    if (pos.size() == m) {
        ll prod = 1;
        int prev = 0;
        // 根据选中位置进行分割，依次计算各段数值的乘积
        for (int p : pos) {
            string segment = s.substr(prev, p - prev);
            prod *= stoll(segment);
            prev = p;
        }
        // 计算最后一段
        prod *= stoll(s.substr(prev));
        maxProduct = max(maxProduct, prod);
        return;
    }
    
    int n = s.size();
    // 枚举后续可能的插入位置
    for (int i = start; i < n; i++) {
        // 保证至少有足够的剩余字符划分出所需段数
        if (n - i < m - pos.size()) break;
        pos.push_back(i);
        dfs(s, m, i + 1, pos);
        pos.pop_back();
    }
}

int main(){
    int m;
    string s;
    cin >> m >> s;
    
    vector<int> pos;
    dfs(s, m, 1, pos);
    
    cout << maxProduct << endl;
    return 0;
}
