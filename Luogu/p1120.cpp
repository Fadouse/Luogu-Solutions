#include <bits/stdc++.h>

using namespace std;

int vis[66]; // 记录小木棍的使用情况
int n;
int len;
int nums[66], sum = 0;

bool dfs(int cnt, int start, int curr_sum) {
    if (cnt * len == sum) return true; // 所有木棍都已使用完
    if (curr_sum == len) return dfs(cnt+1, 0, 0); // 完成一根边，开始下一根
    
    for (int i = start; i < n; i++) {
        if (vis[i]) continue; // 已使用的木棍跳过
        if (curr_sum + nums[i] > len) continue; // 超长跳过
        
        // 剪枝：相同长度的木棍，选择第一个尝试即可
        if (i > 0 && nums[i] == nums[i-1] && !vis[i-1]) continue;
        
        vis[i] = 1; // 标记为已使用
        if (dfs(cnt, i+1, curr_sum + nums[i])) return true; // 正确传递i+1作为下一个起点
        vis[i] = 0; // 回溯
        
        // 剪枝：如果是当前边的第一个木棍失败，或者拼接后刚好等于len失败，则直接返回
        if (curr_sum == 0 || curr_sum + nums[i] == len) return false;
        
        // 跳过相同长度的木棍
        while (i+1 < n && nums[i+1] == nums[i]) i++;
    }
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        sum += nums[i];
    }
    
    // 按降序排序，优化搜索效率
    sort(nums, nums+n, greater<int>());
    
    // 从大到小尝试可能的边长
    for (int i = sum; i > 0; i--) {
        if (sum % i != 0) continue; // 不能整除，跳过
        len = sum / i;
        
        // 剪枝：如果最长的木棍比边长还长，无解
        if (nums[0] > len) continue;
        
        memset(vis, 0, sizeof(vis)); // 重置访问数组
        if (dfs(0, 0, 0)) {
            cout << len << endl;
            return 0;
        }
    }

    return 0;
}