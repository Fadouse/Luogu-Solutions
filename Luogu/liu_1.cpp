#include <bits/stdc++.h>

using namespace std;

int main() {
    string S1;
    cin >> S1;
    cout << (((count(S1.begin(), S1.end(), "A1") + count(S1.begin(), S1.end(), "A2")*2) > (count(S1.begin(), S1.end(), "B1") + count(S1.begin(), S1.end(), "B2")*2)) ? 'A':'B') << "\n";
    return 0;
}