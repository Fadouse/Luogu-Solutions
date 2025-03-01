#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 100005;
constexpr int logN = 17;
int f[MAXN][logN + 1], Logn[MAXN + 1];

void pre() {  // 准备工作，初始化
  Logn[1] = 0;
  Logn[2] = 1;
  for (int i = 3; i < MAXN; i++) {
    Logn[i] = Logn[i / 2] + 1;
  }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    pre();
    int n, m;
    cin >> n >> m;

    for(int i=1; i<=n ; i++){
        cin >> f[i][0];
    }
    for(int j=1; j<=logN; j++){
        for(int i=1; i+(1<<j)-1<=n; i++){
            f[i][j] = min(f[i][j-1], f[i+(1<<(j-1))][j-1]);
        }
    }
    for(int i=1; i<=m; i++){
        int x, y;
        cin >> x >> y;
        int s = Logn[y-x+1];
        cout << min(f[x][s], f[y-(1<<s)+1][s]) << ' ';
    }


    return 0;
}