#pragma once
#include "common.h"
#include "quadratic_sort.h"     // insertionSort()
#include <cmath>

#define INT_MAX 0x7FFFFFFF

void quickSortLomuto(int arr[], int low, int high);
void quickSortHoare(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void mergeSort(int arr[], int low, int high);
void heapSort(int arr[], int low, int high);

void shellSort(int arr[], int low, int high);
void timSort(int arr[], int low, int high);
void introSort(int arr[], int low, int high);

void smoothSort(int arr[], int low, int high);
void blockMergeSort(int arr[], int low, int high);
void librarySort(int arr[], int low, int high);
void tournamentSort(int arr[], int low, int high);
void patchworkSort(int arr[], int low, int high);

//////////////////////////////////////////////////////////////////////
int lomutoPartition(int arr[], int low, int high) {
    swap(arr[(low + high) / 2], arr[high]);
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
        if (arr[j] <= pivot) swap(arr[++i], arr[j]);
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortLomuto(int arr[], int low, int high) {
    if (low < high) {
        int pivotIdx = lomutoPartition(arr, low, high);
        quickSortLomuto(arr, low, pivotIdx - 1);
        quickSortLomuto(arr, pivotIdx + 1, high);
    }
}

int hoarePartition(int arr[], int low, int high) {
    int pivot = arr[(low + high) / 2];
    int i = low - 1, j = high + 1;

    while (true) {
        do i++; while (arr[i] < pivot);
        do j--; while (arr[j] > pivot);
        if (i >= j) return j;
        swap(arr[i], arr[j]);
    }
}

void quickSortHoare(int arr[], int low, int high) {
    if (low < high) {
        int pivotIdx = hoarePartition(arr, low, high);
        quickSortHoare(arr, low, pivotIdx);
        quickSortHoare(arr, pivotIdx + 1, high);
    }
}

void quickSort(int arr[], int low, int high) {
    quickSortLomuto(arr, low, high);
}

//////////////////////////////////////////////////////////////////////
void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;   

    int* left = new int[n1];
    int* right = new int[n2];

    for (int i = 0; i < n1; i++) left[i] = arr[low + i];
    for (int j = 0; j < n2; j++) right[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < n1) arr[k++] = left[i++];
    while (j < n2) arr[k++] = right[j++];

    delete[] left;
    delete[] right;
}

void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

//////////////////////////////////////////////////////////////////////
void heapify(int arr[], int low, int n, int i) {
    int curr = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[low + left] > arr[low + curr]) curr = left;
    if (right < n && arr[low + right] > arr[low + curr]) curr = right;
    if (curr != i) {
        swap(arr[low + i], arr[low + curr]);
        heapify(arr, low, n, curr);
    }
}

void heapSort(int arr[], int low, int high) {
    int n = high - low + 1;

    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, low, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[low], arr[low + i]);
        heapify(arr, low, i, 0);
    }
}

