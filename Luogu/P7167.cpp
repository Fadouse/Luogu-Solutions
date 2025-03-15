#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    vector<long long> D(n+1), C(n+1);
    for (int i = 1; i <= n; i++){
        cin >> D[i] >> C[i];
    }

    vector<int> nxt(n+1, 0);
    stack<int> st;
    for (int i = n; i >= 1; i--){
        while (!st.empty() && D[st.top()] <= D[i])
            st.pop();
        nxt[i] = st.empty() ? 0 : st.top();
        st.push(i);
    }
    

    int maxP = 0;
    while ((1 << maxP) <= n) maxP++;
    vector<vector<int>> up(n+1, vector<int>(maxP, 0));
    vector<vector<long long>> sum(n+1, vector<long long>(maxP, 0));
    
    // Base layer (j=0)
    for (int i = 1; i <= n; i++){
        up[i][0] = nxt[i];
        if (nxt[i])
            sum[i][0] = C[nxt[i]];
        else 
            sum[i][0] = 0;
    }
    
    for (int j = 1; j < maxP; j++){
        for (int i = 1; i <= n; i++){
            int mid = up[i][j-1];
            if (mid){
                up[i][j] = up[mid][j-1];
                sum[i][j] = sum[i][j-1] + sum[mid][j-1];
            } else {
                up[i][j] = 0;
                sum[i][j] = sum[i][j-1];
            }
        }
    }
    
    for (int i = 0; i < q; i++){
        int r;
        long long v;
        cin >> r >> v;
        if (v <= C[r]){
            cout << r << "\n";
            continue;
        }
        long long rem = v - C[r];
        int cur = r;
        for (int j = maxP - 1; j >= 0; j--){
            if (up[cur][j] != 0 && sum[cur][j] < rem){
                rem -= sum[cur][j];
                cur = up[cur][j];
            }
        }
        int nxtDisk = up[cur][0];
        cout << (nxtDisk ? nxtDisk : 0) << "\n";
    }
    
    return 0;
}
