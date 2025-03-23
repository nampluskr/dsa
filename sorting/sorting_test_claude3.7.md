# Sorting Test (Claude3.7 Extended)

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <algorithm>

// 퀵 정렬
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int left, int right) {
    // 피벗으로 중간값 선택 (최악의 경우 방지)
    int mid = left + (right - left) / 2;
    int pivot = arr[mid];
    
    // 피벗을 맨 오른쪽으로 이동
    swap(arr[mid], arr[right]);
    
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

void quickSort(int arr[], int left, int right) {
    if (left < right) {
        int pi = partition(arr, left, right);
        quickSort(arr, left, pi - 1);
        quickSort(arr, pi + 1, right);
    }
}

// 병합 정렬
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int* L = new int[n1];
    int* R = new int[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// 힙 정렬
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int left, int right) {
    int n = right - left + 1;
    int* heapArr = arr + left;
    
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(heapArr, n, i);
    
    for (int i = n - 1; i > 0; i--) {
        swap(heapArr[0], heapArr[i]);
        heapify(heapArr, i, 0);
    }
}

// 삽입 정렬
void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 계수 정렬
void countingSort(int arr[], int left, int right) {
    // 최대값 찾기
    int max_val = arr[left];
    for (int i = left + 1; i <= right; i++) {
        if (arr[i] > max_val)
            max_val = arr[i];
    }
    
    // 최소값 찾기
    int min_val = arr[left];
    for (int i = left + 1; i <= right; i++) {
        if (arr[i] < min_val)
            min_val = min_val;
    }
    
    int range = max_val - min_val + 1;
    
    // 계수 배열 생성 및 초기화
    int* count = new int[range]();
    
    // 각 요소 개수 세기
    for (int i = left; i <= right; i++) {
        count[arr[i] - min_val]++;
    }
    
    // 결과 배열에 정렬된 요소 복원
    int k = left;
    for (int i = 0; i < range; i++) {
        while (count[i] > 0) {
            arr[k++] = i + min_val;
            count[i]--;
        }
    }
    
    delete[] count;
}

// 기수 정렬
void countSortForRadix(int arr[], int n, int exp) {
    int* output = new int[n];
    int count[10] = {0};
    
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
    
    delete[] output;
}

void radixSort(int arr[], int left, int right) {
    int n = right - left + 1;
    int* radixArr = arr + left;
    
    int max_val = radixArr[0];
    for (int i = 1; i < n; i++) {
        if (radixArr[i] > max_val)
            max_val = radixArr[i];
    }
    
    for (int exp = 1; max_val / exp > 0; exp *= 10)
        countSortForRadix(radixArr, n, exp);
}

// 인트로 정렬
void introSortUtil(int arr[], int left, int right, int depthLimit) {
    int n = right - left + 1;
    
    if (n <= 16) {
        insertionSort(arr, left, right);
        return;
    }
    
    if (depthLimit == 0) {
        heapSort(arr, left, right);
        return;
    }
    
    int pivot = partition(arr, left, right);
    
    introSortUtil(arr, left, pivot - 1, depthLimit - 1);
    introSortUtil(arr, pivot + 1, right, depthLimit - 1);
}

void introSort(int arr[], int left, int right) {
    int n = right - left + 1;
    int depthLimit = 2 * log2(n);
    
    introSortUtil(arr, left, right, depthLimit);
}

// 간단한 선형 합동 난수 생성기 구현
struct RandomGenerator {
    unsigned long long seed;
    
    RandomGenerator(unsigned long long initialSeed = 12345) {
        seed = initialSeed;
    }
    
    // 간단한 선형 합동법(Linear Congruential Generator)
    unsigned long long next() {
        seed = (seed * 6364136223846793005ULL + 1442695040888963407ULL) % ULLONG_MAX;
        return seed;
    }
    
    // 0 ~ (max-1) 범위의 랜덤 정수 생성
    int nextInt(int max) {
        return next() % max;
    }
    
    // min ~ max 범위의 랜덤 정수 생성
    int nextIntRange(int min, int max) {
        return min + next() % (max - min + 1);
    }
};

// time.h를 사용한 타이머 구현
struct Timer {
    clock_t startTime;
    
    void start() {
        startTime = clock();
    }
    
    double elapsedMilliseconds() {
        clock_t endTime = clock();
        return (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
    }
};

// 배열 복사
void copyArray(int source[], int destination[], int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}

// 배열이 정렬되었는지 확인
bool isSorted(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i-1]) {
            return false;
        }
    }
    return true;
}