//////////////////////////////////////////////////////////////////////
// 셸 정렬 함수
void shellSort(int arr[], int low, int high) {
    int n = high - low + 1;
    
    // Knuth의 간격 시퀀스: h = 3*h + 1
    int gap = 1;
    while (gap < n / 3)
        gap = 3 * gap + 1;
    
    while (gap >= 1) {
        // 현재 간격으로 삽입 정렬 수행
        for (int i = low + gap; i <= high; i++) {
            int temp = arr[i];
            int j;
            
            for (j = i; j >= low + gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            
            arr[j] = temp;
        }
        
        gap /= 3;  // 다음 간격으로 줄임
    }
}

//////////////////////////////////////////////////////////////////////
// 인트로소트의 재귀 부분
void introSortUtil(int arr[], int low, int high, int depthLimit) {
    // 재귀 깊이 제한 확인
    if (depthLimit == 0) {
        // 깊이 제한 도달 시 힙 정렬로 전환
        heapSort(arr, low, high);
        return;
    }
    
    // 작은 배열은 삽입 정렬 사용
    if (high - low < 16) {
        insertionSort(arr, low, high);
        return;
    }
    
    // 퀵 정렬 (Hoare 파티션)
    int pivot = hoarePartition(arr, low, high);
    introSortUtil(arr, low, pivot, depthLimit - 1);
    introSortUtil(arr, pivot + 1, high, depthLimit - 1);
}

// 인트로소트 메인 함수
void introSort(int arr[], int low, int high) {
    // 재귀 깊이 제한 계산: 2 * log2(n)
    int n = high - low + 1;
    int depthLimit = 2 * (int)floor(log2(n));
    
    introSortUtil(arr, low, high, depthLimit);
}

//////////////////////////////////////////////////////////////////////
// 이진 검색을 사용한 삽입 위치 찾기
int binarySearch(int arr[], int item, int low, int high) {
    if (high <= low)
        return (item > arr[low]) ? (low + 1) : low;
    
    int mid = (low + high) / 2;
    
    if (item == arr[mid])
        return mid + 1;
    
    if (item > arr[mid])
        return binarySearch(arr, item, mid + 1, high);
    
    return binarySearch(arr, item, low, mid - 1);
}

// 이진 삽입 정렬
void binaryInsertionSort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // 이진 검색으로 삽입 위치 찾기
        int loc = binarySearch(arr, key, low, j);
        
        // 요소 이동
        while (j >= loc) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 팀소트의 합병 함수
void timMerge(int arr[], int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    int* left = new int[len1];
    int* right = new int[len2];
    
    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];
    
    int i = 0, j = 0, k = l;
    
    while (i < len1 && j < len2) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    
    while (i < len1)
        arr[k++] = left[i++];
    while (j < len2)
        arr[k++] = right[j++];
    
    delete[] left;
    delete[] right;
}

// 팀소트 메인 함수
void timSort(int arr[], int low, int high) {
    const int RUN = 32;  // 실행 크기 (작은 부분 배열 크기)
    int n = high - low + 1;
    
    // 작은 부분에 이진 삽입 정렬 수행
    for (int i = low; i <= high; i += RUN)
        binaryInsertionSort(arr, i, min(i + RUN - 1, high));
    
    // 정렬된 부분 배열 병합
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = low; left <= high - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, high);
            
            if (mid < right)
                timMerge(arr, left, mid, right);
        }
    }
}

