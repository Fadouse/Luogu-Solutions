#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    string A, B;
    cin >> A >> B;
    vector<pair<string, string>> rules;
    
    string a, b;
    while (cin >> a >> b)
    {
        rules.push_back({a, b});
    }
    
    queue<pair<string, int>> q;
    unordered_set<string> vis;
    vis.insert(A);

    q.push({A,0});
    while(q.size()){
        auto [cs, ct] = q.front(); q.pop();
        if(!B.compare(cs)){
            cout << ct;
            return 0;
        }
        if(ct > 10){
            break;
        }
        for(auto [s, d] : rules){
            for (size_t pos = cs.find(s); pos != string::npos;pos = cs.find(s, pos + 1)) {
                string nxt = cs;
                nxt.replace(pos, s.length(), d); 
                if (vis.insert(nxt).second)
                    q.push({nxt, ct + 1});
            }
        }
    }

    cout << "NO ANSWER!";
    
    return 0;
}