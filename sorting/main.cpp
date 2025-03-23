#include <cstdio>
#include <ctime>
#include "quadratic_sort.h"
#include "log_linear_sort.h"
#include "linear_sort.h"
#include "common.h"

int rand(unsigned long long seed) {
    seed = seed * 25214903917ULL + 11ULL;
    return (seed >> 16) & 0x3fffffff;
}

typedef void (*SortFunction)(int[], int, int);

// 배열이 정렬되었는지 확인하는 함수
bool isSorted(int arr[], int low, int high) {
    for (int i = low; i < high; i++)
        if (arr[i] > arr[i + 1])
            return false;
    return true;
}

// 배열을 초기화하는 함수들
void fillRandom(int arr[], int size, unsigned long long seed) {
    unsigned long long currentSeed = seed;
    for (int i = 0; i < size; i++) {
        arr[i] = rand(currentSeed) % 1000000;
        currentSeed = currentSeed * 25214903917ULL + 11ULL;
    }
}

void fillSorted(int arr[], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = i;
}

void fillReversed(int arr[], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = size - i - 1;
}

void fillMostlySorted(int arr[], int size, unsigned long long seed) {
    fillSorted(arr, size);
    unsigned long long currentSeed = seed;
    // 10% 의 요소만 랜덤하게 섞음
    int swaps = size / 10;
    for (int i = 0; i < swaps; i++) {
        int idx1 = rand(currentSeed) % size;
        currentSeed = currentSeed * 25214903917ULL + 11ULL;
        int idx2 = rand(currentSeed) % size;
        currentSeed = currentSeed * 25214903917ULL + 11ULL;
        swap(arr[idx1], arr[idx2]);
    }
}

// 특정 사이즈와 분포에 대한 정렬 알고리즘 테스트
void testSort(SortFunction sortFunc, const char* name,
              int arr[], int size, const char* distribution) {
    int low = 0;
    int high = size - 1;

    clock_t start = clock();
    sortFunc(arr, low, high);
    clock_t end = clock();
    double duration = 1000.0 * (end - start) / CLOCKS_PER_SEC; // 밀리초로 변환

    printf("%-20s %-15s %-15d %-15.2f %s\n",
           name, distribution, size, duration,
           isSorted(arr, low, high) ? "정렬됨" : "정렬 실패");
}

// 다양한 배열 크기와 분포에 대해 정렬 알고리즘 벤치마크
void benchmarkSort(SortFunction sortFunc, const char* name,
                   int sizes[], int sizesCount, unsigned long long seed) {

                    for (int i = 0; i < sizesCount; i++) {
        int size = sizes[i];
        // 각 배열 크기별로 4가지 다른 분포에 대해 테스트
        int* arr = new int[size];

        // 1. 랜덤 배열
        fillRandom(arr, size, seed);
        testSort(sortFunc, name, arr, size, "랜덤");

        // // 2. 이미 정렬된 배열
        // fillSorted(arr, size);
        // testSort(sortFunc, name, arr, size, "정렬됨");

        // // 3. 역순 정렬된 배열
        // fillReversed(arr, size);
        // testSort(sortFunc, name, arr, size, "역순");

        // // 4. 대부분 정렬된 배열
        // fillMostlySorted(arr, size, seed);
        // testSort(sortFunc, name, arr, size, "대부분 정렬됨");

        delete[] arr;
    }
}

// 메인 함수
int main() {
    // int sizes[] = { 1000, 10000, 100000 };
    int sizes[] = { 1000000 };
    int sizesCount = sizeof(sizes) / sizeof(sizes[0]);
    unsigned long long seed = time(NULL); // 현재 시간 기반 시드 값

    // 결과 테이블 헤더
    printf("%-20s %-15s %-15s %-15s %s\n",
           "알고리즘", "분포", "크기", "시간(ms)", "결과");
    printf("----------------------------------------------------------------------\n");

    // 정렬 알고리즘 벤치마크
    // benchmarkSort(bubbleSort, "BubbleSort", sizes, sizesCount, seed);
    // benchmarkSort(selectionSort, "SelectionSort", sizes, sizesCount, seed);
    // benchmarkSort(insertionSort, "InsertionSort", sizes, sizesCount, seed);
    benchmarkSort(combSort, "CombSort", sizes, sizesCount, seed);
    // benchmarkSort(cocktailSort, "CocktailSort", sizes, sizesCount, seed);
    // benchmarkSort(gnomeSort, "GnomeSort", sizes, sizesCount, seed);
    // benchmarkSort(cycleSort, "CycleSort", sizes, sizesCount, seed);
    // benchmarkSort(oddEvenSort, "OddEvenSort", sizes, sizesCount, seed);
    printf("\n");

    // sizes[0] = 100000;
    benchmarkSort(quickSortLomuto, "QuickSort(L)", sizes, sizesCount, seed);
    benchmarkSort(quickSortHoare, "QuickSort(H)", sizes, sizesCount, seed);
    benchmarkSort(mergeSort, "MergeSort", sizes, sizesCount, seed);
    benchmarkSort(heapSort, "HeapSort", sizes, sizesCount, seed);
    printf("\n");

    // benchmarkSort(smoothSort, "SmoothSort", sizes, sizesCount, seed);
    benchmarkSort(blockMergeSort, "BlockMergeSort", sizes, sizesCount, seed);
    // benchmarkSort(librarySort, "LibrarySort", sizes, sizesCount, seed);
    // benchmarkSort(tournamentSort, "TournamentSort", sizes, sizesCount, seed);
    benchmarkSort(patchworkSort, "PatchworkSort", sizes, sizesCount, seed);
    printf("\n");

    benchmarkSort(shellSort, "ShellSort", sizes, sizesCount, seed);
    benchmarkSort(timSort, "TimSort", sizes, sizesCount, seed);
    benchmarkSort(introSort, "IntroSort", sizes, sizesCount, seed);
    printf("\n");

    benchmarkSort(countingSort, "CountingSort", sizes, sizesCount, seed);
    benchmarkSort(radixSort, "RadixSort", sizes, sizesCount, seed);
    benchmarkSort(bucketSort, "BucketSort", sizes, sizesCount, seed);
    benchmarkSort(pigeonholeSort, "PigeonHoleSort", sizes, sizesCount, seed);
    benchmarkSort(flashSort, "FlashSort", sizes, sizesCount, seed);
    benchmarkSort(distributionSort, "DistributionSort", sizes, sizesCount, seed);
    printf("\n");

    return 0;
}

void shellSort(int arr[], int low, int high);
void timSort(int arr[], int low, int high);
void introSort(int arr[], int low, int high);