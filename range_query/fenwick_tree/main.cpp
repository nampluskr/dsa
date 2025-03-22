#include <cstdio>
#include "fenwick_tree.h"

int main() {
    // 테스트 데이터
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("원본 배열: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
    
    // Fenwick Tree 생성 및 초기화
    FenwickTree fenwick(n);
    fenwick.build(arr);
    
    // 구간 합 쿼리 테스트
    printf("=== 구간 합 쿼리 테스트 ===\n");
    printf("쿼리 [2, 7]: %d\n", fenwick.query(2, 7)); // 5+7+9+11+13+15 = 60
    printf("쿼리 [0, 4]: %d\n", fenwick.query(0, 4)); // 1+3+5+7+9 = 25
    printf("쿼리 [5, 9]: %d\n", fenwick.query(5, 9)); // 11+13+15+17+19 = 75
    printf("쿼리 [0, 9]: %d\n", fenwick.query(0, 9)); // 모든 원소의 합 = 100
    
    // 업데이트 테스트
    printf("\n=== 업데이트 테스트 ===\n");
    printf("arr[3] 값을 7에서 10으로 변경\n");
    fenwick.update(3, 10);
    
    printf("쿼리 [2, 7]: %d\n", fenwick.query(2, 7)); // 5+10+9+11+13+15 = 63
    printf("쿼리 [0, 4]: %d\n", fenwick.query(0, 4)); // 1+3+5+10+9 = 28
    printf("쿼리 [0, 9]: %d\n", fenwick.query(0, 9)); // 전체 합 = 103
    
    // add 함수 테스트 (증분 업데이트)
    printf("\n=== 증분 업데이트 테스트 ===\n");
    printf("arr[5]에 5를 더함 (11 -> 16)\n");
    fenwick.add(5, 5);
    
    printf("쿼리 [2, 7]: %d\n", fenwick.query(2, 7)); // 5+10+9+16+13+15 = 68
    printf("쿼리 [5, 9]: %d\n", fenwick.query(5, 9)); // 16+13+15+17+19 = 80
    printf("쿼리 [0, 9]: %d\n", fenwick.query(0, 9)); // 전체 합 = 108
    
    return 0;
}