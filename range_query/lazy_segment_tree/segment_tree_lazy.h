#pragma once

struct RangeMin {
    static const int identity = 0x7FFFFFFF;     // 최대 정수
    int merge(int a, int b) const { return a < b ? a : b; }
    int update(int value, int size) const { return value; }
};

struct RangeMax {
    static const int identity = 0x80000000;     // 최소 정수
    int merge(int a, int b) const { return a < b ? b : a; }
    int update(int value, int size) const { return value; }
};

struct RangeSum {
    static const int identity = 0;
    int merge(int a, int b) const { return a + b; }
    int update(int value, int size) const { return value * size; }
};

template<typename Operation>
struct SegmentTreeLazy {
    int* tree;
    int* lazyValue;    // 지연된 업데이트 값
    bool* lazyExist;   // 지연된 업데이트 존재 여부
    int n;
    static const int identity = Operation::identity;
    Operation op;      // Operation 인스턴스 생성

    SegmentTreeLazy(int* arr, int size) {
        n = size;
        tree = new int[4 * n];
        lazyValue = new int[4 * n];
        lazyExist = new bool[4 * n];

        for (int i = 0; i < 4 * n; i++) {
            lazyValue[i] = 0;
            lazyExist[i] = false;
        }
        build(arr);
    }
    ~SegmentTreeLazy() {
        delete[] tree;
        delete[] lazyValue;
        delete[] lazyExist;
    }
    void build(int* arr) { build(arr, 1, 0, n - 1); }
    void update(int idx, int value) { update(idx, idx, value, 1, 0, n - 1); }
    void update(int left, int right, int value) { update(left, right, value, 1, 0, n - 1); }
    int query(int left, int right) { return query(left, right, 1, 0, n - 1); }

private:
    int build(int* arr, int node, int start, int end) {
        if (start == end) return tree[node] = arr[start];

        int mid = start + (end - start) / 2;
        int lhs = build(arr, node*2, start, mid);
        int rhs = build(arr, node*2 + 1, mid + 1, end);
        return tree[node] = op.merge(lhs, rhs);
    }
    void propagate(int node, int start, int end) {
        if (lazyExist[node]) {
            tree[node] += op.update(lazyValue[node], end - start + 1);
            if (start != end) {
                // 왼쪽 자식에 업데이트 전파
                lazyValue[node * 2] += lazyValue[node];
                lazyExist[node * 2] = true;
                // 오른쪽 자식에 업데이트 전파
                lazyValue[node * 2 + 1] += lazyValue[node];
                lazyExist[node * 2 + 1] = true;
            }
            lazyValue[node] = 0;
            lazyExist[node] = false;
        }
    }
    int query(int left, int right, int node, int start, int end) {
        propagate(node, start, end);                            // 대기 중인 업데이트 전파
        if (right < start || left > end) return identity;       // 겹치지 않는 경우
        if (left <= start && end <= right) return tree[node];   // 완전히 포함되는 경우

        // 부분적으로 겹치는 경우
        int mid = (start + end) / 2;
        int lhs = query(left, right, node*2, start, mid);
        int rhs = query(left, right, node*2 + 1, mid + 1, end);
        return op.merge(lhs, rhs);
    }
    int update(int left, int right, int value, int node, int start, int end) {
        propagate(node, start, end);                           // 대기 중인 업데이트 전파
        if (right < start || left > end) return tree[node];    // 겹치지 않는 경우
        if (left <= start && end <= right) {                   // 완전히 포함되는 경우
            lazyValue[node] = value;
            lazyExist[node] = true;

            propagate(node, start, end);
            return tree[node];
        }
        // 부분적으로 겹치는 경우
        int mid = (start + end) / 2;
        int lhs = update(left, right, value, node*2, start, mid);
        int rhs = update(left, right, value, node*2 + 1, mid + 1, end);
        return tree[node] = op.merge(lhs, rhs);
    }
};