// 배열의 일부분 출력 (디버깅용)
void printArray(int arr[], int size, int maxPrint = 10) {
    int printSize = size < maxPrint ? size : maxPrint;
    for (int i = 0; i < printSize; i++) {
        printf("%d ", arr[i]);
    }
    if (size > maxPrint) {
        printf("... (%d more elements)", size - maxPrint);
    }
    printf("\n");
}

int main() {
    // 난수 생성기 초기화 - time.h 사용
    RandomGenerator rng((unsigned long long)time(NULL));
    
    // 테스트할 배열 크기
    const int sizes[] = {10000, 100000, 1000000};
    const int numSizes = 3;
    
    // 테스트 반복 횟수 (더 안정적인 결과를 위해)
    const int numTrials = 3;
    
    // 알고리즘 이름
    const char* algorithmNames[] = {
        "Quick Sort", "Merge Sort", "Heap Sort", 
        "Insertion Sort", "Counting Sort", "Radix Sort", "Intro Sort"
    };
    
    printf("정렬 알고리즘 성능 비교 (단위: 밀리초)\n");
    printf("----------------------------------------\n");
    
    // 헤더 출력
    printf("%-16s", "Algorithm");
    for (int s = 0; s < numSizes; s++) {
        printf("%-12d", sizes[s]);
    }
    printf("\n");
    printf("----------------------------------------\n");
    
    // 각 알고리즘에 대해 테스트
    for (int alg = 0; alg < 7; alg++) {
        printf("%-16s", algorithmNames[alg]);
        
        // 각 배열 크기에 대해 테스트
        for (int s = 0; s < numSizes; s++) {
            int size = sizes[s];
            
            // 특정 조건에서 테스트 건너뛰기
            if ((alg == 0 && size > 100000) ||   // 퀵 정렬: 큰 배열에서 스택 오버플로우 위험
                (alg == 3 && size > 10000)) {    // 삽입 정렬: 큰 배열에서 너무 느림
                printf("%-12s", "N/A");
                continue;
            }
            
            // 여러 번 시도하여 평균 측정
            double totalTime = 0.0;
            
            for (int trial = 0; trial < numTrials; trial++) {
                // 원본 배열 생성
                int* originalArray = new int[size];
                
                // 랜덤 값으로 배열 채우기
                for (int i = 0; i < size; i++) {
                    originalArray[i] = rng.nextInt(1000000);
                }
                
                // 테스트용 배열 복사
                int* testArray = new int[size];
                copyArray(originalArray, testArray, size);
                
                // 타이머 시작
                Timer timer;
                timer.start();
                
                // 알고리즘 실행
                switch (alg) {
                    case 0: quickSort(testArray, 0, size - 1); break;
                    case 1: mergeSort(testArray, 0, size - 1); break;
                    case 2: heapSort(testArray, 0, size - 1); break;
                    case 3: insertionSort(testArray, 0, size - 1); break;
                    case 4: countingSort(testArray, 0, size - 1); break;
                    case 5: radixSort(testArray, 0, size - 1); break;
                    case 6: introSort(testArray, 0, size - 1); break;
                }
                
                // 경과 시간 측정
                double elapsedTime = timer.elapsedMilliseconds();
                totalTime += elapsedTime;
                
                // 정렬 확인
                if (!isSorted(testArray, size)) {
                    printf("정렬 실패: %s\n", algorithmNames[alg]);
                    printArray(testArray, size, 20); // 문제 발생 시 일부 출력
                }
                
                // 메모리 해제
                delete[] originalArray;
                delete[] testArray;
            }
            
            // 평균 시간 출력
            double avgTime = totalTime / numTrials;
            printf("%-12.2f", avgTime);
        }
        printf("\n");
    }
    
    // 추가 테스트: 특별한 케이스들
    printf("\n특별한 케이스에서의 성능 (크기: 100000)\n");
    printf("----------------------------------------\n");
    
    const int specialTestSize = 100000;
    const char* testCaseNames[] = {
        "거의 정렬됨", "역순 정렬", "많은 중복", "정렬됨"
    };
    const int numTestCases = 4;
    
    // 테스트 케이스별 헤더
    printf("%-16s", "Algorithm");
    for (int t = 0; t < numTestCases; t++) {
        printf("%-12s", testCaseNames[t]);
    }
    printf("\n");
    printf("----------------------------------------\n");
    
    // 각 알고리즘에 대해 특별 케이스 테스트
    for (int alg = 0; alg < 7; alg++) {
        // 삽입 정렬은 큰 배열에서 건너뛰기
        if (alg == 3) continue;
        
        printf("%-16s", algorithmNames[alg]);
        
        // 각 테스트 케이스에 대해
        for (int testCase = 0; testCase < numTestCases; testCase++) {
            // 원본 배열 생성
            int* originalArray = new int[specialTestSize];
            
            // 테스트 케이스별 배열 초기화
            switch (testCase) {
                case 0: // 거의 정렬됨
                    for (int i = 0; i < specialTestSize; i++) {
                        originalArray[i] = i;
                    }
                    // 5%만 무작위 교환
                    for (int i = 0; i < specialTestSize * 0.05; i++) {
                        int idx1 = rng.nextInt(specialTestSize);
                        int idx2 = rng.nextInt(specialTestSize);
                        int temp = originalArray[idx1];
                        originalArray[idx1] = originalArray[idx2];
                        originalArray[idx2] = temp;
                    }
                    break;
                    
                case 1: // 역순 정렬
                    for (int i = 0; i < specialTestSize; i++) {
                        originalArray[i] = specialTestSize - i - 1;
                    }
                    break;
                    
                case 2: // 많은 중복
                    for (int i = 0; i < specialTestSize; i++) {
                        originalArray[i] = rng.nextInt(100); // 0-99 사이 값만 사용
                    }
                    break;
                    
                case 3: // 이미 정렬됨
                    for (int i = 0; i < specialTestSize; i++) {
                        originalArray[i] = i;
                    }
                    break;
            }
            
            // 테스트용 배열 복사
            int* testArray = new int[specialTestSize];
            copyArray(originalArray, testArray, specialTestSize);
            
            // 타이머 시작
            Timer timer;
            timer.start();
            
            // 알고리즘 실행
            switch (alg) {
                case 0: quickSort(testArray, 0, specialTestSize - 1); break;
                case 1: mergeSort(testArray, 0, specialTestSize - 1); break;
                case 2: heapSort(testArray, 0, specialTestSize - 1); break;
                // 삽입 정렬은 건너뜀
                case 4: countingSort(testArray, 0, specialTestSize - 1); break;
                case 5: radixSort(testArray, 0, specialTestSize - 1); break;
                case 6: introSort(testArray, 0, specialTestSize - 1); break;
            }
            
            // 경과 시간 측정
            double elapsedTime = timer.elapsedMilliseconds();
            printf("%-12.2f", elapsedTime);
            
            // 메모리 해제
            delete[] originalArray;
            delete[] testArray;
        }
        printf("\n");
    }
    
    return 0;
}
```