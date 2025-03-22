#pragma once

struct RangeMin {
    static const int identity = 0x7FFFFFFF;     // 최대 정수
    int merge(int a, int b) const { return a < b ? a : b; }
};

struct RangeMax {
    static const int identity = 0x80000000;     // 최소 정수
    int merge(int a, int b) const { return a < b ? b : a; }
};

struct RangeSum {
    static const int identity = 0;
    int merge(int a, int b) const { return a + b; }
};

template<typename Operation>
struct SegmentTree {
    int* tree;
    int n;
    static const int identity = Operation::identity;
    Operation op;

    SegmentTree(int* arr, int size) {
        n = size;
        tree = new int[4 * n];
        build(arr);
    }
    ~SegmentTree() { delete[] tree; }

    void build(int* arr) { build(arr, 1, 0, n - 1); }
    void update(int idx, int value) { update(idx, value, 1, 0, n - 1); }
    int query(int left, int right) { return query(left, right, 1, 0, n - 1); }

    int build(int* arr, int node, int start, int end) {
        if (start == end) return tree[node] = arr[start];

        int mid = start + (end - start) / 2;
        int lhs = build(arr, node*2, start, mid);
        int rhs = build(arr, node*2 + 1, mid + 1, end);
        return tree[node] = op.merge(lhs, rhs);
    }
    int query(int left, int right, int node, int start, int end) {
        if (right < start || left > end) return identity;
        if (left <= start && end <= right) return tree[node];

        int mid = (start + end) / 2;
        int lhs = query(left, right, node*2, start, mid);
        int rhs = query(left, right, node*2 + 1, mid + 1, end);
        return op.merge(lhs, rhs);
    }
    int update(int idx, int value, int node, int start, int end) {
        if (idx < start || idx > end) return tree[node];
        if (start == end) return tree[node] = value;

        int mid = (start + end) / 2;
        int lhs = update(idx, value, node*2, start, mid);
        int rhs = update(idx, value, node*2 + 1, mid + 1, end);
        return tree[node] = op.merge(lhs, rhs);
    }
};