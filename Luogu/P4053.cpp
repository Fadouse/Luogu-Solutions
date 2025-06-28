#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<pair<long long, long long>> tasks;
    tasks.reserve(N);
    for (int i = 0; i < N; i++) {
        long long t, d;
        cin >> t >> d;               // t = repair time, d = deadline
        tasks.emplace_back(t, d);
    }

    // 按 deadline 升序排序
    sort(tasks.begin(), tasks.end(),
         [](auto a,
            auto b) {
             return a.second < b.second;
         });

    priority_queue<long long> pq;    // 存放已选任务的 repair time
    long long curr_time = 0;
    for (auto& task : tasks) {
        long long t = task.first;
        long long d = task.second;

        curr_time += t;
        pq.push(t);

        // 若超过当前任务的截止时间，则剔除耗时最长的那项
        if (curr_time > d) {
            curr_time -= pq.top();
            pq.pop();
        }
    }

    // 剩余队列大小即为最多可完成的任务数
    cout << pq.size() << "\n";
    return 0;
}