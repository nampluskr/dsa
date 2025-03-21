#pragma once

template<typename T>
struct Vector {
    T* arr;
    int tail = -1, capacity = 1;

    Vector() { arr = new T[capacity]; }
    ~Vector() { delete[] arr; }

    void push_back(const T& data) {
        if (tail == capacity - 1) resize(capacity * 2);
        arr[++tail] = data;
    }
    void pop_back() {
        if (tail >= 0) tail--;
    }
    void clear() { tail = -1; }
    int size() const { return tail + 1; }
    bool empty() const { return tail == -1; }

    T& operator[](int idx) { return arr[idx]; }
    T* begin() { return arr; }
    T* end() { return arr + tail + 1; }

    const T& operator[](int idx) const { return arr[idx]; }
    const T* begin() const { return arr; }
    const T* end() const { return arr + tail + 1; }

private:
    void resize(int newCapacity) {
        capacity = newCapacity;
        T* temp = new T[capacity];
        for (int i = 0; i <= tail; i++) temp[i] = arr[i];
        delete[] arr;
        arr = temp;
    }
};