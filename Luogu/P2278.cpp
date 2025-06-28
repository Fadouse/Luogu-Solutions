#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 进程结构
struct Process {
    int pid;        // 进程号
    ll arrival;     // 到达时间
    ll rem;         // 剩余执行时间
    int priority;   // 优先级
};

// 等待队列比较器：优先级高的先出队；相同优先级时，到达时间早的先出队
struct Cmp {
    bool operator()(Process* a, Process* b) const {
        if (a->priority != b->priority)
            return a->priority < b->priority;        // 优先级小的“更小”
        return a->arrival > b->arrival;              // 到达时间晚的“更小”
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读取所有进程（输入按到达时间升序）
    vector<Process> procs;
    procs.reserve(1e5);
    while (true) {
        Process p;
        if (!(cin >> p.pid >> p.arrival >> p.rem >> p.priority))
            break;
        procs.push_back(p);
    }

    int n = procs.size();
    int idx = 0;                              // 下一个待处理的到达进程索引
    priority_queue<Process*, vector<Process*>, Cmp> waitq;
    vector<pair<int,ll>> finish_order;
    finish_order.reserve(n);

    ll current_time = 0;
    Process* cur = nullptr;
    while (idx < n || cur != nullptr || !waitq.empty()) {
        if (cur == nullptr) {
            if (!waitq.empty()) {
                cur = waitq.top();
                waitq.pop();
            }
            else if (idx < n) {
                current_time = max(current_time, procs[idx].arrival);
                ll t0 = procs[idx].arrival;
                while (idx < n && procs[idx].arrival == t0) {
                    waitq.push(&procs[idx]);
                    idx++;
                }
                cur = waitq.top();
                waitq.pop();
            }
        }
        else {
            ll next_arrival = (idx < n ? procs[idx].arrival : LLONG_MAX);
            ll finish_time = current_time + cur->rem;

            if (next_arrival < finish_time) {
                // 在运行完成前，有新进程到达
                ll delta = next_arrival - current_time;
                cur->rem -= delta;
                current_time = next_arrival;

                Process* newcomer = &procs[idx++];
                if (newcomer->priority > cur->priority) {
                    waitq.push(cur);
                    cur = newcomer;
                } else {
                    waitq.push(newcomer);
                }
            }
            else {
                current_time = finish_time;
                finish_order.emplace_back(cur->pid, current_time);
                cur = nullptr;
            }
        }
    }

    for (auto &pr : finish_order) {
        cout << pr.first << ' ' << pr.second << "\n";
    }

    return 0;
}
