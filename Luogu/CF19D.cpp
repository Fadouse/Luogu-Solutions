#include <bits/stdc++.h>

using namespace std;

struct Segtree {
    struct node {
        int lt, rt;
        int maxy;
    };
    vector<node> segtree;

    Segtree(int size) {
        segtree.assign(4*size, {});
        buildtree(1, 1, size);
    }

    inline void set(int idx, int v) {
        singleupdate(1, idx, v);
    }

    int query(int lt, int t) {
        return rangequery(1, lt, t);
    }

private:
    inline void pushup(int u) {
        segtree[u].maxy = max(segtree[u<<1].maxy, segtree[u<<1|1].maxy);
    }

    inline void buildtree(int u, int lt, int rt) {
        segtree[u] = {lt, rt, 0};  // 初始化为0
        if(lt != rt) {
            int mid = (lt + rt) >> 1;
            buildtree(u<<1, lt, mid);
            buildtree(u<<1|1, mid+1, rt);
        }
    }

    int rangequery(int u, int lt, int t) {
        if(segtree[u].maxy <= t || segtree[u].rt < lt) {
            return -1;
        }
        if(segtree[u].lt >= lt && segtree[u].lt == segtree[u].rt) {
            return segtree[u].lt - 1; 
        }
        int left = rangequery(u<<1, lt, t);
        if(left != -1) return left;
        return rangequery(u<<1|1, lt, t);
    }

    inline void singleupdate(int u, int t, int v) {
        if(segtree[u].lt == segtree[u].rt) {
            segtree[u].maxy = v;
            return;
        }
        int mid = (segtree[u].lt + segtree[u].rt) >> 1;
        (t <= mid) ?
            singleupdate(u<<1, t, v) :
            singleupdate(u<<1|1, t, v);
        pushup(u);
    }
};

struct act {
    int x;
    int y;
    string op;
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int q;
    cin >> q;
    vector<act> acts(q);
    vector<int> allx(q);
    
    for(int i = 0; i < q; i++) {
        cin >> acts[i].op >> acts[i].x >> acts[i].y;
        allx[i] = acts[i].x;
    }

    sort(allx.begin(), allx.end());
    allx.erase(unique(allx.begin(), allx.end()), allx.end());
    int n = allx.size();
    
    vector<set<int>> xys(n); 
    Segtree st(n);
    
    for(int i = 0; i < q; i++) {
        string op = acts[i].op;
        int x = acts[i].x;
        int y = acts[i].y;
        int pos = lower_bound(allx.begin(), allx.end(), x) - allx.begin();

        if(op == "add") {
            xys[pos].insert(y);
            st.set(pos + 1, *xys[pos].rbegin()); 
        }
        else if(op == "remove") {
            xys[pos].erase(y);
            int maxy = 0;
            if(!xys[pos].empty()) {
                maxy = *xys[pos].rbegin();  
            }
            st.set(pos + 1, maxy); 
        }
        else if(op == "find") {
            int target_pos = upper_bound(allx.begin(), allx.end(), x) - allx.begin();
            int dx = st.query(target_pos + 1, y); 
            if(dx == -1) {
                cout << -1 << endl;
            } else {
                cout << allx[dx] << " " << *xys[dx].upper_bound(y) << endl;
            }
        }
    }
    
    return 0;
}