#include <cstdio>
#include "sqrt_decomp_lazy.h"

int main() {
    // 테스트 데이터
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("원본 배열: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
    
    // RangeSum 테스트
    printf("=== 구간 합(RangeSum) 테스트 ===\n");
    SqrtDecompLazy<RangeSum> sumDecomp(n);
    sumDecomp.build(arr);
    
    printf("초기 상태:\n");
    printf("쿼리 [2, 7]: %d\n", sumDecomp.query(2, 7)); // 5+7+9+11+13+15 = 60
    printf("쿼리 [0, 4]: %d\n", sumDecomp.query(0, 4)); // 1+3+5+7+9 = 25
    printf("쿼리 [5, 9]: %d\n", sumDecomp.query(5, 9)); // 11+13+15+17+19 = 75
    
    // 단일 위치 업데이트
    printf("\n단일 위치 업데이트: arr[3] = 10\n");
    sumDecomp.update(3, 10);
    
    printf("쿼리 [2, 7]: %d\n", sumDecomp.query(2, 7)); // 5+10+9+11+13+15 = 63
    printf("쿼리 [0, 4]: %d\n", sumDecomp.query(0, 4)); // 1+3+5+10+9 = 28
    
    // 구간 업데이트
    printf("\n구간 업데이트: arr[2..6] += 5\n");
    sumDecomp.update(2, 6, 5);
    
    printf("쿼리 [2, 7]: %d\n", sumDecomp.query(2, 7)); // (5+5)+(10+5)+(9+5)+(11+5)+(13+5)+(15) = 88
    printf("쿼리 [0, 4]: %d\n", sumDecomp.query(0, 4)); // 1+3+(5+5)+(10+5)+(9+5) = 43
    printf("쿼리 [5, 9]: %d\n", sumDecomp.query(5, 9)); // (11+5)+(13+5)+15+17+19 = 85
    
    // RangeMin 테스트
    printf("\n=== 구간 최소값(RangeMin) 테스트 ===\n");
    SqrtDecompLazy<RangeMin> minDecomp(n);
    minDecomp.build(arr);
    
    printf("초기 상태:\n");
    printf("쿼리 [2, 7]: %d\n", minDecomp.query(2, 7)); // min(5,7,9,11,13,15) = 5
    
    // 단일 위치 업데이트
    printf("\n단일 위치 업데이트: arr[4] = 2\n");
    minDecomp.update(4, 2);
    
    printf("쿼리 [2, 7]: %d\n", minDecomp.query(2, 7)); // min(5,7,2,11,13,15) = 2
    
    // 구간 업데이트
    printf("\n구간 업데이트: arr[1..5] += 3\n");
    minDecomp.update(1, 5, 3);
    
    printf("쿼리 [0, 4]: %d\n", minDecomp.query(0, 4)); // min(1,(3+3),(5+3),(7+3),(2+3)) = 1
    printf("쿼리 [1, 6]: %d\n", minDecomp.query(1, 6)); // min((3+3),(5+3),(7+3),(2+3),(11+3),13) = 5
    
    // RangeMax 테스트
    printf("\n=== 구간 최대값(RangeMax) 테스트 ===\n");
    SqrtDecompLazy<RangeMax> maxDecomp(n);
    maxDecomp.build(arr);
    
    printf("초기 상태:\n");
    printf("쿼리 [2, 7]: %d\n", maxDecomp.query(2, 7)); // max(5,7,9,11,13,15) = 15
    
    // 구간 업데이트
    printf("\n구간 업데이트: arr[3..8] -= 5\n");
    maxDecomp.update(3, 8, -5);
    
    printf("쿼리 [2, 7]: %d\n", maxDecomp.query(2, 7)); // max(5,(7-5),(9-5),(11-5),(13-5),(15-5)) = 10
    printf("쿼리 [0, 4]: %d\n", maxDecomp.query(0, 4)); // max(1,3,5,(7-5),(9-5)) = 5
    printf("쿼리 [5, 9]: %d\n", maxDecomp.query(5, 9)); // max((11-5),(13-5),(15-5),(17-5),19) = 19
    
    return 0;
}