#include <cstdio>
#include <ctime>
#include "common.h"
#include "selection.h"

typedef int (*SelectionFunction)(int[], int, int, int);

int rand(unsigned long long seed) {
    seed = seed * 25214903917ULL + 11ULL;
    return (seed >> 16) & 0x3fffffff;
}

// 배열을 초기화하는 함수
void fillRandom(int arr[], int size, unsigned long long seed) {
    unsigned long long currentSeed = seed;
    for (int i = 0; i < size; i++) {
        arr[i] = rand(currentSeed) % 1000000;
        currentSeed = currentSeed * 25214903917ULL + 11ULL;
    }
}

// 특정 k값에 대한 선택 알고리즘 테스트
void testSelection(SelectionFunction selectionFunc, const char* name,
                   int arr[], int size, int k, int expectedResult) {
    int low = 0;
    int high = size - 1;

    clock_t start = clock();
    int result = selectionFunc(arr, low, high, k);
    clock_t end = clock();
    double duration = 1000.0 * (end - start) / CLOCKS_PER_SEC; // 밀리초로 변환

    printf("%-28s k=%-5d 결과=%-10d 기대값=%-10d 시간=%-15.2f %s\n",
           name, k, result, expectedResult,
           duration, (result == expectedResult) ? "정확함" : "오류");
}

// 다양한 배열 크기와 k값에 대해 선택 알고리즘 벤치마크
void benchmarkSelection(SelectionFunction selectionFunc, const char* name,
                        int sizes[], int sizesCount, int kValues[], int kCount, 
                        unsigned long long seed) {
    for (int i = 0; i < sizesCount; i++) {
        int size = sizes[i];
        
        // 테스트용 배열 생성 및 초기화
        int* arr = new int[size];
        fillRandom(arr, size, seed);
        
        // 기대값 계산을 위한 정렬된 배열 만들기
        int* sortedArr = new int[size];
        for (int j = 0; j < size; j++)
            sortedArr[j] = arr[j];
        
        // 내림차순 정렬 (k번째 큰 값을 구하기 위함)
        for (int m = 0; m < size - 1; m++) {
            for (int n = 0; n < size - m - 1; n++) {
                if (sortedArr[n] < sortedArr[n + 1])
                    swap(sortedArr[n], sortedArr[n + 1]);
            }
        }
        
        printf("배열 크기: %d\n", size);
        printf("------------------------------------------------------------------------------\n");
        
        // 여러 k 값에 대해 테스트
        for (int j = 0; j < kCount; j++) {
            int k = kValues[j];
            if (k <= size) {
                int expectedResult = sortedArr[k - 1];
                testSelection(selectionFunc, name, arr, size, k, expectedResult);
            }
        }
        
        printf("\n");
        
        delete[] arr;
        delete[] sortedArr;
    }
}

// 메인 함수
int main() {
    // int sizes[] = { 100, 1000, 10000 };
    int sizes[] = { 10000 };
    int sizesCount = sizeof(sizes) / sizeof(sizes[0]);
    
    // int kValues[] = { 1, 5, 10, 50, 100 };
    int kValues[] = { 100 };
    int kCount = sizeof(kValues) / sizeof(kValues[0]);
    
    unsigned long long seed = time(NULL);  // 현재 시간 기반 시드 값
    
    // 결과 테이블 헤더
    printf("%-28s %-7s %-12s %-12s %-17s %s\n",
           "알고리즘", "k값", "결과", "기대값", "시간(ms)", "결과 검증");
    printf("==============================================================================\n");
    
    // 선택 알고리즘 벤치마크
    benchmarkSelection(sortAndSelect, "Sort and Select", sizes, sizesCount, kValues, kCount, seed);
    benchmarkSelection(quickSelect, "Quick Select", sizes, sizesCount, kValues, kCount, seed);
    benchmarkSelection(heapSelect, "Heap-based Selection", sizes, sizesCount, kValues, kCount, seed);
    benchmarkSelection(medianOfMediansSelect, "Median of Medians", sizes, sizesCount, kValues, kCount, seed);
    benchmarkSelection(binarySearchSelect, "Binary Search Select", sizes, sizesCount, kValues, kCount, seed);
    benchmarkSelection(countingSelect, "Counting Sort-based", sizes, sizesCount, kValues, kCount, seed);
    benchmarkSelection(partialMergeSelect, "Partial Merge Sort", sizes, sizesCount, kValues, kCount, seed);
    
    return 0;
}