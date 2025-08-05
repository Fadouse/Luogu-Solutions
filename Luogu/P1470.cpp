#include <bits/stdc++.h>

using namespace std;
#define ll long long

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    set<string> strs;
    string t;
    bool first = false;
    string s;
    while (cin >> t)
    {
        if(t == ".") first = true;
        else {
            if(first){
                s+=t;
            }else{
                strs.insert(t);
            }
        }
    }
    int ans=0;

    s = " "+s;
    vector<int> f(s.size()+1, 0);
    f[0] = 1;
    for(int i=1; i<s.size(); i++){
        for(int j=i-1; j>=0 && i-j<=10; j--){
            string ss = s.substr(j+1, i-j);
            if(f[j] && strs.count(ss)){
                f[i] = true;
                ans = max(ans, i);
            }
        }
    }
    cout << ans;


    return 0;
}