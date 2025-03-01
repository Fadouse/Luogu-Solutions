#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    long long sum = 0;
    int x;
    int cnt = 0;
    
    // Read numbers until EOF
    while (cin >> x) {
        sum += x;
        cnt++;
    }

    cout << (sum << (cnt - 1)) << "\n";
    
    return 0;
}