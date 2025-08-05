#include <bits/stdc++.h>

using namespace std;

int usedDy[30], usedDx[30], usedCol[15];
vector<vector<int>> mp;
int n;
int cnt;

inline int findDy(int x, int y){
    return x + y;
}

inline int findDx(int x, int y){
    return n - x + y - 1;
}

void dfs(int row){
    if(row == n){
        cnt ++ ;
        if(cnt <= 3){
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    if(mp[i][j]) cout << j+1 << ' ';
            cout << '\n';
        }
        return;
    }

    for(int col=0; col < n; col++){
        if(usedCol[col]) continue;
        int dy = findDy(row, col);
        int dx = findDx(row, col);
        if(usedDy[dy] || usedDx[dx]) continue;
        
        mp[row][col] = 1;
        usedCol[col] = 1;
        usedDx[dx] = 1;
        usedDy[dy] = 1;

        dfs(row + 1);

        mp[row][col] = 0;
        usedCol[col] = 0;
        usedDx[dx] = 0;
        usedDy[dy] = 0;
    }
    return;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    cin >> n;
    mp.assign(n, vector<int>(n,0));

    dfs(0);

    cout << cnt;

    return 0;
}