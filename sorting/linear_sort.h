#pragma once
#include <cmath>
#include "common.h"


void countingSort(int arr[], int low, int high);
void radixSort(int arr[], int low, int high);

void bucketSort(int arr[], int low, int high);
void pigeonholeSort(int arr[], int low, int high);
void flashSort(int arr[], int low, int high);
void distributionSort(int arr[], int low, int high);

//////////////////////////////////////////////////////////////////////
// 계수 정렬 함수
void countingSort(int arr[], int low, int high) {
    // 배열에서 최대값 찾기
    int max = arr[low];
    for (int i = low + 1; i <= high; i++)
        if (arr[i] > max)
            max = arr[i];

    // 배열에서 최소값 찾기
    int min = arr[low];
    for (int i = low + 1; i <= high; i++)
        if (arr[i] < min)
            min = arr[i];

    // 범위 계산 및 카운트 배열 생성
    int range = max - min + 1;
    int* count = new int[range]();  // 0으로 초기화
    int* output = new int[high - low + 1];

    // 요소 발생 횟수 세기
    for (int i = low; i <= high; i++)
        count[arr[i] - min]++;

    // 카운트 배열을 누적합으로 변환 (안정 정렬을 위해)
    for (int i = 1; i < range; i++)
        count[i] += count[i - 1];

    // 안정 정렬을 위해 뒤에서부터 순회
    for (int i = high; i >= low; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    // 정렬된 결과를 원래 배열에 복사
    for (int i = 0; i < high - low + 1; i++)
        arr[low + i] = output[i];

    // 메모리 해제
    delete[] count;
    delete[] output;
}

// 특정 자릿수를 기준으로 정렬하는 계수 정렬
void countingSortForRadix(int arr[], int low, int high, int exp) {
    int n = high - low + 1;
    int* output = new int[n];
    int count[10] = {0};

    // 현재 자릿수에 따라 요소의 발생 횟수 세기
    for (int i = low; i <= high; i++)
        count[(arr[i] / exp) % 10]++;

    // 누적합으로 변환
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // 안정 정렬을 위해 뒤에서부터 순회
    for (int i = high; i >= low; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // 정렬된 결과를 원래 배열에 복사
    for (int i = 0; i < n; i++)
        arr[low + i] = output[i];

    delete[] output;
}

//////////////////////////////////////////////////////////////////////
// 기수 정렬 함수
void radixSort(int arr[], int low, int high) {
    // 음수 처리 검사
    bool hasNegative = false;
    for (int i = low; i <= high; i++) {
        if (arr[i] < 0) {
            hasNegative = true;
            break;
        }
    }

    // 음수가 있을 경우 처리 (간단한 방법: 모든 값을 양수로 변환)
    int offset = 0;
    if (hasNegative) {
        int min = arr[low];
        for (int i = low + 1; i <= high; i++)
            if (arr[i] < min)
                min = arr[i];

        offset = -min;
        for (int i = low; i <= high; i++)
            arr[i] += offset;
    }

    // 최대값 찾기
    int max = arr[low];
    for (int i = low + 1; i <= high; i++)
        if (arr[i] > max)
            max = arr[i];

    // 각 자릿수에 대해 계수 정렬 수행
    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSortForRadix(arr, low, high, exp);

    // 오프셋 적용한 경우 원래 값으로 복원
    if (hasNegative) {
        for (int i = low; i <= high; i++)
            arr[i] -= offset;
    }
}

//////////////////////////////////////////////////////////////////////
// 삽입 정렬 (버킷 내 정렬용)
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 버킷 정렬 함수
void bucketSort(int arr[], int low, int high) {
    // 배열 크기
    int n = high - low + 1;

    // 최대값과 최소값 찾기
    int maxVal = arr[low], minVal = arr[low];
    for (int i = low + 1; i <= high; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
        if (arr[i] < minVal) minVal = arr[i];
    }

    // 버킷 개수 결정 (여기서는 배열 크기의 제곱근으로 설정)
    int bucketCount = sqrt(n) + 1;

    // 범위 계산
    double range = (maxVal - minVal) / (double)bucketCount;
    if (range < 1) range = 1;  // 범위가 1보다 작으면 1로 설정

    // 버킷 생성 (동적 배열의 포인터 배열)
    struct Bucket {
        int* items;
        int count;
    };

    Bucket* buckets = new Bucket[bucketCount];

    // 버킷 초기화
    for (int i = 0; i < bucketCount; i++) {
        buckets[i].items = new int[n];  // 최악의 경우 모든 요소가 한 버킷에 들어갈 수 있음
        buckets[i].count = 0;
    }

    // 요소들을 적절한 버킷에 분배
    for (int i = low; i <= high; i++) {
        int bucketIndex = (int)((arr[i] - minVal) / range);

        // 마지막 요소가 정확히 마지막 버킷에 들어가도록 조정
        if (bucketIndex >= bucketCount) bucketIndex = bucketCount - 1;

        buckets[bucketIndex].items[buckets[bucketIndex].count++] = arr[i];
    }

    // 각 버킷 정렬
    for (int i = 0; i < bucketCount; i++)
        if (buckets[i].count > 0)
            insertionSort(buckets[i].items, buckets[i].count);

    // 정렬된 버킷의 요소들을 원래 배열에 복사
    int index = low;
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 0; j < buckets[i].count; j++)
            arr[index++] = buckets[i].items[j];
    }

    // 메모리 해제
    for (int i = 0; i < bucketCount; i++)
        delete[] buckets[i].items;
    delete[] buckets;
}

