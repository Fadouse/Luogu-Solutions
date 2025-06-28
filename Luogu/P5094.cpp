#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXV = 50000; // 根据数据范围

// 树状数组模板：支持单点更新和前缀查询
struct Fenw {
    int n;
    vector<ll> tree;
    Fenw(int n): n(n), tree(n+1, 0) { }
    // 更新位置 idx（1-indexed）加上 delta
    void update(int idx, ll delta) {
        for(; idx <= n; idx += idx & -idx)
            tree[idx] += delta;
    }
    // 查询前缀和 [1, idx]
    ll query(int idx) {
        ll res = 0;
        for(; idx > 0; idx -= idx & -idx)
            res += tree[idx];
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<pair<int,int>> cows(n); // (v, x)
    for (int i = 0; i < n; i++){
        cin >> cows[i].first >> cows[i].second;
    }
    // 按 x 坐标排序
    sort(cows.begin(), cows.end(), [](auto &a, auto &b){
        return a.second < b.second;
    });
    
    // 预处理第一部分 S：累加 v_j*(j*x_j - prefix_x)
    ll S = 0;
    ll prefix_x = 0;
    for (int j = 0; j < n; j++){
        int v = cows[j].first;
        int x = cows[j].second;
        S += (ll)v * ( (ll)j * x - prefix_x );
        prefix_x += x;
    }
    
    
    // 构造四个树状数组，大小均为 MAXV
    Fenw bitCount(MAXV), bitSumV(MAXV), bitSumX(MAXV), bitSumVX(MAXV);
    
    ll T = 0;
    // 按 x 坐标从左到右扫描
    for (int j = 0; j < n; j++){
        int v = cows[j].first;
        int x = cows[j].second;
        // 查询之前奶牛中，满足 v_i > v 的，即 v_i ∈ (v, MAXV]
        // 利用 BIT 前缀查询：区间查询 [v+1, MAXV] = query(MAXV) - query(v)
        ll cnt = bitCount.query(MAXV) - bitCount.query(v);
        ll sumV = bitSumV.query(MAXV) - bitSumV.query(v);
        ll sumX = bitSumX.query(MAXV) - bitSumX.query(v);
        ll sumVX = bitSumVX.query(MAXV) - bitSumVX.query(v);
        T += (ll)x * (sumV - (ll)v * cnt) - (sumVX - (ll)v * sumX);
        bitCount.update(v, 1);
        bitSumV.update(v, v);
        bitSumX.update(v, x);
        bitSumVX.update(v, (ll)v * x);
    }
    
    cout << S + T << "\n";
    return 0;
}
