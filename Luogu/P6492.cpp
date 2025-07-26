#include <bits/stdc++.h>

using namespace std;
#define ll long long

struct Segtree{
    struct node
    {
        ll lt, rt; //  左右端点
        ll len;
        ll prelen, sublen;
        ll left, right;
    };
    vector<node> segtree;

    Segtree(const vector<ll>& nums){
        ll len = nums.size();
        segtree.assign(4*len, {});
        buildtree(1, 1, len, nums);
    }

    inline void set(ll idx){
        singleupdate(1, idx);
    }

    ll query(){
        return segtree[1].len;
    }

private:
    /*
    更新非叶子节点值
    时间复杂度O(1)
    u 节点编号
    */
    inline void pushup(ll u){
        node &root = segtree[u];
        node &lc = segtree[u<<1];
        node &rc = segtree[u<<1|1];
        //最大值
        root.len = max(lc.len, rc.len);
        //链接左右
        if(lc.right != rc.left)
            root.len = max(root.len,lc.sublen+rc.prelen);
        //继承或扩展子节点前缀长度
        root.prelen = lc.prelen;
        if(lc.len == lc.rt-lc.lt+1 && lc.right != rc.left)
            root.prelen = max(root.prelen, lc.rt-lc.lt+1+rc.prelen);
        //继承或扩展子节点后缀长度
        root.sublen=rc.sublen;
        if(rc.len == rc.rt-rc.lt+1 && lc.right != rc.left)
            root.sublen=max(root.sublen, rc.rt-rc.lt+1+lc.sublen);

        //更新左右端点的值
        root.left = lc.left;
        root.right = rc.right;
    }

    /*
    构建线段树
    时间复杂度位O(N)
    u  节点编号
    lt 左端点
    rt 右端点
    */
    inline void buildtree(ll u, ll lt, ll rt, const vector<ll>& nums){
        segtree[u] = {lt, rt}; //更新左右端点
        if(lt == rt){
            segtree[u].len = segtree[u].sublen = segtree[u].prelen = 1;
            segtree[u].right = segtree[u].left = 0;
        }
        else{
            //更新左右子树
            ll mid = (lt + rt) >> 1;
            buildtree(u<<1, lt, mid, nums); //左子树
            buildtree(u<<1|1, mid+1, rt, nums); //右子树

            //更新当前节点的值
            pushup(u);
        }
    }

    /*
    单点修改
    时间复杂度O(log n)
    u 当前节点编号
    t 目标元素(叶子节点)
    v 修改后的值
    */
    inline void singleupdate(ll u, ll t){
        if(segtree[u].lt == segtree[u].rt){
            segtree[u].left = segtree[u].right = 1^segtree[u].left; //更新目标节点的值
            return;
        }
        ll mid = (segtree[u].lt + segtree[u].rt) >> 1;
        (t<=mid)?
                singleupdate(u<<1, t): //目标节点在左子树
                singleupdate(u<<1|1, t); //目标节点在右子树
        pushup(u); //更新当前节点
    }

};
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    Segtree st(vector<ll>(n,0));

    while (q--)
    {
        int idx;
        cin >> idx;
        st.set(idx);
        cout << st.query() << '\n';
    }
    

    return 0;
}