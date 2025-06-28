#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

const int INF = 1e9;
int m, k;
int orig[101][101];  // 保存原始棋盘 (-1 表示无色, 0 红, 1 黄)

// best[x][y][c][s] 表示到达 (x,y) 时，继承颜色为 c，且魔法状态为 s 的最小花费
// s = 1 表示可以施展魔法，s = 0 表示刚施展过魔法，不可连续施法
int best[101][101][2][2];

// 四个方向移动
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int dfs(int x, int y, int curColor, int canMagic, int cost) {
    if (x == m - 1 && y == m - 1) return cost;
    if (cost >= best[x][y][curColor][canMagic]) return INF;
    best[x][y][curColor][canMagic] = cost;
    
    int ans = INF;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || nx >= m || ny < 0 || ny >= m) continue;
        
        // 如果目标格子原本有颜色
        if (orig[nx][ny] != -1) {
            int add = (orig[nx][ny] == curColor) ? 0 : 1;
            // 到达后更新状态：继承目标格子的颜色，且状态重置为可施法
            ans = min(ans, dfs(nx, ny, orig[nx][ny], 1, cost + add));
        } 
        // 如果目标格子无色，则只能在可施法状态下施展魔法
        else if (canMagic) {
            // 施法花费为 2，且进入后状态变为不可施法；颜色保持不变（即当前颜色传递下去）
            ans = min(ans, dfs(nx, ny, curColor, 0, cost + 2));
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> k;
    // 初始化棋盘为无色
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            orig[i][j] = -1;
        }
    }
    // 读入有颜色的格子信息
    for (int i = 0; i < k; i++){
        int x, y, c;
        cin >> x >> y >> c;
        orig[x-1][y-1] = c;
    }
    // 保证起点必定有颜色，根据题目描述起点 (1,1) 有颜色
    // 初始化 best 数组
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            for (int c = 0; c < 2; c++){
                for (int s = 0; s < 2; s++){
                    best[i][j][c][s] = INF;
                }
            }
        }
    }
    int result = dfs(0, 0, orig[0][0], 1, 0);
    cout << (result >= INF ? -1 : result) << "\n";
    return 0;
}
