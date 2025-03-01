#include <bits/stdc++.h>
using namespace std;

// 求解跨越中点的最大子段和
int maxCrossingSum(vector<int>& arr, int l, int m, int r) {
    // 求左半部分的最大和
    int leftSum = INT_MIN;
    int sum = 0;
    for (int i = m; i >= l; i--) {
        sum += arr[i];
        leftSum = max(leftSum, sum);
    }

    // 求右半部分的最大和
    int rightSum = INT_MIN;
    sum = 0;
    for (int i = m + 1; i <= r; i++) {
        sum += arr[i];
        rightSum = max(rightSum, sum);
    }

    // 返回跨越中点的最大和
    return leftSum + rightSum;
}

// 分治求解最大子段和
int maxSubArraySum(vector<int>& arr, int l, int r) {
    // 基础情况：只有一个元素
    if (l == r) return arr[l];

    // 找到中点
    int m = (l + r) / 2;
    return max({maxSubArraySum(arr, l, m),              // 左半部分
               maxSubArraySum(arr, m + 1, r),           // 右半部分
               maxCrossingSum(arr, l, m, r)});          // 跨越中点
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    cout << maxSubArraySum(a, 0, n-1) << endl;
    return 0;
}