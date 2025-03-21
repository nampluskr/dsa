#include "priority_queue.h"
#include <cstdio>

struct Data { 
    int x, y;
};

struct MaxCompare {
    bool operator()(const Data& a, const Data& b) const {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    }
};

struct MinCompare {
    bool operator()(const Data& a, const Data& b) const {
        return (a.x > b.x) || (a.x == b.x && a.y > b.y);
    }
};


int main() {
    // Max Heap 테스트 (최대값이 top에 오도록, less 사용)
    PriorityQueue<Data, MaxCompare> maxHeap;
    maxHeap.push({ 1, 10 });
    maxHeap.push({ 2, 5 });
    maxHeap.push({ 1, 5 });
    maxHeap.push({ 2, 10 });
    maxHeap.push({ 3, 0 });

    printf("\nMax Heap:\n");
    while (!maxHeap.empty()) {
        auto data = maxHeap.top();
        printf("Data: a = %d, b = %d\n", data.x, data.y);
        maxHeap.pop();
    }

    // Min Heap 테스트 (최소값이 top에 오도록, greater 사용)
    PriorityQueue<Data, MinCompare> minHeap;
    minHeap.push({ 1, 10 });
    minHeap.push({ 2, 5 });
    minHeap.push({ 1, 5 });
    minHeap.push({ 2, 10 });
    minHeap.push({ 3, 0 });

    printf("\nMin Heap:\n");
    while (!minHeap.empty()) {
        auto data = minHeap.top();
        printf("Data: a = %d, b = %d\n", data.x, data.y);
        minHeap.pop();
    }

    printf("\n");
    return 0;
}
