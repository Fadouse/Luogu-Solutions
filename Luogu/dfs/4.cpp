#include <bits/stdc++.h>

using namespace std;

int mp[4][4];
unordered_set<int> usedRow[4], usedCol[4], usedBox[4];

inline int boxId(int x, int y) {          
    return (x / 2) * 2 + (y / 2);
}

bool dfs(int pos) {   
    if (pos == 16) return true;     
    int x = pos / 4, y = pos % 4;
    if (mp[x][y]) return dfs(pos + 1);    

    for (int v = 1; v <= 4; ++v) {
        if (usedRow[x].count(v) ||
            usedCol[y].count(v) ||
            usedBox[boxId(x, y)].count(v)) continue;

        // 放置 v
        mp[x][y] = v;
        usedRow[x].insert(v);
        usedCol[y].insert(v);
        usedBox[boxId(x, y)].insert(v);

        if (dfs(pos + 1)) return true;   

        // 回溯
        mp[x][y] = 0;
        usedRow[x].erase(v);
        usedCol[y].erase(v);
        usedBox[boxId(x, y)].erase(v);
    }
    return false;                       
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    dfs(0);
    
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cout << mp[i][j] <<' ';
        }
        cout << endl;
    }
    return 0;
}