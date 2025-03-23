#pragma once
#include "common.h"
#include <cmath>

// 선택 알고리즘 함수 선언
// 모든 함수는 배열에서 k번째 큰 원소(k=1: 최대값)를 반환
int sortAndSelect(int arr[], int low, int high, int k);
int quickSelect(int arr[], int low, int high, int k);
int heapSelect(int arr[], int low, int high, int k);
int medianOfMediansSelect(int arr[], int low, int high, int k);
int binarySearchSelect(int arr[], int low, int high, int k);
int countingSelect(int arr[], int low, int high, int k);
int partialMergeSelect(int arr[], int low, int high, int k);


///////////////////////////////////////////////////////////////////////
// 1. Sort and Select
int sortAndSelect(int arr[], int low, int high, int k) {
    // 배열 복사
    int n = high - low + 1;
    int* temp = new int[n];
    for (int i = 0; i < n; i++)
        temp[i] = arr[low + i];
    
    // 간단한 정렬 구현 (삽입 정렬)
    for (int i = 1; i < n; i++) {
        int key = temp[i];
        int j = i - 1;
        while (j >= 0 && temp[j] < key) {
            temp[j + 1] = temp[j];
            j--;
        }
        temp[j + 1] = key;
    }
    
    // k번째 큰 원소 선택
    int result = temp[k - 1];
    
    delete[] temp;
    return result;
}


