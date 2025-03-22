#include <cstdio>
#include "sqrt_decomp.h"

int main() {
    // 테스트 데이터
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("원본 배열: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
    
    // 구간 합 테스트
    printf("=== 구간 합(RangeSum) 테스트 ===\n");
    SqrtDecomp<RangeSum> sumDecomp(n);
    sumDecomp.build(arr);
    
    printf("쿼리 [2, 7]: %d\n", sumDecomp.query(2, 7)); // 5+7+9+11+13+15 = 60
    printf("쿼리 [0, 4]: %d\n", sumDecomp.query(0, 4)); // 1+3+5+7+9 = 25
    printf("쿼리 [5, 9]: %d\n", sumDecomp.query(5, 9)); // 11+13+15+17+19 = 75
    
    // 값 업데이트
    printf("\n값 업데이트: arr[3] = 10\n");
    sumDecomp.update(3, 10);
    
    printf("쿼리 [2, 7]: %d\n", sumDecomp.query(2, 7)); // 5+10+9+11+13+15 = 63
    printf("쿼리 [0, 4]: %d\n", sumDecomp.query(0, 4)); // 1+3+5+10+9 = 28
    
    // 전체 데이터 재구성 테스트
    int newArr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    printf("\n전체 데이터 재구성 테스트\n");
    sumDecomp.build(newArr);
    
    printf("쿼리 [2, 7]: %d\n", sumDecomp.query(2, 7)); // 6+8+10+12+14+16 = 66
    printf("쿼리 [0, 4]: %d\n", sumDecomp.query(0, 4)); // 2+4+6+8+10 = 30
    
    // 구간 최소값 테스트
    printf("\n=== 구간 최소값(RangeMin) 테스트 ===\n");
    SqrtDecomp<RangeMin> minDecomp(n);
    minDecomp.build(arr);
    minDecomp.update(3, 10); // 업데이트된 배열 사용
    
    printf("쿼리 [2, 7]: %d\n", minDecomp.query(2, 7)); // min(5,10,9,11,13,15) = 5
    printf("쿼리 [0, 4]: %d\n", minDecomp.query(0, 4)); // min(1,3,5,10,9) = 1
    printf("쿼리 [5, 9]: %d\n", minDecomp.query(5, 9)); // min(11,13,15,17,19) = 11
    
    // 구간 최대값 테스트
    printf("\n=== 구간 최대값(RangeMax) 테스트 ===\n");
    SqrtDecomp<RangeMax> maxDecomp(n);
    maxDecomp.build(arr);
    maxDecomp.update(3, 10); // 업데이트된 배열 사용
    
    printf("쿼리 [2, 7]: %d\n", maxDecomp.query(2, 7)); // max(5,10,9,11,13,15) = 15
    printf("쿼리 [0, 4]: %d\n", maxDecomp.query(0, 4)); // max(1,3,5,10,9) = 10
    printf("쿼리 [5, 9]: %d\n", maxDecomp.query(5, 9)); // max(11,13,15,17,19) = 19
    
    return 0;
}