//////////////////////////////////////////////////////////////////////
void smoothSort(int arr[], int low, int high) {
    // 레오나르도 수 계산 및 캐싱
    const int MAX_LEONARDO = 46; // 충분한 레오나르도 수
    int leonardo[MAX_LEONARDO];
    
    leonardo[0] = 1;
    leonardo[1] = 1;
    for (int i = 2; i < MAX_LEONARDO; i++) {
        leonardo[i] = leonardo[i - 1] + leonardo[i - 2] + 1;
    }
    
    // 범위 내 요소 수
    int n = high - low + 1;
    
    // 힙 구조 정보
    int p = 0;      // 처리 중인 위치
    int q = 0;      // 힙 크기
    int r = 0;      // 힙 카운터
    
    // sift-down 연산 구현
    auto sift = [&](int pos, int heap_size) {
        if (heap_size <= 1) return;
        
        int root = pos;
        int max_child = pos - 1; // 오른쪽 자식
        
        if (heap_size >= 3) {
            // 왼쪽 자식 위치 계산
            int left_child = pos - 1 - leonardo[heap_size - 2];
            
            // 더 큰 자식 찾기
            if (arr[low + left_child] > arr[low + max_child]) {
                max_child = left_child;
            }
        }
        
        // 루트가 가장 큰 자식보다 작으면 교환
        if (arr[low + root] < arr[low + max_child]) {
            swap(arr[low + root], arr[low + max_child]);
            
            int child_heap_size = 0;
            
            // 자식 힙 크기 결정
            if (max_child == pos - 1) {
                child_heap_size = heap_size - 1;
            } else {
                child_heap_size = heap_size - 2;
            }
            
            // 교환 후 해당 자식 힙에서 sift-down 수행
            if (child_heap_size > 1) {
                int m = max_child;
                int m_size = child_heap_size;
                
                if (m_size >= 3) {
                    int left = m - 1;
                    int right = m - 1 - leonardo[m_size - 2];
                    
                    if (arr[low + m] < arr[low + left] || arr[low + m] < arr[low + right]) {
                        if (arr[low + left] > arr[low + right]) {
                            swap(arr[low + m], arr[low + left]);
                            m = left;
                            m_size--;
                        } else {
                            swap(arr[low + m], arr[low + right]);
                            m = right;
                            m_size -= 2;
                        }
                        
                        // 재귀적 sift-down - 여기선 반복으로 대체
                        while (m_size > 1) {
                            int new_left = m - 1;
                            if (m_size < 3) {
                                if (arr[low + m] < arr[low + new_left]) {
                                    swap(arr[low + m], arr[low + new_left]);
                                }
                                break;
                            }
                            
                            int new_right = m - 1 - leonardo[m_size - 2];
                            
                            if (arr[low + m] >= arr[low + new_left] && 
                                arr[low + m] >= arr[low + new_right]) {
                                break;
                            }
                            
                            if (arr[low + new_left] > arr[low + new_right]) {
                                swap(arr[low + m], arr[low + new_left]);
                                m = new_left;
                                m_size--;
                            } else {
                                swap(arr[low + m], arr[low + new_right]);
                                m = new_right;
                                m_size -= 2;
                            }
                        }
                    }
                }
            }
        }
    };
    
    // 힙 트러스트 구성
    for (int i = 0; i < n; i++) {
        if (r == 0) {
            q = r = 1;
        } else if (r == 1) {
            q = r = 2;
        } else {
            r = leonardo[r] - 1;
            q++;
        }
        
        p = i;
        sift(p, q);
        
        while (q != 1 && r != q) {
            q = r;
            r = 1;
            p--;
            
            while (r <= q) {
                r++;
            }
            
            if (q < 3 || leonardo[r-1] + leonardo[r-3] != leonardo[r] - 1) {
                sift(p, q);
            } else {
                int num = p;
                int size = q;
                
                // 추가 작업 필요한 경우 처리
                if (arr[low + num] < arr[low + num - 1] || arr[low + num] < arr[low + num - 1 - leonardo[size - 2]]) {
                    if (arr[low + num - 1] > arr[low + num - 1 - leonardo[size - 2]]) {
                        swap(arr[low + num], arr[low + num - 1]);
                        sift(num - 1, size - 1);
                    } else {
                        swap(arr[low + num], arr[low + num - 1 - leonardo[size - 2]]);
                        sift(num - 1 - leonardo[size - 2], size - 2);
                    }
                }
            }
            
            r = q;
        }
    }
    
    // 요소 추출 및 정렬 완성
    for (int i = n - 1; i >= 0; i--) {
        if (q == 1) {
            r = q = 0;
        } else if (q == 2) {
            r = q = 1;
        } else {
            r = q;
            q = 1;
            
            while (q < r) {
                q++;
            }
            
            if (leonardo[q-1] + leonardo[q-3] == leonardo[q]) {
                q--;
            }
        }
        
        if (r == 0) continue;
        
        // 마지막으로 삽입 정렬로 마무리
        if (i > 0) {
            p--;
            
            while (q != 1 && r != q) {
                q = r;
                r = 1;
                
                while (r <= q) {
                    r++;
                }
                
                if (q < 3 || leonardo[r-1] + leonardo[r-3] != leonardo[r] - 1) {
                    sift(p, q);
                } else {
                    int num = p;
                    int size = q;
                    
                    if (arr[low + num] < arr[low + num - 1] || arr[low + num] < arr[low + num - 1 - leonardo[size - 2]]) {
                        if (arr[low + num - 1] > arr[low + num - 1 - leonardo[size - 2]]) {
                            swap(arr[low + num], arr[low + num - 1]);
                            sift(num - 1, size - 1);
                        } else {
                            swap(arr[low + num], arr[low + num - 1 - leonardo[size - 2]]);
                            sift(num - 1 - leonardo[size - 2], size - 2);
                        }
                    }
                }
                
                r = q;
            }
        }
    }
    
    // 마지막으로 삽입 정렬로 마무리 (정확성 보장)
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
// 두 블록을 병합하는 함수
void mergeBlocks(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    
    int* left = new int[n1];
    int* right = new int[n2];
    
    for (int i = 0; i < n1; i++)
        left[i] = arr[low + i];
    for (int j = 0; j < n2; j++)
        right[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    
    while (i < n1)
        arr[k++] = left[i++];
    while (j < n2)
        arr[k++] = right[j++];
    
    delete[] left;
    delete[] right;
}

// 삽입 정렬 (작은 블록용)
void insertionSortForBlock(int arr[], int low, int high) {
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

// 블록 병합 정렬
void blockMergeSort(int arr[], int low, int high) {
    int n = high - low + 1;
    
    // 캐시 효율성을 고려한 블록 크기 선택 (일반적으로 16-32)
    const int BLOCK_SIZE = 32;
    
    // 각 블록 내부를 삽입 정렬로 정렬
    for (int i = low; i <= high; i += BLOCK_SIZE) {
        int blockEnd = (i + BLOCK_SIZE - 1 < high) ? i + BLOCK_SIZE - 1 : high;
        insertionSortForBlock(arr, i, blockEnd);
    }
    
    // 병합 단계: 정렬된 블록들을 점진적으로 병합
    for (int blockSize = BLOCK_SIZE; blockSize < n; blockSize *= 2) {
        for (int leftStart = low; leftStart <= high - blockSize; leftStart += 2 * blockSize) {
            int mid = leftStart + blockSize - 1;
            int rightEnd = (leftStart + 2 * blockSize - 1 < high) ? 
                            leftStart + 2 * blockSize - 1 : high;
            
            mergeBlocks(arr, leftStart, mid, rightEnd);
        }
    }
}

//////////////////////////////////////////////////////////////////////
void librarySort(int arr[], int low, int high) {
    int n = high - low + 1;
    
    // 삽입 정렬로 작은 배열 처리
    if (n <= 16) {
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
    
    // 갭 인자 (epsilon) - 추가 공간의 비율
    const double epsilon = 1.0;  // 추가 공간 100%
    
    // 작업 배열 준비
    int size = (int)(n * (1.0 + epsilon));
    int* temp = new int[size];
    bool* filled = new bool[size]();  // 모두 false로 초기화
    
    // 첫 번째 요소 삽입
    temp[0] = arr[low];
    filled[0] = true;
    
    // 나머지 요소들 순차적으로 삽입
    for (int i = low + 1; i <= high; i++) {
        int val = arr[i];
        
        // 삽입 위치 찾기 (간단한 선형 검색)
        int pos = 0;
        while (pos < size && filled[pos] && temp[pos] < val) {
            pos++;
        }
        
        // 삽입 위치에 여유 공간이 없다면 재배치
        if (filled[pos]) {
            // 삽입 지점 이후의 요소들을 한 칸씩 이동
            int moveCount = 0;
            for (int j = pos; j < size && filled[j]; j++) {
                moveCount++;
            }
            
            // 이동할 공간이 없으면 모든 배열 재배치
            if (pos + moveCount >= size) {
                int* newTemp = new int[size];
                bool* newFilled = new bool[size]();
                
                // 균등하게 재배치
                int idx = 0;
                for (int j = 0; j < size; j++) {
                    if (filled[j]) {
                        int newPos = (int)(idx * (1.0 + epsilon));
                        if (newPos >= size) newPos = size - 1;
                        newTemp[newPos] = temp[j];
                        newFilled[newPos] = true;
                        idx++;
                    }
                }
                
                delete[] temp;
                delete[] filled;
                temp = newTemp;
                filled = newFilled;
                
                // 현재 요소 재삽입을 위해 반복
                i--;
                continue;
            }
            
            // 요소들을 뒤로 이동하여 공간 확보
            int end = pos + moveCount;
            for (int j = end; j > pos; j--) {
                temp[j] = temp[j-1];
                filled[j] = true;
            }
        }
        
        // 값 삽입
        temp[pos] = val;
        filled[pos] = true;
    }
    
    // 정렬된 요소들을 원본 배열로 복사
    int idx = 0;
    for (int i = 0; i < size; i++) {
        if (filled[i]) {
            arr[low + idx] = temp[i];
            idx++;
            if (idx >= n) break;
        }
    }
    
    delete[] temp;
    delete[] filled;
}

//////////////////////////////////////////////////////////////////////
void tournamentSort(int arr[], int low, int high) {
    int n = high - low + 1;
    
    // 토너먼트 트리 구축 (완전 이진 트리)
    int treeSize = 2 * n;
    int* tree = new int[treeSize];
    int* position = new int[treeSize]; // 각 값의 원래 배열 위치 추적
    
    // 트리 초기화
    for (int i = 0; i < treeSize; i++) {
        tree[i] = INT_MAX;
        position[i] = -1;
    }
    
    // 초기 토너먼트 설정: 리프 노드에 배치
    for (int i = 0; i < n; i++) {
        int node = n + i; // 리프 노드 시작 인덱스
        tree[node] = arr[low + i];
        position[node] = low + i;
    }
    
    // 토너먼트 트리 구축 (바텀업)
    for (int i = n - 1; i > 0; i--) {
        int left = 2 * i;
        int right = 2 * i + 1;
        
        if (tree[left] <= tree[right]) {
            tree[i] = tree[left];
            position[i] = position[left];
        } else {
            tree[i] = tree[right];
            position[i] = position[right];
        }
    }
    
    // n번 반복하여 최소값 추출
    for (int i = 0; i < n; i++) {
        // 루트(최소값)를 결과에 저장
        int winner = tree[1];
        int winnerPos = position[1];
        arr[low + i] = winner;
        
        // 해당 리프 노드를 무한대로 설정
        int leafNode = n;
        for (int j = n; j < 2 * n; j++) {
            if (position[j] == winnerPos) {
                leafNode = j;
                break;
            }
        }
        
        tree[leafNode] = INT_MAX;
        position[leafNode] = -1;
        
        // 루트까지 경로 업데이트
        int node = leafNode / 2;
        while (node > 0) {
            int left = 2 * node;
            int right = 2 * node + 1;
            
            if (tree[left] <= tree[right]) {
                tree[node] = tree[left];
                position[node] = position[left];
            } else {
                tree[node] = tree[right];
                position[node] = position[right];
            }
            
            node /= 2;
        }
    }
    
    delete[] tree;
    delete[] position;
}

//////////////////////////////////////////////////////////////////////
// 두 정렬된 부분 병합
void mergePatchwork(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    
    int* left = new int[n1];
    int* right = new int[n2];
    
    for (int i = 0; i < n1; i++)
        left[i] = arr[low + i];
    for (int j = 0; j < n2; j++)
        right[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    
    while (i < n1)
        arr[k++] = left[i++];
    while (j < n2)
        arr[k++] = right[j++];
    
    delete[] left;
    delete[] right;
}

// 이진 삽입 정렬 (작은 패치용)
void binaryInsertionSortPatch(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int left = low;
        int right = i - 1;
        
        // 이진 검색으로 삽입 위치 찾기
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] > key)
                right = mid - 1;
            else
                left = mid + 1;
        }
        
        // 요소 이동
        for (int j = i - 1; j >= left; j--)
            arr[j + 1] = arr[j];
        
        arr[left] = key;
    }
}

// 패치워크 정렬 구현
void patchworkSort(int arr[], int low, int high) {
    int n = high - low + 1;
    
    // 작은 패치 크기 설정 (16-32가 일반적)
    const int PATCH_SIZE = 24;
    
    // 각 패치를 이진 삽입 정렬로 정렬
    for (int i = low; i <= high; i += PATCH_SIZE) {
        int patchEnd = (i + PATCH_SIZE - 1 < high) ? i + PATCH_SIZE - 1 : high;
        binaryInsertionSortPatch(arr, i, patchEnd);
    }
    
    // 패치 병합: 작은 패치에서 시작하여 점진적으로 병합
    for (int size = PATCH_SIZE; size < n; size *= 2) {
        // 병합 최적화: 병합 전 검사 수행
        for (int left = low; left <= high - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < high) ? left + 2 * size - 1 : high;
            
            // 병합 최적화: 이미 정렬된 경우 건너뛰기
            if (arr[mid] > arr[mid + 1])
                mergePatchwork(arr, left, mid, right);
        }
    }
}
