#include <bits/stdc++.h>

using namespace std;

//分治法求解, 递归，1-based index
void solve(int x, int y, int a, int b, int length){
    if(length == 1){
        return;
    }
    int half = length / 2;
    if(x - a <= half - 1 && y - b <= half - 1){
        cout << a + half << " " << b + half << " " << 1 << endl;
        solve(x, y, a, b, half);
        solve(a + half - 1, b + half, a, b + half, half);
        solve(a + half, b + half - 1, a + half, b, half);
        solve(a + half, b + half, a + half, b + half, half);
    } else if(x - a <= half - 1 && y - b > half - 1){
        cout << a + half << " " << b + half - 1 << " " << 2 << endl;
        solve(a + half - 1, b + half - 1, a, b, half);
        solve(x, y, a, b + half, half);
        solve(a + half, b + half - 1, a + half, b, half);
        solve(a + half, b + half, a + half, b + half, half);
    } else if(x - a > half - 1 && y - b <= half - 1){
        cout << a + half - 1 << " " << b + half << " " << 3 << endl;
        solve(a + half - 1, b + half - 1, a, b, half);
        solve(a + half - 1, b + half, a, b + half, half);
        solve(x, y, a + half, b, half);
        solve(a + half, b + half, a + half, b + half, half);
    } else{
        cout << a + half - 1 << " " << b + half - 1 << " " << 4 << endl;
        solve(a + half - 1, b + half - 1, a, b, half);
        solve(a + half - 1, b + half, a, b + half, half);
        solve(a + half, b + half - 1, a + half, b, half);
        solve(x, y, a + half, b + half, half);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    //输入矩阵大小 为 2^p * 2^p, 则分治为 4 个 2^(p-1) * 2^(p-1) 的矩阵
    int p;
    cin >> p;
    int n = pow(2, p);
    vector<vector<int>> matrix(n, vector<int>(n));

    //输入公主位置
    int x, y;
    cin >> x >> y;

    //求解
    solve(x, y, 1, 1, n);
    
    return 0;
}