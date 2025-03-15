#include <bits/stdc++.h>

using namespace std;
#define ll long long


int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    ll n;
    cin >> n;
    vector<pair<ll, ll>> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    ll cnt = 0;
    for(ll i=0;i<n-1;i++){
        for(ll j=i+1;j<n;j++){
            cnt += abs(a[i].second - a[j].second)*max(a[i].first, a[j].first);
        }
    }
    cout << cnt << '\n';

    
    return 0;
}
