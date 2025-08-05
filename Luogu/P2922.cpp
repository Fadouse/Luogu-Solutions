#include <bits/stdc++.h>
using namespace std;

struct Trie {
    struct Node {
        int nxt[2];     // 子节点下标
        int pass;       // 经过该节点的串数量（本节点代表的前缀出现次数）
        int term;       // 正好在该节点结束的串数量
        Node() : pass(0), term(0) { nxt[0] = nxt[1] = -1; }
    };

    vector<Node> tr{Node()};           // 根节点编号 0

    /* 插入一条消息（二进制字符串） */
    void add(const string &s) {
        int u = 0;
        for (char c : s) {
            int bit = c - '0';
            if (tr[u].nxt[bit] == -1) {
                tr[u].nxt[bit] = tr.size();
                tr.emplace_back();
            }
            u = tr[u].nxt[bit];
            tr[u].pass++;              // 前缀计数
        }
        tr[u].term++;                  // 完整串计数
    }

    /* 查询一个 codeword 与多少消息匹配 */
    int query(const string &s) const {
        int u = 0;
        int ans = 0;

        for (char c : s) {
            ans += tr[u].term;         // 消息比 codeword 短且前缀相同
            int bit = c - '0';
            if (tr[u].nxt[bit] == -1)  // 前缀断裂
                return ans;
            u = tr[u].nxt[bit];
        }
        ans += tr[u].pass;             // 消息长度 ≥ codeword 长度且前缀相同
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    if (!(cin >> M >> N)) return 0;

    Trie trie;
    /* 读入并插入消息 */
    for (int i = 0; i < M; ++i) {
        int len; cin >> len;
        string s; s.reserve(len);
        for (int j = 0; j < len; ++j) {
            char bit; cin >> bit;
            s.push_back(bit);
        }
        trie.add(s);
    }

    /* 逐个处理 codeword 查询 */
    for (int i = 0; i < N; ++i) {
        int len; cin >> len;
        string s; s.reserve(len);
        for (int j = 0; j < len; ++j) {
            char bit; cin >> bit;
            s.push_back(bit);
        }
        cout << trie.query(s) << '\n';
    }
    return 0;
}
