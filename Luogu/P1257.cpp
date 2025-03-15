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
    ll ans = 1e9;
    for(ll i=0;i<n;i++){
        for(ll j=0;j<n;j++){
            if(i == j)
                continue;
            ll x_diff = abs(a[i].first - a[j].first);
            ll y_diff = abs(a[i].second - a[j].second);
            ans = min(ans, x_diff * x_diff + y_diff * y_diff);   
        }
    }

    printf("%.4f\n", sqrt(ans));
    
    return 0;
}

