# 중급자를 위한 정렬 알고리즘 체계적 정리

C++ 문법과 기본적인 자료구조 및 알고리즘에 익숙한 중급자를 위한 정렬 알고리즘 강의자료입니다. 시간 복잡도에 따라 세 가지 주요 카테고리로 정리했습니다.

## 1. Quadratic Sorting Algorithms (이차 시간 정렬 알고리즘)

| 알고리즘 | 시간 복잡도 (최선/평균/최악) | 안정성 | 특징 |
|-----------|--------------------------------------|--------|-----------------|
| **Insertion Sort** **(★)** | O(n)/O(n²)/O(n²) | 안정적 | 작은 배열이나 거의 정렬된 데이터에 효율적, 적응형 알고리즘 |
| **Shell Sort** **(★)** | O(n log n)/O(n^1.3)/O(n²) | 불안정 | 간격 시퀀스에 따라 성능 차이, 삽입 정렬의 개선 버전 |
| Bubble Sort | O(n)/O(n²)/O(n²) | 안정적 | 구현이 간단하지만 비효율적, 조기 종료로 최적화 가능 |
| Selection Sort | O(n²)/O(n²)/O(n²) | 불안정 | 교환 횟수 최소화(최대 n-1번), 항상 동일한 비교 횟수 수행 |
| Comb Sort | O(n log n)/O(n²)/O(n²) | 불안정 | 간격 감소 전략을 사용한 버블 정렬의 개선 버전 |
| Cocktail Sort | O(n)/O(n²)/O(n²) | 안정적 | 양방향 버블 정렬, "거북이 값" 문제 해결 |
| Cycle Sort | O(n²)/O(n²)/O(n²) | 불안정 | 메모리 쓰기 최소화, 제자리 정렬에 최적화 |
| Gnome Sort | O(n)/O(n²)/O(n²) | 안정적 | 매우 단순한 구현의 삽입 정렬 변형 |
| Odd-Even Sort | O(n)/O(n²)/O(n²) | 안정적 | 병렬 처리 아키텍처에 적합한 설계 |
| Stooge Sort | O(n^(log₃/log₁.₅))/O(n^(log₃/log₁.₅))/O(n^(log₃/log₁.₅)) | 불안정 | 재귀적 분할 정복, 매우 느린 성능 |

## 2. Log-Linear Sorting Algorithms (로그 선형 정렬 알고리즘)

| 알고리즘 | 시간 복잡도 (최선/평균/최악) | 안정성 | 특징 |
|-----------|--------------------------------------|--------|-----------------|
| **Quick Sort** **(★★)** | O(n log n)/O(n log n)/O(n²) | 불안정 | 분할 정복, 실제로 매우 빠름, 피벗 선택이 중요 |
| **Merge Sort** **(★★)** | O(n log n)/O(n log n)/O(n log n) | 안정적 | 분할 정복, 일관된 성능, 연결 리스트에 효율적 |
| **Heap Sort** **(★★)** | O(n log n)/O(n log n)/O(n log n) | 불안정 | 최악의 경우에도 성능 보장, 힙 자료구조 사용 |
| **Introsort** **(★)** | O(n log n)/O(n log n)/O(n log n) | 불안정 | 퀵, 힙, 삽입 정렬의 하이브리드; C++ STL sort() 구현 |
| **Timsort** **(★)** | O(n)/O(n log n)/O(n log n) | 안정적 | 병합과 삽입 정렬의 하이브리드, 파이썬 내장 정렬 |
| Smooth Sort | O(n)/O(n log n)/O(n log n) | 불안정 | 힙 정렬의 변형, 적응형 알고리즘 |
| Block Merge Sort | O(n)/O(n log n)/O(n log n) | 안정적 | 캐시 효율성이 향상된 블록 기반 병합 정렬 |
| Library Sort | O(n)/O(n log n)/O(n log n) | 안정적 | 성능 향상을 위한 간격을 가진 삽입 기반 정렬 |
| Tournament Sort | O(n log n)/O(n log n)/O(n log n) | 안정적 | 이진 트리 토너먼트 구조 사용 |
| Patchwork Sort | O(n log n)/O(n log n)/O(n log n) | 안정적 | 병합 정렬과 삽입 정렬의 조합 |

## 3. Linear Time Sorting Algorithms (선형 시간 정렬 알고리즘)

| 알고리즘 | 시간 복잡도 (최선/평균/최악) | 안정성 | 특징 |
|-----------|--------------------------------------|--------|-----------------|
| **Counting Sort** **(★★)** | O(n+k)/O(n+k)/O(n+k) | 안정적 | 제한된 범위의 정수에 매우 효율적, k는 값의 범위 |
| **Radix Sort** **(★★)** | O(d(n+k))/O(d(n+k))/O(d(n+k)) | 안정적 | 자릿수별 정렬, d는 자릿수, k는 진법(보통 10) |
| **Bucket Sort** **(★)** | O(n+k)/O(n+k)/O(n²) | 안정적 | 균등 분포 데이터에 효율적, k는 버킷 수 |
| Flash Sort | O(n)/O(n+k)/O(n²) | 불안정 | 분포 기반, 메모리 효율적 |
| Pigeonhole Sort | O(n+k)/O(n+k)/O(n+k) | 안정적 | 계수 정렬의 변형, 값이 고르게 분포된 경우 효율적 |
| Distribution Sort | O(n)/O(n+k)/O(n+k) | 안정적 | 데이터 분포 특성을 활용, 다양한 구현이 존재 |

## 특별 주목 알고리즘 (★★: 필수, ★: 중요)

1. **Quadratic Sorting Algorithms**:
   - **Insertion Sort(★)**: 작은 데이터셋에 효율적이며 다른 알고리즘의 기본 구성 요소로 사용됨
   - **Shell Sort(★)**: 삽입 정렬의 개선 버전으로 중간 크기 데이터에 유용

2. **Log-Linear Sorting Algorithms**:
   - **Quick Sort(★★)**: 실제 구현에서 가장 빠른 정렬 중 하나, 피벗 선택 전략이 핵심
   - **Merge Sort(★★)**: 안정적인 성능과 안정 정렬이 필요한 상황에 적합
   - **Heap Sort(★★)**: 최악 케이스에도 성능 보장, 제자리 정렬 가능
   - **Introsort(★)**: C++ STL의 sort() 구현, 실제 환경에 최적화된 하이브리드
   - **Timsort(★)**: 파이썬의 내장 정렬, 실제 데이터에 최적화된 하이브리드

3. **Linear Time Sorting Algorithms**:
   - **Counting Sort(★★)**: 제한된 범위의 정수 정렬에 매우 효율적
   - **Radix Sort(★★)**: 큰 정수, 문자열 정렬에 효율적
   - **Bucket Sort(★)**: 균등 분포 데이터에 효율적, 병렬화 가능

## 코딩테스트 특화 알고리즘

코딩테스트에서 직접 구현해야 할 가능성이 높은 알고리즘은 다음과 같습니다:
1. **Quick Sort**: 일반적인 상황에서 가장 효율적, 분할 정복 접근법의 대표적 예시
2. **Merge Sort**: 안정 정렬이 필요하거나 최악 케이스 성능 보장이 필요할 때
3. **Counting Sort**: 제한된 범위의 정수 정렬에 매우 빠름 (특히 범위가 작을 때)
4. **Heap Sort**: 메모리 제약이 있는 환경에서 효율적인 제자리 정렬