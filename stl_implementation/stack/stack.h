#pragma once

template<typename T>
struct Stack {
    T* arr;
    int tail = -1, capacity = 1;

    Stack() { arr = new T[capacity]; }
    ~Stack() { delete[] arr; }

    void push(const T& data) {
        if (tail + 1 >= capacity) resize(capacity * 2);
        arr[++tail] = data;
    }
    void pop() {
        if (!empty()) tail--; 
    }
    T& top() { return arr[tail]; }
    const T& top() const { return arr[tail]; }

    void clear() { tail = -1; }
    bool empty() const { return tail == -1; }
    int size() const { return tail + 1; }

private:
    void resize(int newCapacity) {
        capacity = newCapacity;
        T* temp = new T[capacity];
        for (int i = 0; i <= tail; i++) temp[i] = arr[i];
        delete[] arr;
        arr = temp;
    }
};