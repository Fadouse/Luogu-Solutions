#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q, t;
    long long u, v;
    cin >> n >> m >> q >> u >> v >> t;

    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    // 预分配：最大需要 n + m 个元素
    vector<int> buf;
    buf.reserve(n + m + 1);
    // max-heap，元素类型 int
    priority_queue<int, vector<int>, less<int>> pq(less<int>(), move(buf));

    // 初始时插入 stored = a[i]
    for(int x : a){
        pq.push(x);
    }

    vector<int> first;
    first.reserve(m / t + 1);

    // 模拟每秒切割
    // stored = raw_length - time*q
    for(int i = 1; i <= m; i++){
        int s = pq.top(); pq.pop();
        // 实际长度
        int x = s + (i - 1) * q;

        if (i % t == 0) first.push_back(x);

        // 切分
        int L = int((long long)u * x / v);
        int R = x - L;

        // 插入新段，stored = raw - time*q
        pq.push(L - i * q);
        pq.push(R - i * q);
    }

    // 输出第1行
    if (!first.empty()){
        for(size_t i = 0; i < first.size(); i++){
            if (i) cout << ' ';
            cout << first[i];
        }
    }
    cout << '\n';

    // 输出第2行：取出前 n+m 个中的 t,2t,... 名
    vector<int> second;
    second.reserve((n + m) / t + 1);
    int total = n + m;
    for(int i = 1; i <= total; i++){
        int s = pq.top(); pq.pop();
        int x = s + m * q;
        if (i % t == 0) second.push_back(x);
    }
    if (!second.empty()){
        for(size_t i = 0; i < second.size(); i++){
            if (i) cout << ' ';
            cout << second[i];
        }
    }
    cout << '\n';
    return 0;
}
