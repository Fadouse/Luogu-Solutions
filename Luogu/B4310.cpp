#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll k;
    cin >> n >> k;

    vector<ll> a(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // 哈希表记录余数的第一次和最后一次出现位置
    unordered_map<ll,int> first_occ, last_occ;
    first_occ.reserve(n+1);
    last_occ.reserve(n+1);

    ll cur_mod = 0;
    first_occ[0] = 0;
    last_occ[0]  = 0;

    // 1) first/last
    for (int i = 1; i <= n; ++i) {
        cur_mod = (cur_mod + a[i]) % k;
        if (cur_mod < 0) cur_mod += k;  // 保证非负

        // 如果这是余数 cur_mod 第一次出现，就记录下标 i
        if (!first_occ.count(cur_mod)) {
            first_occ[cur_mod] = i;
        }
        // 每次都更新最后出现位置
        last_occ[cur_mod] = i;
    }

    // 2) 遍历所有出现过的余数，寻找最长区间
    int best_len   = 0;
    int best_start = -1;

    for (auto &kv : first_occ) {
        
        ll r = kv.first;
        int first_i = kv.second;
        int last_i  = last_occ[r];
        int len = last_i - first_i;  // 子数组长度

        // 更新策略：长度更大 or 长度相同但起点靠后
        int start_i = first_i + 1;
        if (len > best_len ||
           (len == best_len && start_i > best_start)) {
            best_len   = len;
            best_start = start_i;
        }
    }

    // 3) 输出结果
    if (best_len <= 0) {
        cout << -1 << endl;
    } else {
        cout << best_len << endl;
        for (int i = 0; i < best_len; ++i) {
            if (i) cout << ' ';
            cout << a[best_start + i];
        }
        cout << endl;
    }

    return 0;
}
