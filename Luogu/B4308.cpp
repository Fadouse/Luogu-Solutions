#include <bits/stdc++.h>
using namespace std;

// 注意：int8_t 类型足以存储 -1, 0, 1
using i8 = int8_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    // 线性筛到 n
    vector<char> is_comp(n + 1, 0);    // 合数标记
    vector<i8>   mu(n + 1, 0);         // 存储 μ(i)
    vector<int>  primes;               // 质数表

    mu[1] = 1;

    long long prefix_sum = 1;          // sum = pre[1]
    long long sum_m_1 = 0;             // 存 pre[m-1]
    long long sum_n   = 0;             // 存 pre[n]

    if (n == 1) {
        sum_n = 1;
    }

    for (int i = 2; i <= n; ++i) {
        if (!is_comp[i]) {
            primes.push_back(i);
            mu[i] = -1;   // i 是质数，只有一个素因子 → μ(i) = (-1)^1 = -1
        }
        for (int p : primes) {
            long long t = 1LL * i * p;
            if (t > n) break;
            is_comp[t] = 1;
            if (i % p == 0) {
                // p^2 整除 t，μ(t)=0
                mu[t] = 0;
                break;
            } else {
                // 新增一个不同素因子 → 符号取反
                mu[t] = -mu[i];
            }
        }
        // 累加前缀和
        prefix_sum += mu[i];

        if (i == m - 1) prefix_sum;  // 先累到 m-1，再记录
        if (i == m - 1) sum_m_1 = prefix_sum;
        if (i == n)     sum_n   = prefix_sum;
    }

    // 若 m==1，我们需要 pre[0]=0
    if (m == 1) sum_m_1 = 0;

    // 答案 = pre[n] - pre[m-1]
    cout << (sum_n - sum_m_1) << "\n";
    return 0;
}
