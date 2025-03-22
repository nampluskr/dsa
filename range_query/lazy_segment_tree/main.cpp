#include <cstdio>
#include "segment_tree_lazy.h"

int main() {
    // RangeSum 테스트
    {
        printf("===== RangeSum 테스트 =====\n");
        int arr[] = {1, 2, 3, 4, 5};
        int n = sizeof(arr) / sizeof(arr[0]);
        
        SegmentTreeLazy<RangeSum> sumTree(arr, n);
        
        printf("초기 배열: [1, 2, 3, 4, 5]\n");
        printf("구간 [0, 4] 합: %d\n", sumTree.query(0, 4));  // 15
        printf("구간 [1, 3] 합: %d\n", sumTree.query(1, 3));  // 9
        
        printf("\n구간 [1, 3]에 2 더하기\n");
        sumTree.update(1, 3, 2);
        
        printf("업데이트 후 배열: [1, 4, 5, 6, 5]\n");
        printf("구간 [0, 4] 합: %d\n", sumTree.query(0, 4));  // 21
        printf("구간 [1, 3] 합: %d\n", sumTree.query(1, 3));  // 15
        
        printf("\n구간 [0, 2]에 3 더하기\n");
        sumTree.update(0, 2, 3);
        
        printf("업데이트 후 배열: [4, 7, 8, 6, 5]\n");
        printf("구간 [0, 4] 합: %d\n", sumTree.query(0, 4));  // 30
        printf("구간 [0, 2] 합: %d\n", sumTree.query(0, 2));  // 19
        
        printf("\n음수 업데이트 테스트: 구간 [1, 4]에 -2 더하기\n");
        sumTree.update(1, 4, -2);
        
        printf("업데이트 후 배열: [4, 5, 6, 4, 3]\n");
        printf("구간 [0, 4] 합: %d\n", sumTree.query(0, 4));  // 22
        printf("구간 [1, 4] 합: %d\n", sumTree.query(1, 4));  // 18
    }
    
    // RangeMin 테스트
    {
        printf("\n===== RangeMin 테스트 =====\n");
        int arr[] = {5, 2, 8, 3, 7};
        int n = sizeof(arr) / sizeof(arr[0]);
        
        SegmentTreeLazy<RangeMin> minTree(arr, n);
        
        printf("초기 배열: [5, 2, 8, 3, 7]\n");
        printf("구간 [0, 4] 최솟값: %d\n", minTree.query(0, 4));  // 2
        printf("구간 [2, 4] 최솟값: %d\n", minTree.query(2, 4));  // 3
        
        printf("\n구간 [0, 2]에 1 더하기\n");
        minTree.update(0, 2, 1);
        
        printf("업데이트 후 배열: [6, 3, 9, 3, 7]\n");
        printf("구간 [0, 4] 최솟값: %d\n", minTree.query(0, 4));  // 3
        printf("구간 [0, 2] 최솟값: %d\n", minTree.query(0, 2));  // 3
        
        printf("\n0 값 업데이트 테스트: 구간 [0, 4]에 0 더하기\n");
        minTree.update(0, 4, 0);
        
        printf("업데이트 후 배열: [6, 3, 9, 3, 7] (변화 없음)\n");
        printf("구간 [0, 4] 최솟값: %d\n", minTree.query(0, 4));  // 3
    }
    
    // RangeMax 테스트
    {
        printf("\n===== RangeMax 테스트 =====\n");
        int arr[] = {5, 2, 8, 3, 7};
        int n = sizeof(arr) / sizeof(arr[0]);
        
        SegmentTreeLazy<RangeMax> maxTree(arr, n);
        
        printf("초기 배열: [5, 2, 8, 3, 7]\n");
        printf("구간 [0, 4] 최댓값: %d\n", maxTree.query(0, 4));  // 8
        printf("구간 [0, 1] 최댓값: %d\n", maxTree.query(0, 1));  // 5
        
        printf("\n구간 [3, 4]에 2 더하기\n");
        maxTree.update(3, 4, 2);
        
        printf("업데이트 후 배열: [5, 2, 8, 5, 9]\n");
        printf("구간 [0, 4] 최댓값: %d\n", maxTree.query(0, 4));  // 9
        printf("구간 [2, 4] 최댓값: %d\n", maxTree.query(2, 4));  // 9
        
        printf("\n복합 업데이트 테스트: 구간 [0, 2]에 3 더하기 후 구간 [1, 3]에 -1 더하기\n");
        maxTree.update(0, 2, 3);
        maxTree.update(1, 3, -1);
        
        printf("업데이트 후 배열: [8, 4, 10, 4, 9]\n");
        printf("구간 [0, 4] 최댓값: %d\n", maxTree.query(0, 4));  // 10
        printf("구간 [1, 3] 최댓값: %d\n", maxTree.query(1, 3));  // 10
    }
    
    return 0;
}