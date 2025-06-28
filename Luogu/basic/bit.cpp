class BIT {
private:
    vector<long long> tree;
    int n;
    
public:
    BIT(int size) {
        n = size;
        tree.assign(n + 1, 0);
    }
    
    void update(int pos, int val) {
        for (int i = pos; i <= n; i += i & (-i)) {
            tree[i] += val;
        }
    }
    
    long long query(int pos) {
        long long sum = 0;
        for (int i = pos; i > 0; i -= i & (-i)) {
            sum += tree[i];
        }
        return sum;
    }
    
    long long rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};