///////////////////////////////////////////////////////////////////////
// 2. Quick Select (★★)
// 퀵 선택 알고리즘의 파티션 함수
int quickSelectPartition(int arr[], int low, int high) {
    // 피벗 선택 (중간 요소를 사용하여 성능 향상)
    int mid = low + (high - low) / 2;
    swap(arr[mid], arr[high]);
    
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] >= pivot) {  // 내림차순 정렬 (k번째 큰 값 찾기)
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int quickSelect(int arr[], int low, int high, int k) {
    if (low <= high) {
        // 파티션을 통해 피벗의 위치 찾기
        int pivotIndex = quickSelectPartition(arr, low, high);
        
        // 피벗이 찾는 k번째 위치인 경우
        if (pivotIndex - low + 1 == k)
            return arr[pivotIndex];
        
        // k가 피벗 위치보다 작은 경우, 왼쪽 부분 배열 탐색
        if (pivotIndex - low + 1 > k)
            return quickSelect(arr, low, pivotIndex - 1, k);
        
        // k가 피벗 위치보다 큰 경우, 오른쪽 부분 배열 탐색
        return quickSelect(arr, pivotIndex + 1, high, k - (pivotIndex - low + 1));
    }
    
    return -1; // 적절한 원소가 없는 경우
}


///////////////////////////////////////////////////////////////////////
// 3. Heap-based Selection (★)
// 힙의 최대 힙 속성을 유지하는 함수
void maxHeapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

int heapSelect(int arr[], int low, int high, int k) {
    int n = high - low + 1;
    
    // 배열 복사
    int* heap = new int[n];
    for (int i = 0; i < n; i++)
        heap[i] = arr[low + i];
    
    // 최대 힙 구성
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(heap, n, i);
    
    // k번째 큰 원소 추출
    for (int i = 1; i < k; i++) {
        heap[0] = heap[n - i];
        maxHeapify(heap, n - i, 0);
    }
    
    int result = heap[0];
    delete[] heap;
    return result;
}


///////////////////////////////////////////////////////////////////////
// 4. Median of Medians (BFPRT)
// 중앙값들의 중앙값을 찾는 함수
int findMedian(int arr[], int n) {
    // 간단한 삽입 정렬로 정렬 후 중앙값 반환
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return arr[n / 2];
}

int medianOfMediansPartition(int arr[], int low, int high, int pivot) {
    // pivot 값을 기준으로 파티션 수행
    for (int i = low; i <= high; i++) {
        if (arr[i] == pivot) {
            swap(arr[i], arr[high]);
            break;
        }
    }
    
    int pivotValue = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] >= pivotValue) {  // 내림차순 정렬 (k번째 큰 값 찾기)
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int findMedianOfMedians(int arr[], int low, int high) {
    int n = high - low + 1;
    
    // 배열 크기가 5 이하인 경우, 직접 중앙값 계산
    if (n <= 5)
        return findMedian(&arr[low], n);
    
    // n/5 그룹으로 나누고 각 그룹의 중앙값 계산
    int numGroups = (n + 4) / 5;  // ceil(n/5)
    int* medians = new int[numGroups];
    
    for (int i = 0; i < numGroups; i++) {
        int groupStart = low + i * 5;
        int groupEnd = min(groupStart + 4, high);
        medians[i] = findMedian(&arr[groupStart], groupEnd - groupStart + 1);
    }
    
    // 중앙값들의 중앙값 찾기
    int medianOfMedians;
    if (numGroups == 1)
        medianOfMedians = medians[0];
    else
        medianOfMedians = findMedianOfMedians(medians, 0, numGroups - 1);
    
    delete[] medians;
    return medianOfMedians;
}

int medianOfMediansSelectUtil(int arr[], int low, int high, int k) {
    int n = high - low + 1;
    
    // 배열 크기가 작으면 직접 정렬하여 반환
    if (n <= 5) {
        int* temp = new int[n];
        for (int i = 0; i < n; i++)
            temp[i] = arr[low + i];
        
        // 내림차순 정렬
        for (int i = 1; i < n; i++) {
            int key = temp[i];
            int j = i - 1;
            while (j >= 0 && temp[j] < key) {
                temp[j + 1] = temp[j];
                j--;
            }
            temp[j + 1] = key;
        }
        
        int result = temp[k - 1];
        delete[] temp;
        return result;
    }
    
    // 중앙값들의 중앙값을 피벗으로 선택
    int pivot = findMedianOfMedians(arr, low, high);
    
    // 피벗을 기준으로 배열 파티션
    int pivotIndex = medianOfMediansPartition(arr, low, high, pivot);
    
    // 피벗이 찾는 k번째 위치인 경우
    int rank = pivotIndex - low + 1;
    if (rank == k)
        return arr[pivotIndex];
    
    // k가 피벗 위치보다 작은 경우, 왼쪽 부분 배열 탐색
    if (rank > k)
        return medianOfMediansSelectUtil(arr, low, pivotIndex - 1, k);
    
    // k가 피벗 위치보다 큰 경우, 오른쪽 부분 배열 탐색
    return medianOfMediansSelectUtil(arr, pivotIndex + 1, high, k - rank);
}

int medianOfMediansSelect(int arr[], int low, int high, int k) {
    // 배열 복사 (원본 보존)
    int n = high - low + 1;
    int* temp = new int[n];
    for (int i = 0; i < n; i++)
        temp[i] = arr[low + i];
    
    int result = medianOfMediansSelectUtil(temp, 0, n - 1, k);
    
    delete[] temp;
    return result;
}


///////////////////////////////////////////////////////////////////////
// 5. Binary Search with Counting
int binarySearchSelect(int arr[], int low, int high, int k) {
    // 배열의 최소값과 최대값 찾기
    int minVal = arr[low], maxVal = arr[low];
    for (int i = low + 1; i <= high; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    
    // 이진 탐색 수행
    int left = minVal, right = maxVal;
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        // mid보다 큰 원소 개수 계산
        int count = 0;
        for (int i = low; i <= high; i++) {
            if (arr[i] > mid) count++;
        }
        
        if (count >= k) left = mid + 1;
        else right = mid;
    }
    
    return left;
}


///////////////////////////////////////////////////////////////////////
// 6. Counting Sort-based (★)
int countingSelect(int arr[], int low, int high, int k) {
    // 최대값과 최소값 찾기
    int max = arr[low], min = arr[low];
    for (int i = low + 1; i <= high; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    
    // 범위 계산 및 카운트 배열 생성
    int range = max - min + 1;
    int* count = new int[range]();  // 0으로 초기화
    
    // 요소 발생 횟수 세기
    for (int i = low; i <= high; i++)
        count[arr[i] - min]++;
    
    // k번째 큰 원소 찾기 (내림차순 순회)
    int kCount = 0;
    for (int i = range - 1; i >= 0; i--) {
        kCount += count[i];
        if (kCount >= k) {
            delete[] count;
            return i + min;
        }
    }
    
    delete[] count;
    return min;  // 찾지 못한 경우 최소값 반환
}


///////////////////////////////////////////////////////////////////////
// 7. Partial Merge Sort
void siftDown(int heap[], int size, int root) {
    int smallest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    
    if (left < size && heap[left] < heap[smallest])
        smallest = left;
    
    if (right < size && heap[right] < heap[smallest])
        smallest = right;
    
    if (smallest != root) {
        swap(heap[root], heap[smallest]);
        siftDown(heap, size, smallest);
    }
}

int partialMergeSelect(int arr[], int low, int high, int k) {
    int n = high - low + 1;
    
    // k가 배열 크기보다 큰 경우 조정
    if (k > n) k = n;
    
    // 최소 힙 생성
    int* minHeap = new int[k];
    for (int i = 0; i < k; i++)
        minHeap[i] = arr[low + i];
    
    // 최소 힙 구성
    for (int i = k / 2 - 1; i >= 0; i--)
        siftDown(minHeap, k, i);
    
    // 나머지 요소들을 처리
    for (int i = k; i < n; i++) {
        if (arr[low + i] > minHeap[0]) {
            minHeap[0] = arr[low + i];
            siftDown(minHeap, k, 0);
        }
    }
    
    // 최소 힙의 루트는 k번째 큰 원소
    int result = minHeap[0];
    
    delete[] minHeap;
    return result;
}