#pragma once

struct FenwickTreeRange {
    int* tree1;         // 첫 번째 BIT: B1[i] = (i+1)*A[i] - i*A[i-1] 형태의 값 저장
    int* tree2;         // 두 번째 BIT: B2[i] = A[i] 형태의 값 저장
    int n;              // 배열 크기

    // 배열 크기만 받는 생성자
    FenwickTreeRange(int size) {
        n = size + 1;   // 1-based 인덱싱을 위해 크기를 1 증가
        tree1 = new int[n];
        tree2 = new int[n];
        for (int i = 0; i < n; i++) {
            tree1[i] = 0;
            tree2[i] = 0;
        }
    }

    ~FenwickTreeRange() {
        delete[] tree1;
        delete[] tree2;
    }

    // 배열을 받아 BIT 구성
    void build(int* arr) {
        // 먼저 모든 값을 0으로 초기화
        for (int i = 0; i < n; i++) {
            tree1[i] = 0;
            tree2[i] = 0;
        }
        
        // 원본 배열의 값을 이용해 각 위치를 개별적으로 업데이트
        for (int i = 0; i < n - 1; i++) {
            update(i, i, arr[i]);
        }
    }

    // 내부적으로 Fenwick Tree 갱신 (단일 위치)
    void add(int* tree, int idx, int val) {
        idx++; // 1-based 인덱싱으로 변환
        while (idx < n) {
            tree[idx] += val;
            idx += (idx & -idx); // 최하위 비트를 이용해 다음 위치로 이동
        }
    }

    // 내부적으로 Fenwick Tree 합 계산
    int sum(int* tree, int idx) {
        idx++; // 1-based 인덱싱으로 변환
        int result = 0;
        while (idx > 0) {
            result += tree[idx];
            idx -= (idx & -idx); // 최하위 비트를 이용해 이전 위치로 이동
        }
        return result;
    }

    // [left, right] 구간의 모든 원소에 val을 더함
    void update(int left, int right, int val) {
        // 첫 번째 BIT 업데이트
        add(tree1, left, val);
        add(tree1, right + 1, -val);
        
        // 두 번째 BIT 업데이트 (위치 가중치 고려)
        add(tree2, left, val * left);
        add(tree2, right + 1, -val * (right + 1));
    }

    // idx 위치의 현재 값을 구함
    int pointQuery(int idx) {
        return sum(tree1, idx);
    }

    // [0, idx] 구간의 합을 구함
    int prefixSum(int idx) {
        return sum(tree1, idx) * (idx + 1) - sum(tree2, idx);
    }

    // [left, right] 구간의 합을 구함
    int query(int left, int right) {
        if (left > right) return 0;
        if (left == 0) return prefixSum(right);
        return prefixSum(right) - prefixSum(left - 1);
    }
};