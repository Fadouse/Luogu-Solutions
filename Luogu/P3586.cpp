#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Fenwick Tree for counts (int) and sums (ll)
struct Fenwick {
    int n;
    vector<ll> f;
    Fenwick(int _n): n(_n), f(n+1, 0) {}
    // add v at position i (0-based)
    void add(int i, ll v) {
        for (int x = i+1; x <= n; x += x & -x)
            f[x] += v;
    }
    // query sum[0..i] (0-based). if i<0 returns 0.
    ll sum(int i) const {
        if (i < 0) return 0;
        if (i >= n) i = n-1;
        ll s = 0;
        for (int x = i+1; x > 0; x -= x & -x)
            s += f[x];
        return s;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // 读入所有操作，顺便收集所有更新值 a 和查询阈值 s 以备离散化
    vector<char>   typ(m);
    vector<int>    x1(m);
    vector<ll>     x2(m);
    vector<ll>     comp;
    comp.reserve(2*m + 1);
    comp.push_back(0);  // 初始值 0 也要离散化

    for (int i = 0; i < m; i++) {
        cin >> typ[i] >> x1[i] >> x2[i];
        comp.push_back(x2[i]);
    }
    // 去重并排序
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    int C = comp.size();

    // 两棵 Fenwick：一棵记录频次，一棵记录元素和
    Fenwick bitCnt(C);
    Fenwick bitSum(C);
    // 初始序列全为 0
    int idx0 = lower_bound(comp.begin(), comp.end(), 0) - comp.begin();
    bitCnt.add(idx0, n);
    // Aidx 保存每个位置当前值的离散化下标
    vector<int> Aidx(n+1, idx0);
    ll totalSum = 0;

    string output;
    output.reserve(m * 4);

    for (int i = 0; i < m; i++) {
        if (typ[i] == 'U') {
            int pos = x1[i];
            ll   val = x2[i];
            int newIdx = lower_bound(comp.begin(), comp.end(), val) - comp.begin();
            int oldIdx = Aidx[pos];
            ll  oldVal = comp[oldIdx];
            // 从 Fenwick 中删除旧值，加入新值
            bitCnt.add(oldIdx, -1);
            bitSum.add(oldIdx, -oldVal);
            bitCnt.add(newIdx, +1);
            bitSum.add(newIdx, +val);
            totalSum += val - oldVal;
            Aidx[pos] = newIdx;
        }
        else { // 'Z' 查询
            ll c = x1[i], s = x2[i];
            // 找到 comp 中最后一个 <= s 的下标
            int idxS = int(upper_bound(comp.begin(), comp.end(), s) - comp.begin()) - 1;
            ll cntLE = bitCnt.sum(idxS);
            ll sumLE = bitSum.sum(idxS);
            ll cntGT = ll(n) - cntLE;
            
            // sum_{i} min(A_i, s)
            ll sumMin = sumLE + cntGT * s;
            // 判断能否进行 s 次“每次选 c 个正数减 1”
            if (sumMin >= c * s) output += "TAK\n";
            else               output += "NIE\n";
        }
    }

    // 一次性输出
    cout << output;
    return 0;
}
