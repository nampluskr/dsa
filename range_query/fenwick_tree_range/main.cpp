#include <cstdio>
#include "fenwick_tree_range.h"

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
    FenwickTreeRange fenwick(n);
    fenwick.build(arr);
    
    // 초기 구간 합 쿼리 테스트
    printf("=== 초기 구간 합 쿼리 테스트 ===\n");
    printf("쿼리 [2, 7]: %d\n", fenwick.query(2, 7)); // 5+7+9+11+13+15 = 60
    printf("쿼리 [0, 4]: %d\n", fenwick.query(0, 4)); // 1+3+5+7+9 = 25
    printf("쿼리 [5, 9]: %d\n", fenwick.query(5, 9)); // 11+13+15+17+19 = 75
    printf("쿼리 [0, 9]: %d\n", fenwick.query(0, 9)); // 모든 원소의 합 = 100
    
    // 단일 위치 업데이트 테스트
    printf("\n=== 단일 위치 업데이트 테스트 ===\n");
    printf("arr[3] 값을 7에서 10으로 변경 (차이: +3)\n");
    fenwick.update(3, 3, 3); // 7에 3을 더해 10으로 변경
    
    printf("쿼리 [2, 7]: %d\n", fenwick.query(2, 7)); // 5+10+9+11+13+15 = 63
    printf("쿼리 [0, 4]: %d\n", fenwick.query(0, 4)); // 1+3+5+10+9 = 28
    printf("쿼리 [0, 9]: %d\n", fenwick.query(0, 9)); // 전체 합 = 103
    
    // 구간 업데이트 테스트
    printf("\n=== 구간 업데이트 테스트 ===\n");
    printf("arr[2..6] 모든 값에 +5\n");
    fenwick.update(2, 6, 5);
    
    printf("쿼리 [2, 7]: %d\n", fenwick.query(2, 7)); // (5+5)+(10+5)+(9+5)+(11+5)+(13+5)+(15) = 88
    printf("쿼리 [0, 4]: %d\n", fenwick.query(0, 4)); // 1+3+(5+5)+(10+5)+(9+5) = 43
    printf("쿼리 [5, 9]: %d\n", fenwick.query(5, 9)); // (11+5)+(13+5)+15+17+19 = 85
    printf("쿼리 [0, 9]: %d\n", fenwick.query(0, 9)); // 전체 합 = 128
    
    // 중첩 구간 업데이트 테스트
    printf("\n=== 중첩 구간 업데이트 테스트 ===\n");
    printf("arr[1..5] 모든 값에 +3\n");
    fenwick.update(1, 5, 3);
    
    printf("쿼리 [0, 4]: %d\n", fenwick.query(0, 4)); // 1+(3+3)+(5+5+3)+(10+5+3)+(9+5+3) = 55
    printf("쿼리 [2, 7]: %d\n", fenwick.query(2, 7)); // (5+5+3)+(10+5+3)+(9+5+3)+(11+5+3)+(13+5)+15 = 100
    printf("쿼리 [0, 9]: %d\n", fenwick.query(0, 9)); // 전체 합 = 143
    
    // 개별 요소 값 확인
    printf("\n=== 개별 요소 값 확인 ===\n");
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = %d\n", i, fenwick.pointQuery(i));
    }
    
    return 0;
}