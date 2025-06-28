#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<long long> A(N), B(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> B[i];
    }

    // 定义堆中记录的节点类型：(sum, i, j)
    //   sum = A[i] + B[j]，i 表示当前“行”，j 表示在该行中的索引
    // 使用 tuple<long long,int,int>，并配合 greater<> 实现最小堆
    using Node = tuple<long long,int,int>;

    // min-heap：按 sum 从小到大排列
    priority_queue<Node, vector<Node>, greater<Node>> minHeap;

    // 初始阶段：将每一行 i 的 j=0（即 A[i] + B[0]）全部 push
    for (int i = 0; i < N; i++) {
        long long s = A[i] + B[0];
        minHeap.emplace(s, i, 0);
    }

    // 结果直接输出最小的 N 个 sum
    // 为了输出格式，先把结果放到 vector 中；也可以直接边 pop 边打印
    vector<long long> answer;
    answer.reserve(N);

    for (int k = 0; k < N; k++) {
        auto [sum, i, j] = minHeap.top();
        minHeap.pop();

        answer.push_back(sum);

        if (j + 1 < N) {
            long long nextSum = A[i] + B[j + 1];
            minHeap.emplace(nextSum, i, j + 1);
        }
    }

    // 输出时用空格分隔
    for (int i = 0; i < N; i++) {
        if (i > 0) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';

    return 0;
}
