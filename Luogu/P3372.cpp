#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = 1e5+5; //   原序列大小
ll ori[N]; // 原序列


struct node
{
    ll lt, rt; //  左右端点
    ll sum; //     值
    ll add; //     懒标记
}segtree[N*4];


/*
更新懒标记
时间复杂度O(1)
u 节点编号
add 需要懒更新的值
*/
ll addtag(ll u, ll add){
    segtree[u].sum += (segtree[u].rt - segtree[u].lt + 1)*add; //u区间子节点数量 x 单个节点需要更新的值
    segtree[u].add += add; //更新懒标记
    return 1;
}

/*
更新非叶子节点值
时间复杂度O(1)
u 节点编号
*/
ll pushup(ll u){
    segtree[u].sum = segtree[u<<1].sum+segtree[u<<1|1].sum;
    return segtree[u].sum;
}

/*
向下更新
时间复杂度O(1)
u 节点编号
*/
ll pushdown(ll u){
    if(segtree[u].add){
        addtag(u<<1, segtree[u].add);
        addtag(u<<1|1, segtree[u].add);
        segtree[u].add = 0;
    }
    return 1;
}

/*
构建线段树
时间复杂度位O(N)
u  节点编号
lt 左端点
rt 右端点
*/
ll buildtree(ll u, ll lt, ll rt){
    segtree[u] = {lt, rt}; //更新左右端点
    if(lt == rt) segtree[u].sum=ori[lt]; //判断是否为叶子节点，如果是则更新原序列对应的值
    else{
        //更新左右子树
        ll mid = (lt + rt) >> 1;
        buildtree(u<<1, lt, mid); //左子树
        buildtree(u<<1|1, mid+1, rt); //右子树

        //更新当前节点的值
        pushup(u);
    }
    return 1;
}

/*
单点查询
时间复杂度O(log n)
u 当前节点编号
t 目标元素(叶子节点)
*/
ll singlequery(ll u, ll t){
    pushdown(u); //如果u有懒标记，则更新子节点
    if(segtree[u].lt == segtree[u].rt) return segtree[u].sum; //判断是否为叶子节点，如果是则返回
    ll mid = (segtree[u].lt + segtree[u].rt) >> 1;
    return (t>mid)?
                singlequery(u<<1|1, t): //目标节点在左子树
                singlequery(u<<1, t); //目标节点在右子树
    return 1; //应该执行不到(?)
}

/*
单点修改
时间复杂度O(log n)
u 当前节点编号
t 目标元素(叶子节点)
v 修改后的值
*/
ll singleupdate(ll u, ll t, ll v){
    if(segtree[u].lt == segtree[u].rt) return segtree[u].sum = v; //更新目标节点的值
    pushdown(u); //如果u有懒标记，则更新子节点
    ll mid = (segtree[u].lt + segtree[u].rt) >> 1;
    (t>mid)?
            singleupdate(u<<1|1, t, v): //目标节点在左子树
            singleupdate(u<<1, t, v); //目标节点在右子树
    pushup(u); //更新当前节点
    return 1;
}

/*
区间查询
Q[lt, rt] = sigma(segtree.sum_i)
时间复杂度O(log n)
u  当前节点标号
lt 左端点
rt 右端点
*/
ll rangequery(ll u, ll lt, ll rt){
    if(segtree[u].lt >= lt && segtree[u].rt <= rt){ //当前u区间完全包含在[lt, rt](子区间)
        return segtree[u].sum; //直接返回当前区间的值
    }
    else if(segtree[u].lt > rt || segtree[u].rt < lt){ //u区间与[lt, rt]完全没有交集
        return 0; //不贡献
    }else{ //u区间与[lt, rt]有交集, 但不是[lt, rt]的子区间
        pushdown(u); //如果u有懒标记，则更新子节点
        return rangequery(u<<1, lt, rt) + rangequery(u<<1|1, lt, rt);
    }
    return 1; //按理说不会执行到这
}

/*
区间修改 with 懒标记
时间复杂度O(log n)
u  当前节点标号
lt 左端点
rt 右端点
v  添加的值
*/
ll rangeupdate(ll u, ll lt, ll rt, ll v){
    if(segtree[u].lt >= lt && segtree[u].rt <= rt){ //当前u区间完全包含在[lt, rt](子区间)
        return addtag(u, v); //添加懒标记
    }
    else if(segtree[u].lt > rt || segtree[u].rt < lt){ //u区间与[lt, rt]完全没有交集
        return 0; //不贡献
    }else{ //u区间与[lt, rt]有交集, 但不是[lt, rt]的子区间
        pushdown(u);
        rangeupdate(u<<1, lt, rt, v); //更新左节点
        rangeupdate(u<<1|1, lt, rt, v); //更新右节点
        pushup(u);
    }
    return 1; //按理说不会执行到这
}


int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    ll n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> ori[i]; //输入原序列
    buildtree(1, 1, n); //构建线段树
    while (m--) {
        ll op, x, y, v;
        cin >> op; //操作类型
        if(op == 2){ //区间查询
            cin >> x >> y; //左端点和右端点
            cout << rangequery(1, x, y) << '\n'; //输出区间查询结果
        }else if(op == 1){ //区间修改
            cin >> x >> y >> v; //左端点、右端点和添加的值
            rangeupdate(1, x, y, v); //执行区间修改
        }
    }
    
    return 0;
}