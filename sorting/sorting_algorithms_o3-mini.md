아래는 각 카테고리별로 분리한 정렬 알고리즘 테이블입니다.

---

### Quadratic Sorting Algorithms

| **Algorithm**                    | **Time Complexity (Avg/Worst)**         | **Stability**              | **Key Characteristics**                                                                                     |
|----------------------------------|-----------------------------------------|----------------------------|-------------------------------------------------------------------------------------------------------------|
| Bubble Sort (★)                  | O(n²) / O(n²)                           | Stable                     | 인접 원소 교환을 반복하며 정렬. 기본 개념 학습에 유용.                                                       |
| Selection Sort (★★)              | O(n²) / O(n²)                           | Not Stable                 | 매 회 최소(또는 최대) 원소를 선택하여 제자리 교환. 불필요한 교환이 발생할 수 있음.                            |
| Insertion Sort (★★)              | O(n²) / O(n²); 최선 O(n)                 | Stable                     | 정렬된 부분 배열에 새 원소를 삽입. 거의 정렬된 데이터에서 매우 효율적임.                                      |
| Gnome Sort                       | O(n²) / O(n²)                           | Stable (구현에 따라 다름)   | 인접 원소 비교 후 위치 이동 방식. 간단하지만 실전에서는 사용 빈도가 낮음.                                     |
| Cocktail Shaker Sort             | O(n²) / O(n²)                           | Stable                     | 양방향으로 정렬을 진행하는 버블 정렬의 변형.                                                                 |
| Shell Sort                       | 평균: O(n log² n) ~ O(n^(3/2)); Worst: O(n²) | Not Stable                 | 삽입 정렬의 개선판으로, gap(간격)을 두고 부분 정렬 수행. gap 시퀀스 선택이 중요함.                           |

---

### Log-Linear Sorting Algorithms

| **Algorithm**                    | **Time Complexity (Avg/Worst)**         | **Stability**              | **Key Characteristics**                                                                                     |
|----------------------------------|-----------------------------------------|----------------------------|-------------------------------------------------------------------------------------------------------------|
| Merge Sort (★★)                 | O(n log n) / O(n log n)                  | Stable                     | 분할 정복을 통한 병합 방식. 안정적 정렬이 가능하지만 추가 메모리 사용 필요.                                    |
| Quick Sort (★★)                 | 평균: O(n log n); Worst: O(n²)            | Not Stable                 | 피벗 기준 분할 방식. 평균적으로 매우 빠르며 in-place 정렬이 가능하지만, 최악의 경우 대비 피벗 선택 전략이 중요함.   |
| Heap Sort (★)                   | O(n log n) / O(n log n)                  | Not Stable                 | 힙 자료구조를 활용한 정렬. in-place로 동작하며, 최악의 경우에도 일정한 성능 보장.                             |
| Intro Sort                       | 평균: O(n log n); Worst: O(n log n)       | Not Stable                 | Quick Sort와 Heap Sort의 하이브리드 방식. C++의 std::sort 구현에 가까움.                                    |
| Timsort                        | O(n log n) / O(n log n)                  | Stable                     | Merge Sort와 Insertion Sort 결합. Python 등 실제 프로그래밍 언어에서 사용됨.                                   |
| Smoothsort                      | 평균: O(n log n); Worst: O(n log n)       | Not Stable                 | Heap Sort의 변형. 거의 정렬된 데이터에서 더 빠른 성능을 보일 수 있음.                                         |

---

### Linear Time Sorting Algorithms

| **Algorithm**                    | **Time Complexity (Avg/Worst)**         | **Stability**              | **Key Characteristics**                                                                                     |
|----------------------------------|-----------------------------------------|----------------------------|-------------------------------------------------------------------------------------------------------------|
| Counting Sort (★★)              | O(n + k) / O(n + k)                      | Stable                     | 정수 등 한정된 범위 데이터에 대해 선형 시간 정렬 가능. 메모리 사용량이 입력 범위에 비례함.                       |
| Radix Sort (★★)                 | O(n·d) / O(n·d)                         | Stable (하위 정렬이 안정적일 경우) | 자리수(digit) 단위로 분류하여 정렬. 내부에 Counting Sort를 하위 정렬로 사용하는 경우가 많음.                    |
| Bucket Sort (★)                 | 평균: O(n + k); Worst: O(n²)             | Stable (구현에 따라 다름)   | 데이터를 여러 버킷으로 분배 후 각각 정렬. 데이터가 균등하게 분포할 때 효과적임.                                |
| Pigeonhole Sort                 | O(n + k) / O(n + k)                      | Stable                     | Counting Sort와 유사하게, 데이터 범위가 제한적일 때 사용할 수 있는 정렬 알고리즘.                              |

---

이 자료는 중급 학습자를 대상으로 하여, 각 카테고리 내 핵심 알고리즘에 대해 (★★) 필수, (★) 중요으로 표시해 두어 체계적인 학습 및 비교 분석에 도움이 될 수 있도록 구성하였습니다.