//////////////////////////////////////////////////////////////////////
// 피젼홀 정렬 함수
void pigeonholeSort(int arr[], int low, int high) {
    // 배열에서 최대값과 최소값 찾기
    int max = arr[low], min = arr[low];
    for (int i = low + 1; i <= high; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    // 필요한 홀(pigeonhole)의 개수 계산
    int range = max - min + 1;

    // 각 홀을 저장할 동적 배열 선언
    int* holes = new int[range]();  // 0으로 초기화

    // 요소를 적절한 홀에 배치
    for (int i = low; i <= high; i++)
        holes[arr[i] - min]++;

    // 홀에서 값을 가져와 원래 배열에 정렬된 순서로 저장
    int index = low;
    for (int i = 0; i < range; i++)
        while (holes[i]--)
            arr[index++] = i + min;

    // 메모리 해제
    delete[] holes;
}

//////////////////////////////////////////////////////////////////////
// 수정된 플래시 정렬 함수
void flashSort(int arr[], int low, int high) {
    int n = high - low + 1;
    if (n <= 1) return;
    
    // 최소값과 최대값 찾기
    int min = arr[low], max = arr[low];
    int maxIndex = low;
    
    for (int i = low + 1; i <= high; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) {
            max = arr[i];
            maxIndex = i;
        }
    }
    
    if (max == min) return;  // 모든 요소가 동일하면 정렬 필요 없음
    
    // 클래스 개수 계산 (보통 0.45n이 최적)
    int m = (int)(0.45 * n);
    if (m <= 2) m = 2;  // 최소 2개의 클래스 보장
    
    // 클래스 배열 초기화
    int* L = new int[m]();
    
    // 각 요소의 클래스 계산 및 카운팅
    const double c = (double)(m - 1) / (max - min);
    for (int i = low; i <= high; i++) {
        int k = (int)(c * (arr[i] - min));
        if (k >= m) k = m - 1; // 인덱스 경계 확인
        L[k]++;
    }
    
    // 누적합 계산
    for (int i = 1; i < m; i++)
        L[i] += L[i - 1];
    
    // 첫 번째 위치에 최대값 배치
    swap(arr[low], arr[maxIndex]);
    
    // 사이클 소트 방식으로 요소 재배치
    int move = 0;      // 이동된 요소 수
    int j = 0;         // 현재 인덱스
    
    // 단순화된 구현 - 계수 정렬 접근법 사용
    int* output = new int[n];
    int* count = new int[m];
    
    // count 배열 복사
    for (int i = 0; i < m; i++)
        count[i] = L[i];
    
    // 위치 계산 및 요소 배치
    for (int i = 0; i < n; i++) {
        int k = (int)(c * (arr[low + i] - min));
        if (k >= m) k = m - 1; // 인덱스 경계 확인
        output[--count[k]] = arr[low + i];
    }
    
    // 결과 복사
    for (int i = 0; i < n; i++)
        arr[low + i] = output[i];
    
    // 작은 부분 정렬 불일치 보정을 위한 삽입 정렬
    for (int i = low + 1; i <= high; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
    
    // 메모리 해제
    delete[] L;
    delete[] count;
    delete[] output;
}

//////////////////////////////////////////////////////////////////////
// 파티션 함수 (Lomuto 파티션 방식)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // 피벗으로 마지막 요소 선택
    int i = low - 1;        // 피벗보다 작은 요소들의 경계
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]);  // 피벗을 올바른 위치로 이동
    return i + 1;  // 피벗의 최종 위치 반환
}

