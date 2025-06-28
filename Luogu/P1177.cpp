// minHeap
#include <bits/stdc++.h>

using namespace std;

vector<int> heap;

void push(int val) {
    heap.push_back(val);
    int index = heap.size() - 1;  
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent] > heap[index]) {
            swap(heap[parent], heap[index]);
            index = parent;
        } else {
            break;       
        }
    }
}

int top(){
    return heap[0];
}

int pop(){
    int val = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    int index = 0;
    while(index*2+1 < heap.size()){
        //找出左右子节点中较小的一个
        int minIndex = index*2+1;
        if(index*2+2 < heap.size() && heap[index*2+2] < heap[minIndex]){
            minIndex = index*2+2;
        }

        if(heap[index] > heap[minIndex]){
            swap(heap[index], heap[minIndex]);
            index = minIndex;
        } else {
            break;
        }
    }
    return val;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        push(x);
    }

    for(int i=0;i<n;i++){
        cout << top() << " ";
        pop();
    }

    return 0;
}