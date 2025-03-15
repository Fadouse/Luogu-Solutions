#include <bits/stdc++.h>
using namespace std;

// 定义事件结构体
struct Event {
    int x;      // 横坐标
    int h;      // 建筑高度
    bool start; // true 表示建筑起点（左端点），false 表示建筑终点（右端点）
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<Event> events;
    int L, H, R;
    // 读入每幢建筑的三个数据
    while(cin >> L >> H >> R) {
        // 左端点事件：标记为开始事件
        events.push_back({L, H, true});
        // 右端点事件：标记为结束事件
        events.push_back({R, H, false});
    }
    
    // 按照 x 坐标排序，当 x 坐标相同时，规则如下：
    // 1. 左端点事件先于右端点事件；
    // 2. 对于左端点事件，高度高的优先；
    // 3. 对于右端点事件，高度低的优先。
    sort(events.begin(), events.end(), [](const Event &a, const Event &b) {
        if(a.x != b.x)
            return a.x < b.x;
        else {
            // 如果两个事件在同一个 x 坐标上
            if(a.start && b.start)
                return a.h > b.h;  // 左端点中高度大的优先
            if(!a.start && !b.start)
                return a.h < b.h;  // 右端点中高度小的优先
            return a.start;       // 左端点先于右端点
        }
    });
    
    multiset<int> heights; // 用来维护当前扫描线下的所有建筑高度
    heights.insert(0);     // 地面高度
    
    int prevMax = 0;
    vector<pair<int,int>> skyline; // 存储结果，每个元素为 (x, height)
    
    // 扫描所有事件
    for (auto &e : events) {
        if(e.start) {
            // 遇到左端点，加入建筑高度
            heights.insert(e.h);
        } else {
            // 遇到右端点，从集合中删除一个高度
            auto it = heights.find(e.h);
            if(it != heights.end()) {
                heights.erase(it);
            }
        }
        // 当前最高高度
        int currMax = *heights.rbegin();
        if(currMax != prevMax) {
            // 当最高高度发生变化，记录折点
            skyline.push_back({e.x, currMax});
            prevMax = currMax;
        }
    }
    
    // 输出所有折点，按照题目要求空格分隔
    // 注意输出顺序为：x1 h1 x2 h2 ... 
    for (auto &p : skyline) {
        cout << p.first << " " << p.second << " ";
    }
    cout << "\n";
    
    return 0;
}