void distributionSort(int arr[], int low, int high) {
    int n = high - low + 1;
    
    // 작은 배열은 삽입 정렬 사용
    if (n <= 32) {
        for (int i = low + 1; i <= high; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= low && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return;
    }
    
    // 최소값과 최대값 찾기
    int min_val = arr[low];
    int max_val = arr[low];
    for (int i = low + 1; i <= high; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }
    
    // 범위 계산
    int range = max_val - min_val + 1;
    
    // 데이터 분포 특성에 따라 정렬 방법 선택
    if (range <= n * 2) {
        // 범위가 작을 때는 계수 정렬 사용
        int* count = new int[range]();
        
        // 각 값의 빈도 계산
        for (int i = low; i <= high; i++) {
            count[arr[i] - min_val]++;
        }
        
        // 계수 배열에서 원래 배열로 복원
        int index = low;
        for (int i = 0; i < range; i++) {
            while (count[i]-- > 0) {
                arr[index++] = i + min_val;
            }
        }
        
        delete[] count;
    } 
    else if (range > n * n) {
        // 범위가 매우 클 때는 퀵 정렬 사용
        // (분포 정렬이 효율적이지 않은 경우)
        int pivot = partition(arr, low, high);
        distributionSort(arr, low, pivot);
        distributionSort(arr, pivot + 1, high);
    } 
    else {
        // 그 외에는 버킷 정렬 사용
        int bucket_count = sqrt(n) + 1;
        
        // 버킷 생성 및 초기화
        struct Bucket {
            int* values;
            int count;
        };
        
        Bucket* buckets = new Bucket[bucket_count];
        for (int i = 0; i < bucket_count; i++) {
            buckets[i].values = new int[n]; // 최악의 경우 모든 요소가 한 버킷에 들어갈 수 있음
            buckets[i].count = 0;
        }
        
        // 버킷에 요소 분배
        double bucket_width = (double)range / bucket_count;
        for (int i = low; i <= high; i++) {
            int bucket_idx = (int)((arr[i] - min_val) / bucket_width);
            if (bucket_idx >= bucket_count) bucket_idx = bucket_count - 1;
            
            buckets[bucket_idx].values[buckets[bucket_idx].count++] = arr[i];
        }
        
        // 각 버킷 내부 정렬 및 원래 배열에 복사
        int arr_idx = low;
        for (int i = 0; i < bucket_count; i++) {
            if (buckets[i].count > 0) {
                // 각 버킷 내부 정렬
                for (int j = 1; j < buckets[i].count; j++) {
                    int key = buckets[i].values[j];
                    int k = j - 1;
                    while (k >= 0 && buckets[i].values[k] > key) {
                        buckets[i].values[k + 1] = buckets[i].values[k];
                        k--;
                    }
                    buckets[i].values[k + 1] = key;
                }
                
                // 정렬된 버킷을 원래 배열에 복사
                for (int j = 0; j < buckets[i].count; j++) {
                    arr[arr_idx++] = buckets[i].values[j];
                }
            }
        }
        
        // 메모리 해제
        for (int i = 0; i < bucket_count; i++) {
            delete[] buckets[i].values;
        }
        delete[] buckets;
    }
}