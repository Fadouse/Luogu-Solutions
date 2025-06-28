#include <bits/stdc++.h>
using namespace std;

#define ll long long

// 当前构造的单位分数分母序列（候选解）
vector<int> currentSolution;
// 最优解，存储最优的单位分数分母序列
vector<int> bestSolution;

// 输入的目标分数为 originalNumerator / originalDenom
ll originalNumerator, originalDenom;

/*
  dfs 递归搜索函数

  参数说明：
    remNum      : 当前剩余分数的分子（处于约分后的状态）
    remDenom    : 当前剩余分数的分母（处于约分后的状态）
    depth       : 当前已经使用的单位分数个数（从1开始计数）
    startDenom  : 下一次选取的单位分数的分母下界（保证各项递增）
    maxDenBound : 本次搜索允许的单位分数分母上界
    maxDepth    : 本轮迭代加深的允许最大项数
*/
void dfs(ll remNum, ll remDenom, int depth, ll startDenom, int maxDenBound, int maxDepth) {
    // 若超过允许的项数，结束当前搜索
    if (depth > maxDepth) return;
    
    // 对当前分数进行约分处理
    ll d = __gcd(remNum, remDenom);
    remNum /= d;
    remDenom /= d;
    
    // 若当前剩余分母超过允许的最大分母值，剪枝退出
    if (remDenom > maxDenBound) return;
    
    /*
      判断是否剩余分数为单位分数
      当 remNum == 1 时，目标已经变成单位分数 1/remDenom；
      还需保证此分母满足递增性要求，即必须大于上一次选择的分母（即 currentSolution 的最后一个元素）。
      （注意：在初始调用时 currentSolution 不存在单位分数，但问题保证待表示分数的值大于 1/10^7，
       因此单位分数必定出现在后续递归中）
    */
    if (remNum == 1 && remDenom > currentSolution.back()) {
        currentSolution.push_back(remDenom);
        // 更新最优解：若还未找到解，或新解的长度与最优解相同且最后一项分母更小（即对应的单位分数更大）
        if (bestSolution.empty() || (currentSolution.size() == bestSolution.size() && currentSolution.back() < bestSolution.back()))
            bestSolution = currentSolution;
        currentSolution.pop_back();
        return;
    }
    
    // 下一项单位分数分母的起始值不能小于已选的最后一个分母，同时应满足分数减法的基本下界：至少大于 floor(remDenom/remNum)
    startDenom = max(startDenom, remDenom / remNum + 1);

    /*
      枚举可能选取的单位分数分母 candidateDenom 从 startDenom 开始
      同时设定一个上界，用以剪枝：
      假设还剩余 k 项可选（包括当前这一步），即 k = maxDepth - depth + 1，
      则候选分母最大值可由不等式推导： remDenom / remNum <= k / candidateDenom
      得 candidateDenom <= (k * remDenom) / remNum
    */
    int remainingCount = maxDepth - depth + 1;
    int candidateUpperBound = (int)((remainingCount * remDenom) / remNum);
    
    // 剪枝：如果从 startDenom 开始连续 remainingCount 项的倒数和都不能凑出足够和，则没有解
    double sumBound = 0.0;
    for (int j = 0; j < remainingCount; j++) {
        sumBound += 1.0 / (startDenom + j);
    }
    if (sumBound < (double)remNum / remDenom) return;
    
    // 枚举 candidateDenom，从 startDenom 开始到 candidateUpperBound 内依次尝试
    for (int candidateDenom = startDenom;; candidateDenom++) {
        // 剪枝：如果剩余所有项的理论最大和不足以表示当前剩余分数，则退出循环
        if (remDenom * (remainingCount) < remNum * candidateDenom)
            break;
        // 若 candidateDenom 超过上界，则退出循环
        if (candidateDenom > maxDenBound)
            break;
        
        // 利用全局最优解剪枝：如果当前 candidateDenom 已经不可能比已找最优解中最后一项的分母更小，则不可能改进解
        if (!bestSolution.empty() && candidateDenom >= bestSolution.back())
            break;
        
        // 选择当前 candidateDenom，加入当前方案
        currentSolution.push_back(candidateDenom);
        // 计算新的剩余分数：remNum/remDenom - 1/candidateDenom
        // 即 newRemaining = (remNum * candidateDenom - remDenom) / (remDenom * candidateDenom)
        dfs(remNum * candidateDenom - remDenom, remDenom * candidateDenom, depth + 1, candidateDenom + 1, maxDenBound, maxDepth);
        // 撤销选择，回溯
        currentSolution.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 输入原分数 originalNumerator / originalDenom
    cin >> originalNumerator >> originalDenom;
    
    // 采用迭代加深方式，限制项数 maxDepth 从 1 开始，到 10 为止（10 为经验上充分上界）
    // 同时对候选的单位分数分母上界 maxDenBound 逐级放宽：从 1000 到 1e7
    for (int maxDepth = 1; maxDepth <= 10; maxDepth++) {
        for (int maxDenBound = 1000; maxDenBound <= 1e7; maxDenBound *= 10) {
            dfs(originalNumerator, originalDenom, 1, 1, maxDenBound, maxDepth);
            if (!bestSolution.empty())
                break;
        }
        if (!bestSolution.empty())
            break;
    }
    
    // 输出最优解，单位分数分母按从小到大排列（DFS过程中保证分母是严格递增的）
    for (auto d : bestSolution)
        cout << d << " ";
    
    return 0;
}
