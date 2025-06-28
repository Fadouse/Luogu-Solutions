#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// DFS生成所有可能的组合sum
void dfs(vector<ll>& prices, int start, int end, ll current_sum, ll budget, vector<ll>& result) {
    if (start == end) {
        // 到达边界，将当前sum加入结果
        if (current_sum <= budget) {
            result.push_back(current_sum);
        }
        return;
    }
    
    // 不选当前比赛
    dfs(prices, start + 1, end, current_sum, budget, result);
    
    // 选当前比赛（如果不超预算）
    if (current_sum + prices[start] <= budget) {
        dfs(prices, start + 1, end, current_sum + prices[start], budget, result);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    ll m;
    cin >> n >> m;
    
    vector<ll> prices(n);
    for (int i = 0; i < n; i++) {
        cin >> prices[i];
    }
    int mid = n / 2;
    
    vector<ll> first_half;
    dfs(prices, 0, mid, 0, m, first_half);
    
    vector<ll> second_half;
    dfs(prices, mid, n, 0, m, second_half);
    
    sort(second_half.begin(), second_half.end());
    
    ll answer = 0;
    for (ll sum : first_half) {
        ll remaining = m - sum;
        answer += upper_bound(second_half.begin(), second_half.end(), remaining) - second_half.begin();
    }
    
    cout << answer << endl;
    return 0;
}