#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static const int N = 9;
int a[N][N];
// 靶形权值
int W[N][N] = {
    {6,6,6,6,6,6,6,6,6},
    {6,7,7,7,7,7,7,7,6},
    {6,7,8,8,8,8,8,7,6},
    {6,7,8,9,9,9,8,7,6},
    {6,7,8,9,10,9,8,7,6},
    {6,7,8,9,9,9,8,7,6},
    {6,7,8,8,8,8,8,7,6},
    {6,7,7,7,7,7,7,7,6},
    {6,6,6,6,6,6,6,6,6}
};

// 预先收集所有空格 (x,y)
vector<pair<int,int>> empties;
int M; // 空格总数

// 行/列/宫 已用掩码
int rowMask[N], colMask[N], blkMask[N];

// 全局最优
ll best = -1;

// 计算 (x,y) 属于哪个 3x3 宫
inline int toBlock(int x, int y) {
    return (x/3)*3 + (y/3);
}

// 递归 DFS
// 参数：已用格子数 usedCnt，当前得分 curG，剩余最大估算分 remH
void dfs(int usedCnt, ll curG, ll remH) {
    // 剪枝：即便后面全部 9 分也追不上 best
    if (curG + remH <= best) return;
    if (usedCnt == M) {
        best = max(best, curG);
        return;
    }

    // MRV：选未填且候选数最少的格子
    int pick = -1, minCnt = 10;
    int pickMask = 0;
    for (int i = 0; i < M; i++) {
        auto [x,y] = empties[i];
        // 用一个标志数组检测已填，改用 a[x][y] != 0
        if (a[x][y] != 0) continue;
        int m = rowMask[x] | colMask[y] | blkMask[toBlock(x,y)];
        int cMask = (~m) & 0x1FF;          // 9 位有效
        int cnt = __builtin_popcount(cMask);
        if (cnt == 0) return;            // 无可选，直接剪枝
        if (cnt < minCnt) {
            minCnt = cnt;
            pick = i;
            pickMask = cMask;
            if (cnt == 1) break;         // 最优早停
        }
    }

    // 将 pick 对应格子填上
    int x = empties[pick].first, y = empties[pick].second, b = toBlock(x,y);
    int w = W[x][y];
    // 新的 remH：本格从“9 分估算”中扣除 w*9
    ll nextRemH = remH - ll(w) * 9;

    // 枚举所有可选 d
    while (pickMask) {
        int lowbit = pickMask & -pickMask;

        pickMask ^= lowbit;
        int d = __builtin_ctz(lowbit) + 1;  // 从 1..9

        // 设定
        a[x][y] = d;
        rowMask[x] |= lowbit;
        colMask[y] |= lowbit;
        blkMask[b]   |= lowbit;

        dfs(usedCnt + 1,
            curG + ll(w) * d,
            nextRemH);

        // 恢复
        a[x][y] = 0;
        rowMask[x] ^= lowbit;
        colMask[y] ^= lowbit;
        blkMask[b]   ^= lowbit;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++){
            cin >> a[i][j];
            if(a[i][j]==0)
                empties.emplace_back(i,j);
        }
    M = empties.size();

    // 初始化掩码 & 初始得分 & remH
    ll remH = 0, initG = 0;
    for(int i=0;i<N;i++){
        rowMask[i] = colMask[i] = blkMask[i] = 0;
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(a[i][j]){
                int d = a[i][j], b = toBlock(i,j);
                int bit = 1<<(d-1);
                rowMask[i] |= bit;
                colMask[j] |= bit;
                blkMask[b]   |= bit;
                initG += ll(W[i][j]) * d;
            }
        }
    }
    // 计算剩余所有空格的“9 分估算”总和
    for(auto &p : empties){
        remH += ll(W[p.first][p.second]) * 9;
    }

    // 启动 DFS
    dfs(0, initG, remH);

    // 输出结果
    if(best < 0) cout << -1 << "\n";
    else         cout << best << "\n";
    return 0;
}
