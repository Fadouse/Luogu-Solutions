#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int a[5] = {1,2,3,4,5};
    int *p = a+2;
    cout << a[1]+2;
    cout << *(p++);
    cout << p[0];
    cout << *(a+3);
    return 0;
}