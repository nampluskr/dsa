#pragma once

struct FenwickTree {
    int* tree;  // BIT 배열
    int n;      // 배열 크기

    FenwickTree(int size) {
        n = size + 1;   // 1-based 인덱싱을 위해 크기를 1 증가
        tree = new int[n];
        for (int i = 0; i < n; i++) tree[i] = 0;
    }
    ~FenwickTree() { delete[] tree; }

    // 배열을 받아 BIT 구성
    void build(int* arr) {
        // 먼저 모든 값을 0으로 초기화
        for (int i = 0; i < n; i++) tree[i] = 0;
        
        // 원본 배열의 값을 이용해 BIT 구성
        for (int i = 0; i < n - 1; i++) update(i, arr[i]);
    }

    // idx 위치의 값을 value로 변경 (기존 값에 value를 더하는 것이 아님)
    void update(int idx, int value) {
        // 기존 값과의 차이를 계산해서 업데이트
        int diff = value - query(idx, idx);
        
        // 내부 업데이트 함수 호출
        add(idx, diff);
    }

    int query(int left, int right) {
        if (left > right) return 0;
        return sum(right) - sum(left - 1);  // [0, right] 합에서 [0, left-1] 합을 빼서 계산
    }

private:
    // idx 위치에 value를 더함
    void add(int idx, int value) {
        idx++; // 1-based 인덱싱으로 변환
        
        // 관련된 모든 구간 업데이트
        while (idx < n) {
            tree[idx] += value;
            idx += (idx & -idx); // 최하위 비트를 이용해 다음 위치로 이동
        }
    }

    // [0, idx] 구간의 합 반환 (내부 함수)
    int sum(int idx) {
        idx++; // 1-based 인덱싱으로 변환
        int result = 0;
        
        // 관련된 모든 구간의 합 계산
        while (idx > 0) {
            result += tree[idx];
            idx -= (idx & -idx); // 최하위 비트를 이용해 이전 위치로 이동
        }
        return result;
    }
};