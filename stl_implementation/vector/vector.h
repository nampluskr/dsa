#pragma once

template<typename T>
struct Vector {
    T* arr;
    int tail = -1, capacity = 1;

    Vector() { arr = new T[capacity]; }
    ~Vector() { delete[] arr; }

    // 복사 생성자: other의 capacity와 tail을 복사하고, 새로운 메모리를 할당하여 요소들을 복사
    Vector(const Vector& other) {
        capacity = other.capacity;
        tail = other.tail;
        arr = new T[capacity];
        for (int i = 0; i <= tail; i++) arr[i] = other.arr[i];
    }

    // 복사 대입 연산자: 자기 자신과의 대입을 체크한 후, 기존 메모리를 해제하고 other의 데이터를 깊은 복사
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] arr;
            capacity = other.capacity;
            tail = other.tail;
            arr = new T[capacity];
            for (int i = 0; i <= tail; i++) arr[i] = other.arr[i];
        }
        return *this;
    }

    void push_back(const T& data) {
        if (tail == capacity - 1) resize(capacity * 2);
        arr[++tail] = data;
    }
    void pop_back() { 
        if (!empty()) tail--;
    }
    void clear() { tail = -1; }
    bool empty() const { return tail == -1; }
    int size() const { return tail + 1; }

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