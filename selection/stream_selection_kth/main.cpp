#include <cstdio>
#include <ctime>
#include <cmath>
#include "common.h"
#include "stream_selection.h"

typedef int (*StreamSelectionFunction)(int[], int, int);
typedef int (*SlidingWindowFunction)(int[], int, int, int);

int rand(unsigned long long seed) {
    seed = seed * 25214903917ULL + 11ULL;
    return (seed >> 16) & 0x3fffffff;
}

// 스트림 데이터 생성 함수
void generateStream(int stream[], int size, unsigned long long seed, int dataType) {
    unsigned long long currentSeed = seed;
    
    if (dataType == 0) {  // 무작위 데이터
        for (int i = 0; i < size; i++) {
            stream[i] = rand(currentSeed) % 1000;
            currentSeed = currentSeed * 25214903917ULL + 11ULL;
        }
    } 
    else if (dataType == 1) {  // 반복 패턴이 있는 데이터
        int patterns[] = {10, 30, 50, 70, 90};
        int patternCount = 5;
        
        for (int i = 0; i < size; i++) {
            int noise = rand(currentSeed) % 10;
            currentSeed = currentSeed * 25214903917ULL + 11ULL;
            stream[i] = patterns[i % patternCount] + noise;
        }
    }
    else if (dataType == 2) {  // 주기적으로 급증하는 데이터
        for (int i = 0; i < size; i++) {
            int base = rand(currentSeed) % 100;
            currentSeed = currentSeed * 25214903917ULL + 11ULL;
            
            // 주기적으로 급증하는 값
            if (i % 100 < 10) {
                stream[i] = base + 500;  // 급증
            } else {
                stream[i] = base;  // 일반 값
            }
        }
    }
}

// 배열 복사 함수
void copyArray(int src[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

// 정렬 기반으로 k번째 큰 값 구하기 (참조 결과)
int findKthLargest(int arr[], int size, int k) {
    // 배열 복사
    int* temp = new int[size];
    for (int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }
    
    // 내림차순 정렬
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (temp[j] < temp[j + 1]) {
                swap(temp[j], temp[j + 1]);
            }
        }
    }
    
    // k번째 큰 값 찾기
    int result = temp[k - 1];
    
    delete[] temp;
    return result;
}

// 스트리밍 알고리즘 테스트 함수
void testStreamSelectionAlgorithm(StreamSelectionFunction func, const char* name,
                                int stream[], int streamSize, int k, int expectedResult) {
    clock_t start = clock();
    int result = func(stream, streamSize, k);
    clock_t end = clock();
    double duration = 1000.0 * (end - start) / CLOCKS_PER_SEC;  // 밀리초 변환
    
    printf("%-28s k=%-5d 결과=%-10d 기대값=%-10d 시간=%-15.2f %s\n",
           name, k, result, expectedResult,
           duration, (result == expectedResult) ? "정확함" : "근사값");
}

// 슬라이딩 윈도우 알고리즘 테스트 함수
void testSlidingWindowAlgorithm(SlidingWindowFunction func, const char* name,
                              int stream[], int streamSize, int k, int windowSize, int expectedResult) {
    clock_t start = clock();
    int result = func(stream, streamSize, k, windowSize);
    clock_t end = clock();
    double duration = 1000.0 * (end - start) / CLOCKS_PER_SEC;  // 밀리초 변환
    
    printf("%-28s k=%-5d w=%-5d 결과=%-10d 기대값=%-10d 시간=%-15.2f %s\n",
           name, k, windowSize, result, expectedResult,
           duration, (result == expectedResult) ? "정확함" : "근사값");
}

