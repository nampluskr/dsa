#include <cstdio>
#include "segment_tree.h"

int main()
{
    int arr[] = {1, 3, 2, 7, 9, 11, 8, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("원본 배열: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n\n");
    
    SegmentTree<RangeMin> minTree(arr, n);
    SegmentTree<RangeMax> maxTree(arr, n);
    SegmentTree<RangeSum> sumTree(arr, n);
    
    printf("=== 구간 쿼리 테스트 ===\n");
    int l = 2, r = 5;
    printf("구간 [%d, %d] 최소값: %d\n", l, r, minTree.query(l, r));
    printf("구간 [%d, %d] 최대값: %d\n", l, r, maxTree.query(l, r));
    printf("구간 [%d, %d] 구간합: %d\n", l, r, sumTree.query(l, r));
    printf("\n");
    
    int idx = 3, new_val = 10;
    printf("=== 값 업데이트 테스트 ===\n");
    printf("arr[%d]의 값을 %d에서 %d로 변경\n", idx, arr[idx], new_val);
    
    minTree.update(idx, new_val);
    maxTree.update(idx, new_val);
    sumTree.update(idx, new_val);
    
    printf("\n");
    printf("구간 [%d, %d] 최소값: %d\n", l, r, minTree.query(l, r));
    printf("구간 [%d, %d] 최대값: %d\n", l, r, maxTree.query(l, r));
    printf("구간 [%d, %d] 구간합: %d\n", l, r, sumTree.query(l, r));
    
    return 0;
}