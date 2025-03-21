#pragma once

template<typename T>
struct Queue {
    T* arr;
    int head = 0, tail = -1, capacity = 1;

    Queue() { arr = new T[capacity]; }
    ~Queue() { delete[] arr; }

    void push(const T& data) {
        if (tail + 1 >= capacity) resize(capacity * 2);
        arr[++tail] = data;
    }
    void pop() {
        if (!empty()) head++;
    }
    T& front() { return arr[head]; }
    const T& front() const { return arr[head]; }

    void clear() { head = 0; tail = -1; }
    bool empty() const { return  tail + 1 - head == 0; }
    int size() const { return tail + 1 - head; }

private:
    void resize(int newCapacity) {
        T* temp = new T[newCapacity];
        for (int i = head; i <= tail; i++) temp[i - head] = arr[i];
        delete[] arr;
        arr = temp;
        tail = tail - head;
        head = 0;
        capacity = newCapacity;
    }
};
