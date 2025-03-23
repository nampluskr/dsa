#pragma once
#include "common.h"


void bubbleSort(int arr[], int low, int high);
void selectionSort(int arr[], int low, int high);
void insertionSort(int arr[], int low, int high);
void combSort(int arr[], int low, int high);
void cocktailSort(int arr[], int low, int high);
void gnomeSort(int arr[], int low, int high);
void cycleSort(int arr[], int low, int high);
void oddEvenSort(int arr[], int low, int high);

//////////////////////////////////////////////////////////////////////
void bubbleSort(int arr[], int low, int high) {
    for (int i = low; i < high; i++) {
        bool swapped = false;
        for (int j = low; j < high - (i - low); j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // 교환이 없으면 이미 정렬된 상태
        if (!swapped) break;
    }
}

//////////////////////////////////////////////////////////////////////
void selectionSort(int arr[], int low, int high) {
    for (int i = low; i < high; i++) {
        int min_idx = i;
        for (int j = i + 1; j <= high; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        
        if (min_idx != i)
            swap(arr[i], arr[min_idx]);
    }
}

//////////////////////////////////////////////////////////////////////
void insertionSort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

//////////////////////////////////////////////////////////////////////
void combSort(int arr[], int low, int high) {
    int n = high - low + 1;
    int gap = n;
    bool swapped = true;
    
    // 축소 계수 1.3이 실험적으로 좋은 결과를 보임
    const double shrink = 1.3;
    
    while (gap > 1 || swapped) {
        // 간격 계산
        gap = (int)(gap / shrink);
        if (gap < 1) gap = 1;
        
        swapped = false;
        
        // 현재 간격으로 비교 및 교환
        for (int i = low; i + gap <= high; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}


//////////////////////////////////////////////////////////////////////
void cocktailSort(int arr[], int low, int high) {
    bool swapped = true;
    int start = low;
    int end = high;
    
    while (swapped) {
        // 왼쪽에서 오른쪽으로 이동하며 정렬
        swapped = false;
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        
        // 한 사이클 완료 후 더 이상 교환이 없으면 종료
        if (!swapped) break;
        
        // 끝 인덱스 감소
        end--;
        
        // 오른쪽에서 왼쪽으로 이동하며 정렬
        swapped = false;
        for (int i = end - 1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        
        // 시작 인덱스 증가
        start++;
    }
}

//////////////////////////////////////////////////////////////////////
void gnomeSort(int arr[], int low, int high) {
    int i = low;
    
    while (i <= high) {
        if (i == low || arr[i - 1] <= arr[i])
            i++;
        else {
            swap(arr[i], arr[i - 1]);
            i--;
        }
    }
}

//////////////////////////////////////////////////////////////////////
void cycleSort(int arr[], int low, int high) {
    int n = high - low + 1;
    
    for (int cycle_start = low; cycle_start < high; cycle_start++) {
        int item = arr[cycle_start];
        
        // 현재 아이템의 위치 찾기
        int pos = cycle_start;
        for (int i = cycle_start + 1; i <= high; i++)
            if (arr[i] < item)
                pos++;
        
        // 이미 올바른 위치에 있으면 다음으로
        if (pos == cycle_start) continue;
        
        // 중복 요소 건너뛰기
        while (item == arr[pos])
            pos++;
        
        // 올바른 위치에 배치
        if (pos != cycle_start)
            swap(item, arr[pos]);
        
        // 사이클 완성할 때까지 반복
        while (pos != cycle_start) {
            pos = cycle_start;
            
            // 새 위치 찾기
            for (int i = cycle_start + 1; i <= high; i++)
                if (arr[i] < item)
                    pos++;
            
            // 중복 요소 건너뛰기
            while (item == arr[pos])
                pos++;
            
            // 올바른 위치에 배치
            if (item != arr[pos])
                swap(item, arr[pos]);
        }
    }
}

//////////////////////////////////////////////////////////////////////
void oddEvenSort(int arr[], int low, int high) {
    bool sorted = false;
    
    while (!sorted) {
        sorted = true;
        
        // 홀수 인덱스 정렬
        for (int i = low + 1; i < high; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
        
        // 짝수 인덱스 정렬
        for (int i = low; i < high; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
    }
}
