#include <bits/stdc++.h>
using namespace std;
 
static const int MOD = 1000000007;
 
// 快速幂，计算 2^x mod MOD
long long modPow2(long long x) {
    const long long base = 2;
    long long ans = 1, cur = base;
    while (x > 0) {
        if (x & 1) ans = (ans * cur) % MOD;
        cur = (cur * cur) % MOD;
        x >>= 1;
    }
    return ans;
}
 
// 区间结构体，记录区间左右端点以及对应的比特值（0 或 1）
struct Segment {
    long long start, end;  // 区间左右端点
    int bit;               // 区间比特值
};
 
// 全局合并区间数组（按起点排序）
vector<Segment> merged;
 
// 用于二分查找：根据区间的 end 与给定的值比较
bool cmpEnd(const Segment &seg, long long x) {
    return seg.end < x;
}
 
// 用于二分查找：根据给定的值与区间的 start 比较
bool cmpStart(long long x, const Segment &seg) {
    return x < seg.start;
}
 
// 模拟函数，用于在给定的查询区间子区间上更新答案，采用贪心策略
// subSeg：每个元素为 {bit, length}，表示查询区间内一个连续区间的比特和长度
// k：查询需要取的位数
long long simulateQuery(const vector<pair<int, long long>> &subSeg, long long k) {
    long long need = k;
    long long answer = 0;
    long long totalLen = 0;
    for (auto &pp : subSeg)
        totalLen += pp.second;
    long long remain = totalLen;
 
    // 按顺序处理各个区间片段
    for (int i = 0; i < (int)subSeg.size() && need > 0; i++) {
        int b = subSeg[i].first;
        long long len = subSeg[i].second;
 
        if (b == 1) {
            // 比特 1 的区间：尽可能取尽
            long long x = min(len, need);
            long long pow2x = modPow2(x);
            answer = (answer * pow2x) % MOD;
            // 加上这一段贡献 (2^x - 1)
            answer = (answer + (pow2x - 1 + MOD) % MOD) % MOD;
 
            need -= x;
            remain -= len;
        } else {
            // 比特 0 的区间：可选择跳过部分位
            long long skipCount = 0;
            if (remain > need) {
                // 尽可能跳过一些位（不影响后续必选的位数）
                skipCount = min(len, remain - need);
            }
            long long leftover = len - skipCount;
            remain -= len;
            long long pickX = min(leftover, need);
            if (pickX > 0) {
                long long pow2x = modPow2(pickX);
                answer = (answer * pow2x) % MOD;
                // 对于比特 0 的区间，无需额外加上数值
                need -= pickX;
            }
        }
    }
    return answer % MOD;
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    long long N;
    int M, Q;
    cin >> N >> M >> Q;
    vector<long long> endpoints;
    endpoints.reserve(2 * M + 2);
 
    // 差分数组，记录区间加减操作
    unordered_map<long long,int> diff;
    diff.reserve(M*2 + 4);
    diff.max_load_factor(0.7f);
 
    // 输入区间，构建差分
    for(int i = 0; i < M; i++){
        long long L, R;
        cin >> L >> R;
        diff[L] += 1;
        if(R + 1 <= N) {
            diff[R + 1] -= 1;
        }
    }
 
    // 收集所有端点
    endpoints.push_back(1);
    endpoints.push_back(N + 1LL);
    for(auto &kv : diff){
        long long p = kv.first;
        if(p >= 1 && p <= N + 1) {
            endpoints.push_back(p);
        }
    }
    sort(endpoints.begin(), endpoints.end());
    endpoints.erase(unique(endpoints.begin(), endpoints.end()), endpoints.end());
 
    long long curSum = 0;
    vector<Segment> segs;
    segs.reserve(endpoints.size());
 
    // 利用差分构造连续区间的比特值
    for(int i = 0; i + 1 < (int)endpoints.size(); i++){
        long long x = endpoints[i];
        long long nx = endpoints[i + 1];
        if(diff.find(x) != diff.end()) {
            curSum += diff[x];
        }
        int par = (curSum % 2 + 2) % 2;  // 当前区间比特值
 
        if(x <= N) {
            long long segStart = x;
            long long segEnd   = nx - 1;
            if(segStart <= segEnd && segStart <= N) {
                if(segEnd > N) segEnd = N;
                if(segStart <= segEnd) {
                    segs.push_back({segStart, segEnd, par});
                }
            }
        }
    }
 
    // 合并相邻且比特相同的区间
    merged.reserve(segs.size());
    merged.push_back(segs[0]);
    for(int i = 1; i < (int)segs.size(); i++){
        Segment &prev = merged.back();
        if(segs[i].bit == prev.bit && segs[i].start == prev.end + 1) {
            prev.end = segs[i].end;  // 扩展区间
        } else {
            merged.push_back(segs[i]);
        }
    }
    segs.clear();
 
    // 为便于二分查找，按起点排序（理论上 merged 已经按区间顺序）
    sort(merged.begin(), merged.end(), [](const Segment &a, const Segment &b){
        return a.start < b.start;
    });
 
    // 处理每个查询
    while(Q--){
        long long L, R, k;
        cin >> L >> R >> k;
 
        // 利用二分查找确定查询 [L, R] 内的合并区间
        // 找第一个区间：其 end >= L
        int idxStart = lower_bound(merged.begin(), merged.end(), L, cmpEnd) - merged.begin();
        // 找最后一个区间：其 start <= R
        int idxEnd = (upper_bound(merged.begin(), merged.end(), R, cmpStart) - merged.begin()) - 1;
 
        vector<pair<int,long long>> subSeg;
        if(idxStart < (int)merged.size() && idxEnd >= idxStart) {
            for (int i = idxStart; i <= idxEnd; i++){
                long long segL = merged[i].start, segR = merged[i].end;
                // 取 [max(segL, L), min(segR, R)] 交集
                long long qs = max(segL, L), qe = min(segR, R);
                if(qs <= qe) {
                    long long len = qe - qs + 1;
                    subSeg.push_back({merged[i].bit, len});
                }
            }
        }
 
        long long answer = simulateQuery(subSeg, k);
        cout << answer % MOD << "\n";
    }
 
    return 0;
}
