#pragma once

template<typename T, typename Compare>
struct PriorityQueue {
    T* arr;
    int cnt = 0, capacity = 1;
    Compare compare;

    PriorityQueue() { arr = new T[capacity]; }
    ~PriorityQueue() { delete[] arr; }

    // 복사 생성자
    PriorityQueue(const PriorityQueue& other) {
        cnt = other.cnt;
        capacity = other.capacity;
        arr = new T[capacity];
        for (int i = 0; i < cnt; ++i) arr[i] = other.arr[i];
    }
    
    // 대입 연산자
    PriorityQueue& operator=(const PriorityQueue& other) {
        if (this != &other) {
            delete[] arr;
            cnt = other.cnt;
            capacity = other.capacity;
            arr = new T[capacity];
            for (int i = 0; i < cnt; ++i) arr[i] = other.arr[i];
        }
        return *this;
    }

    void clear() { cnt = 0; }
    void push(const T& data) {
        if (cnt == capacity) resize(capacity * 2);
        arr[cnt] = data;
        siftUp(cnt);
        cnt++;
    }
    void pop() {
        cnt--;
        swap(arr[0], arr[cnt]);
        siftDown(0);
    }
    T top() { return arr[0]; }
    bool empty() { return cnt == 0; }
    int size() { return cnt; }

private:
    void resize(int newCapacity) {
        capacity = newCapacity;
        T* temp = new T[capacity];
        for (int i = 0; i < cnt; i++) temp[i] = arr[i];
        delete[] arr;
        arr = temp;
    }
    void siftUp(int curr) {
        int parent = (curr - 1) / 2;
        while (curr > 0) {
            if (compare(arr[curr], arr[parent])) break;
            swap(arr[curr], arr[parent]);
            curr = parent;
            parent = (curr - 1) / 2;
        }
    }
    void siftDown(int curr) {
        int child = 2 * curr + 1;
        while (child < cnt) {   // *** 주의 ***
            if (child + 1 < cnt && compare(arr[child], arr[child + 1])) child++;
            if (compare(arr[child], arr[curr])) break;
            swap(arr[child], arr[curr]);
            curr = child;
            child = 2 * child + 1;
        }
    }
    void swap(T& a, T& b) { T temp = a; a = b; b = temp; }
};
