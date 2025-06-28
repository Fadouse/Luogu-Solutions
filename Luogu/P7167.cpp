#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    int a = 0, b = 0, i = 0; while (i < s.size() && !((a >= 11 || b >= 11) && abs(a - b) >= 2) && !((a >= 10 && b >= 10) && abs(a - b) >= 2)) s[i] == 'A' ? a += s[i+1] - '0' : b += s[i+1] - '0', i += 2;
    cout << (a > b ? 'A' : 'B') << "\n";
    return 0;
}