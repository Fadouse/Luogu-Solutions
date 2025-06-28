// minHeap
#include <bits/stdc++.h>

using namespace std;

vector<int> heap;

// 下沉操作，用于维护堆属性
void heapify_down(int index) {
    int size = heap.size();
    while(index*2+1 < size) {
        int minIndex = index*2+1;
        if(index*2+2 < size && heap[index*2+2] < heap[minIndex]) {
            minIndex = index*2+2;
        }

        if(heap[index] > heap[minIndex]) {
            swap(heap[index], heap[minIndex]);
            index = minIndex;
        } else {
            break;
        }
    }
}

// O(n) 构建堆
void build_heap(vector<int>& arr) {
    heap = arr; 
    for(int i = heap.size()/2 - 1; i >= 0; i--) {
        heapify_down(i);
    }
}

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

int top() {
    if(heap.empty()) throw runtime_error("Heap is empty");
    return heap[0];
}

int pop() {
    if(heap.empty()) throw runtime_error("Heap is empty");
    int val = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if(!heap.empty()) {
        heapify_down(0);
    }
    return val;
}