// 메인 함수
int main() {
    // int streamSizes[] = { 100, 1000, 10000 };
    int streamSizes[] = { 10000 };
    int streamSizesCount = sizeof(streamSizes) / sizeof(streamSizes[0]);
    
    // int kValues[] = { 1, 5, 10, 50, 100 };
    int kValues[] = { 50 };
    int kCount = sizeof(kValues) / sizeof(kValues[0]);
    
    // int windowSizes[] = { 50, 200, 500 };
    int windowSizes[] = { 100 };
    int windowCount = sizeof(windowSizes) / sizeof(windowSizes[0]);
    
    // int dataTypes[] = { 0, 1, 2 };  // 0: 무작위, 1: 반복 패턴, 2: 주기적 급증
    int dataTypes[] = { 0 };  // 0: 무작위, 1: 반복 패턴, 2: 주기적 급증
    const char* dataTypeNames[] = { "무작위 데이터", "반복 패턴 데이터", "주기적 급증 데이터" };
    int dataTypeCount = sizeof(dataTypes) / sizeof(dataTypes[0]);
    
    unsigned long long seed = time(NULL);
    
    // 결과 테이블 헤더
    printf("==============================================================================\n");
    printf("스트리밍 데이터에서 k번째 큰 원소 선택 알고리즘 비교\n");
    printf("==============================================================================\n");
    
    for (int d = 0; d < dataTypeCount; d++) {
        printf("\n데이터 유형: %s\n", dataTypeNames[d]);
        printf("------------------------------------------------------------------------------\n");
        
        for (int i = 0; i < streamSizesCount; i++) {
            int streamSize = streamSizes[i];
            printf("\n[스트림 크기: %d]\n", streamSize);
            printf("------------------------------------------------------------------------------\n");
            
            // 스트림 데이터 생성
            int* stream = new int[streamSize];
            generateStream(stream, streamSize, seed + i, dataTypes[d]);
            
            // 각 k값에 대해 테스트
            for (int j = 0; j < kCount; j++) {
                int k = kValues[j];
                if (k <= streamSize) {
                    // 정렬 기반으로 참조 결과 계산
                    int expectedResult = findKthLargest(stream, streamSize, k);
                    
                    printf("\nk = %d, 기대값 = %d\n", k, expectedResult);
                    printf("------------------------------------------------------------------------------\n");
                    
                    // 각 알고리즘 테스트
                    testStreamSelectionAlgorithm(boundedPQSelect, 
                        "Bounded PQ", stream, streamSize, k, expectedResult);
                    
                    testStreamSelectionAlgorithm(reservoirSamplingSelect, 
                        "Reservoir Sampling", stream, streamSize, k, expectedResult);
                    
                    testStreamSelectionAlgorithm(countMinSketchSelect, 
                        "Count-Min Sketch", stream, streamSize, k, expectedResult);
                    
                    testStreamSelectionAlgorithm(spaceSavingSelect, 
                        "Space Saving", stream, streamSize, k, expectedResult);
                    
                    testStreamSelectionAlgorithm(lossyCountingSelect, 
                        "Lossy Counting", stream, streamSize, k, expectedResult);
                    
                    // 슬라이딩 윈도우는 윈도우 크기별로 테스트
                    printf("\n[슬라이딩 윈도우 (다양한 윈도우 크기)]\n");
                    for (int w = 0; w < windowCount; w++) {
                        int windowSize = windowSizes[w];
                        if (windowSize <= streamSize) {
                            // 윈도우 내 참조 결과 계산
                            int* windowData = new int[windowSize];
                            int windowStart = streamSize - windowSize;
                            for (int m = 0; m < windowSize; m++) {
                                windowData[m] = stream[windowStart + m];
                            }
                            int windowExpectedResult = findKthLargest(windowData, windowSize, k);
                            
                            testSlidingWindowAlgorithm(slidingWindowSelect, 
                                "Sliding Window", stream, streamSize, k, windowSize, windowExpectedResult);
                            
                            delete[] windowData;
                        }
                    }
                    
                    testStreamSelectionAlgorithm(expHistSelect, 
                        "Exponential Histogram", stream, streamSize, k, expectedResult);
                    
                    printf("\n");
                }
            }
            
            delete[] stream;
        }
    }
    
    return 0;
}