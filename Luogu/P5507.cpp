#include <bits/stdc++.h>
using namespace std;

// 状态空间大小：4^12 = 1<<24
static const int MAXS = 1 << 24;

// 输入映射：a[i][j] 表示第 i 个旋钮在状态 j 下旋转时触发的旋钮
int a[12][5];

// 从状态 cur 通过正向操作（旋转 knob）生成下一个状态
inline uint32_t forward_step(uint32_t cur, int knob) {
    int shift1 = 2 * knob;
    int s1 = (cur >> shift1) & 3;            // 当前状态 0..3
    int ns1 = (s1 + 1) & 3;                  // 旋转后
    uint32_t nxt = (cur & ~(3u << shift1)) 
                   | (uint32_t(ns1) << shift1);
    // 触发的旋钮
    int trg = a[knob][s1 + 1];
    int shift2 = 2 * trg;
    int s2 = (nxt >> shift2) & 3;
    int ns2 = (s2 + 1) & 3;
    nxt = (nxt & ~(3u << shift2)) 
          | (uint32_t(ns2) << shift2);
    return nxt;
}

// 从状态 cur 生成所有可以一步“到达” cur 的前驱状态
inline void backward_steps(uint32_t cur, vector<pair<uint32_t,uint8_t>>& out) {
    // out 清空后，存 (pred_state, knob_index)
    out.clear();
    // 提前读出所有旋钮的位
    int cur_s[12];
    for(int i = 0; i < 12; i++){
        cur_s[i] = (cur >> (2*i)) & 3;
    }
    // 尝试每个旋钮 i，在某个状态 j（1..4）时旋转会到达 cur
    for(int i = 0; i < 12; i++){
        int shift1 = 2*i;
        for(int j = 1; j <= 4; j++){
            int k = a[i][j];  // 触发的旋钮
            int Ti;           // cur 上该 knob i 的值应该是谁
            if(k != i){
                // 正常：旋转 i 只 +1，故 cur_s[i] == j % 4
                Ti = j & 3;
                if(cur_s[i] != Ti) continue;
            } else {
                // 自触发：旋转 i 两次，故 cur_s[i] == (j%4 +1)%4
                Ti = ((j & 3) + 1) & 3;
                if(cur_s[i] != Ti) continue;
            }
            // 构造前驱 P = cur
            uint32_t P = cur;
            // P_i = j-1
            P = (P & ~(3u << shift1))
                | (uint32_t(j-1) << shift1);
            if(k != i){
                // 触发 knob k：前向 +1，逆向 -1
                int shift2 = 2*k;
                int sk = cur_s[k];
                int pk = (sk + 3) & 3;
                P = (P & ~(3u << shift2))
                    | (uint32_t(pk) << shift2);
            }
            // 记录：从 P 旋转 knob=i 可以到 cur
            out.emplace_back(P, uint8_t(i+1));
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读取初始状态和映射
    uint32_t start = 0;
    for(int i = 0; i < 12; i++){
        int s; cin >> s;
        start |= uint32_t(s-1) << (2*i);
        for(int j = 1; j <= 4; j++){
            cin >> a[i][j];
            --a[i][j];
        }
    }
    const uint32_t GOAL = 0;
    if(start == GOAL){
        cout << 0 << "\n\n";
        return 0;
    }

    // 双向访问标记、父节点和所用旋钮
    static bitset<MAXS> vis0, vis1;
    static uint32_t parent0[MAXS], parent1[MAXS];
    static uint8_t  mv0[MAXS], mv1[MAXS];

    // 当前层、下一层节点列表
    vector<uint32_t> cur0, next0, cur1, next1;
    cur0.reserve(1<<16); 
    cur1.reserve(1<<16);

    // 初始化
    vis0[start] = 1; parent0[start] = UINT32_MAX;
    vis1[GOAL] = 1; parent1[GOAL] = UINT32_MAX;
    cur0.push_back(start);
    cur1.push_back(GOAL);

    uint32_t meet = UINT32_MAX;
    bool found = false;
    vector<pair<uint32_t,uint8_t>> preds;
    // 交替扩展
    while(!cur0.empty() && !cur1.empty() && !found){
        // 选择节点较少的一边扩展
        if(cur0.size() <= cur1.size()){
            next0.clear();
            for(auto cur: cur0){
                for(int knob = 0; knob < 12; knob++){
                    uint32_t nxt = forward_step(cur, knob);
                    if(vis0[nxt]) continue;
                    vis0[nxt] = 1;
                    parent0[nxt] = cur;
                    mv0[nxt] = knob+1;
                    if(vis1[nxt]){
                        meet = nxt;
                        found = true;
                        break;
                    }
                    next0.push_back(nxt);
                }
                if(found) break;
            }
            cur0.swap(next0);
        } else {
            next1.clear();
            for(auto cur: cur1){
                backward_steps(cur, preds);
                for(auto &pr : preds){
                    uint32_t P = pr.first;
                    uint8_t knob = pr.second;
                    if(vis1[P]) continue;
                    vis1[P] = 1;
                    parent1[P] = cur;  // 从 P 旋转 knob -> cur
                    mv1[P] = knob;
                    if(vis0[P]){
                        meet = P;
                        found = true;
                        break;
                    }
                    next1.push_back(P);
                }
                if(found) break;
            }
            cur1.swap(next1);
        }
    }

    // 回溯：start -> meet
    vector<int> path;
    for(uint32_t s = meet; s != start; s = parent0[s]){
        path.push_back(mv0[s]);
    }
    reverse(path.begin(), path.end());
    // 回溯：meet -> goal
    for(uint32_t s = meet; s != GOAL; s = parent1[s]){
        path.push_back(mv1[s]);
    }

    // 输出
    cout << path.size() << "\n";
    for(int i = 0; i < (int)path.size(); i++){
        if(i) cout << ' ';
        cout << path[i];
    }
    cout << "\n";
    return 0;
}
