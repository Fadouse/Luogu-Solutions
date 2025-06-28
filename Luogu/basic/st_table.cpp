#include <bits/stdc++.h>

using namespace std;

class SparseTable {
private:
    vector<vector<int>> st;
    vector<int> lg;
    int n;
    
public:
    SparseTable(vector<int>& arr) {
        n = arr.size();
        int k = log2(n) + 1;
        st.assign(n, vector<int>(k));
        lg.assign(n + 1, 0);
        
        // Precompute logarithms
        for (int i = 2; i <= n; i++) {
            lg[i] = lg[i / 2] + 1;
        }
        
        // Initialize first column
        for (int i = 0; i < n; i++) {
            st[i][0] = arr[i];
        }
        
        // Build sparse table
        for (int j = 1; j < k; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = min(st[i][j-1], st[i + (1 << (j-1))][j-1]);
            }
        }
    }
    
    int query(int l, int r) {
        int j = lg[r - l + 1];
        return min(st[l][j], st[r - (1 << j) + 1][j]);
    }
};
