#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    set<pii> S;  
    while (n--) {
        char op;
        cin >> op;
        if (op == 'A') {
            int l, r;
            cin >> l >> r;
            vector<pii> toRemove;
            auto it = S.lower_bound({l, -1});
            if (it != S.begin()) {
                auto pit = prev(it);
                if (pit->second >= l) {
                    toRemove.push_back(*pit);
                }
            }
            for (; it != S.end() && it->first <= r; ++it) {
                toRemove.push_back(*it);
            }
            for (auto &seg : toRemove) {
                S.erase(seg);
            }
            S.emplace(l, r);
            cout << toRemove.size() << "\n";

        } else if (op == 'B') {
            cout << S.size() << "\n";
        }
    }

    return 0;
}
