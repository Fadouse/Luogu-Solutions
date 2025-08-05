#include <bits/stdc++.h>
using namespace std;

void dfs(int rem, int last, string curr, vector<string>& res) {
    if(rem == 0){
        res.emplace_back(curr.substr(1));
    }else{
        for(int i=last; i<=rem;i++){
            dfs(rem - i, i, curr + "+" + to_string(i), res);
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;

    vector<string> expr;
    dfs(n, 1, "", expr);
    
    expr.erase(expr.begin() + expr.size());
    for (const auto& s : expr) cout << s << '\n';
    return 0;

}
