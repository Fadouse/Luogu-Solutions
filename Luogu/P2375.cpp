#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9+7;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n;
    cin >> n;
    while(n--){
        string p;
        cin >> p;
        vector<int> next(p.size(), 0);
        vector<int> cnt(p.size(), 0);
        vector<int> num(p.size(), 0);
        int j = 0;
        for(int i=1; i<p.size(); i++){
            while( j && p[j] != p[i]) j = next[j-1];
            if(p[j] == p[i]) j++;
            next[i] = j;

            //是否有相同前后最, j表示的是前缀的结尾索引
            if(j) {
                cnt[i] = cnt[j-1] + 1; 
            }
        }
        j=0;

        //不重叠
        for(int i=1; i<p.size(); i++){
            while( j && p[j] != p[i]) j = next[j-1];
            if(p[j] == p[i]) j++;
            while (j*2 > i+1)
            {
                j = next[j-1];
            }
            
            if(j) {
                num[i] = cnt[j-1]+1;
            }
        }
        long long ans = 1;
        for (int i = 0; i < p.size(); i++) {
            ans = (ans * (num[i] + 1)) % MOD;
        }
        cout << ans << "\n";

    }
    return 0;
}