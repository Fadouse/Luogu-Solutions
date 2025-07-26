#include <bits/stdc++.h>

using namespace std;
#define ll long long

struct Segtree {
    struct node
    {
        ll lt, rt; //  左右端点
        pair<ll,ll> pre, max, sub;
        ll sum;
        ll add; //     懒标记
    };
    vector<node> segtree;

    Segtree(const vector<ll>& nums){
        ll len = nums.size();
        segtree.assign(4*len, {});
        buildtree(1, 1, len, nums);
    }

    Segtree(const ll* nums, ll size){
        ll len = size;
        segtree.assign(4*len, {});
        vector<ll> vec; 
        copy(nums, nums + size, std::back_inserter(vec));
        buildtree(1, 1, len, vec);
    }

    inline void update(ll lt, ll rt, ll v){
        rangeupdate(1, lt, rt, v);
    }

    node query(ll lt, ll rt){
        return rangequery(1, lt, rt);
    }

private:

    int compose(int oldt, int op) {
        if (op==1||op==2) return op;     
        switch(oldt) {
            case 0: return 3;   // none → invert
            case 3: return 0;   // invert → none
            case 1: return 2;   // set0 → set1
            case 2: return 1;   // set1 → set0
        }
        return 0;
    }

    inline void addtag(ll u, ll op){
        ll len = segtree[u].rt - segtree[u].lt + 1;
        segtree[u].add = compose(segtree[u].add, op);
        if (op == 1) {           // set0
            segtree[u].sum = 0;
            segtree[u].pre = segtree[u].sub = segtree[u].max = {0, len};
        }
        else if (op == 2) {      // set1
            segtree[u].sum = len;
            segtree[u].pre = segtree[u].sub = segtree[u].max = {len, 0};
        }
        else {                   
            segtree[u].sum = len - segtree[u].sum;
            swap(segtree[u].pre.first, segtree[u].pre.second);
            swap(segtree[u].sub.first, segtree[u].sub.second);
            swap(segtree[u].max.first, segtree[u].max.second);
        }

    }

    inline void pushdown(ll u){
        if(segtree[u].add){
            addtag(u<<1, segtree[u].add);
            addtag(u<<1|1, segtree[u].add);
            segtree[u].add = 0;
        }
    }

    inline void pushup(node &root, node &left, node &right){
        root.sum = left.sum + right.sum;
        //维护前缀
        ll llen = left.rt - left.lt + 1;
        root.pre.first = left.pre.first;
        if(left.pre.first == llen){
            root.pre.first = llen + right.pre.first;
        }
        root.pre.second = left.pre.second;
        if(left.pre.second == llen){
            root.pre.second = llen + right.pre.second;
        }

        //维护后缀
        ll rlen = right.rt - right.lt + 1;
        root.sub.first = right.sub.first;
        if(right.sub.first == rlen){
            root.sub.first = rlen + left.sub.first;
        }
        root.sub.second = right.sub.second;
        if(right.sub.second == rlen){
            root.sub.second = rlen + left.sub.second;
        }

        //维护最大
        root.max.first = max({left.max.first, left.sub.first + right.pre.first, right.max.first});
        root.max.second = max({left.max.second, left.sub.second + right.pre.second, right.max.second});
    }

    inline void pushup(ll u){
        pushup(segtree[u] ,segtree[u<<1], segtree[u<<1|1]);
    }


    inline void buildtree(ll u, ll lt, ll rt, const vector<ll>& nums){
        segtree[u] = {lt, rt}; //更新左右端点
        if(lt == rt){
            auto &nd = segtree[u];
            ll v = nums[lt-1];
            nd.sum = v;
            if (v==1) {
            nd.pre = nd.sub = nd.max = {1,0};
            } else {
            nd.pre = nd.sub = nd.max = {0,1};
            }
            nd.add = 0;
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

    node rangequery(int u, int L, int R) {
        if (segtree[u].lt >= L && segtree[u].rt <= R)
            return segtree[u];
        if (segtree[u].rt < L || segtree[u].lt > R) {
            node nulln;
            nulln.lt = 1; nulln.rt = 0;       
            nulln.sum = 0;
            nulln.pre = nulln.sub = nulln.max = {0,0};
            nulln.add = 0;
            return nulln;
        }
        pushdown(u);
        node left  = rangequery(u<<1,  L, R);
        node right = rangequery(u<<1|1, L, R);
        node res;
        pushup(res, left, right);
        return res;
    }
    inline void rangeupdate(ll u, ll lt, ll rt, ll v){
        if(segtree[u].lt >= lt && segtree[u].rt <= rt){ //当前u区间完全包含在[lt, rt](子区间)
            return addtag(u, v); //添加懒标记
        }
        else if(segtree[u].lt > rt || segtree[u].rt < lt){ //u区间与[lt, rt]完全没有交集
            return; //不贡献
        }else{ //u区间与[lt, rt]有交集, 但不是[lt, rt]的子区间
            pushdown(u);
            rangeupdate(u<<1, lt, rt, v); //更新左节点
            rangeupdate(u<<1|1, lt, rt, v); //更新右节点
            pushup(u);
        }
        return; //按理说不会执行到这
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<ll> nums(n);
    for(int i=0;i<n;i++){
        cin >> nums[i];
    }
    Segtree st(nums);
    while (q--)
    {
        int op, lt, rt;
        cin >> op >> lt >> rt;
        lt++; rt++;
        if(op == 0){
            st.update(lt, rt, 1);
        }else if(op == 1){
            st.update(lt, rt, 2);
        }else if(op == 2){
            st.update(lt, rt, 3);
        }else if(op == 3){
            cout << st.query(lt, rt).sum << '\n';
        }else if(op == 4){
            cout << st.query(lt, rt).max.first << '\n';
        }
    }
    
    return 0;
}