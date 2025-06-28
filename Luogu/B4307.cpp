#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> A(n), B(n);
        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> B[i];
        }

        long long c01 = 0, c10 = 0;
        for (int i = 0; i < n; i++) {
            if (A[i] == 0 && B[i] == 1) {
                c01++;
            } else if (A[i] == 1 && B[i] == 0) {
                c10++;
            }
        }

        if ((c01 + c10) % 2 == 1) {
            cout << -1 << endl;
        } else {
            long long swaps = (c01 / 2) + (c10 / 2) + 2 * (c01 % 2);
            cout << swaps << endl;
        }
    }

    return 0;
}
