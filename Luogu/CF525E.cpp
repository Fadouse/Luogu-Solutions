#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef long long ll;

// 全局变量说明：
// n: 给定的数字个数 (n ≤ 25)
// k: 可使用的 "!" 数量，每个 "!" 可以将一个数字变成其阶乘 (每个数字最多使用一次)
// S: 目标和，需要选出若干数字（可以选择将其中部分数字变成阶乘）得到该和
int n;
int k;
ll S;
// 数组 a 存放初始序列中的数字，满足 0 ≤ a[i] ≤ 10^9
vector<ll> a;

// 使用 map 记录枚举第一部分数字的所有方案：
// key 表示枚举得到的部分数字和，value 是一个长度为 k+1 的向量，其中向量中第 i 个数表示使用 i 个 "!" 达到该和的方案数
map<ll, vector<ll>> counts1;

// 记录所有满足条件的方案总数
ll ans = 0;

// fact 数组存储 0 到 19 的阶乘值；超过范围或者不合法的值记为 -1
ll fact[20];

// 预先计算 0 到 18 的阶乘；注意 19 的阶乘直接设为 -1 防止越界
void precompute_factorials() {
    fact[0] = 1;
    fact[1] = 1;
    for (int i = 2; i <= 18; ++i) {
        // 检查是否会越界
        if (fact[i - 1] > __LONG_LONG_MAX__ / i) {
            for (int j = i; j <= 19; ++j) {
                fact[j] = -1; // 超出范围，不可用
            }
            break;
        }
        fact[i] = fact[i - 1] * i;
    }
    // 直接将 i == 19 的阶乘设为 -1
    for (int i = 19; i < 20; ++i) {
        fact[i] = -1;
    }
}

// dfs1 枚举前半部分 (前 n/2 个数字) 的所有可能选法
// 参数含义：
// index          —— 当前处理的位置（下标）
// n1             —— 前半部分数字的总个数
// current_sum    —— 当前选择的数字（或阶乘后数字）的累积和
// stickers_used  —— 当前已使用 "!" 的个数
void dfs1(int index, int n1, ll current_sum, int stickers_used) {
    // 当枚举到末尾时，将当前的累积和及使用 "!" 数量存入 counts1
    if (index == n1) {
        if (counts1.find(current_sum) == counts1.end()) {
            counts1[current_sum] = vector<ll>(k + 1, 0);
        }
        if (stickers_used <= k) {
            counts1[current_sum][stickers_used]++;
        }
        return;
    }
    
    // 方案 1：不选择当前数字
    dfs1(index + 1, n1, current_sum, stickers_used);
    
    // 方案 2：选择当前数字但不使用 "!"，直接累加 a[index]
    // 预先判断防止累加超过 S
    if (a[index] <= S - current_sum) {
        dfs1(index + 1, n1, current_sum + a[index], stickers_used);
    }
    
    // 方案 3：选择当前数字，并使用 "!" 将数字变为其阶乘
    // 条件：当前数字必须在 1 ~ 18 范围内（否则阶乘计算不适用），且总 "!" 数量未超限
    if (a[index] >= 1 && a[index] <= 18 && stickers_used < k) {
        ll val_fact = fact[a[index]];
        // 阶乘值必须合法且不使累积和超过目标 S
        if (val_fact > 0 && val_fact <= S - current_sum) {
            dfs1(index + 1, n1, current_sum + val_fact, stickers_used + 1);
        }
    }
}

// dfs2 枚举后半部分 (后 n - n/2 个数字) 的所有可能选法
// 参数含义同上，但枚举的是剩余部分
void dfs2(int index, int n_total, ll current_sum, int stickers_used) {
    // 当枚举完所有数字后，
    // 计算前半部分需要的补充和：target_sum1 = S - current_sum
    // 然后在 counts1 中寻找符合条件的方案数
    if (index == n_total) {
        ll target_sum1 = S - current_sum;
        if (target_sum1 >= 0 && counts1.count(target_sum1)) {
            const vector<ll>& ways1 = counts1.at(target_sum1);
            // 剩余可使用的 "!" 数量
            int max_k1 = k - stickers_used;
            // 累计前半部分使用 0 到 max_k1 个 "!" 的所有方案数
            for (int k1 = 0; k1 <= max_k1; ++k1) {
                ans += ways1[k1];
            }
        }
        return;
    }
    
    // 方案 1：不选当前数字
    dfs2(index + 1, n_total, current_sum, stickers_used);
    
    // 方案 2：选当前数字但不使用 "!"，直接累加 a[index]
    if (a[index] <= S - current_sum) {
        dfs2(index + 1, n_total, current_sum + a[index], stickers_used);
    }
    
    // 方案 3：选当前数字并使用 "!"（条件同前半部分）
    if (a[index] >= 1 && a[index] <= 18 && stickers_used < k) {
        ll val_fact = fact[a[index]];
        if (val_fact > 0 && val_fact <= S - current_sum) {
            dfs2(index + 1, n_total, current_sum + val_fact, stickers_used + 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 输入：第一行输入 n, k, S
    cin >> n >> k >> S;
    
    // 输入：第二行输入 n 个数字
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    // 预计算阶乘数组（仅对 1~18 的数字有效）
    precompute_factorials();
    
    // 将序列分为两部分：前半部分和后半部分
    int n1 = n / 2;
    
    // 枚举前半部分所有可能的选择情况，存入 counts1 中
    dfs1(0, n1, 0, 0);
    
    // 枚举后半部分，并结合前半部分的结果计算符合条件的方案总数
    dfs2(n1, n, 0, 0);
    
    // 输出满足条件的方案总数
    cout << ans << endl;
    
    return 0;
}
