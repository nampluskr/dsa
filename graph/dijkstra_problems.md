
The user is asking me to list all common or possible types of Dijkstra's algorithm problems that appear in coding tests, without providing code. They want me to explain solution methods and number them according to frequency of appearance or importance.

The request is in Korean, so I should respond in Korean as well.

Let me start by categorizing the most common types of Dijkstra's algorithm problems that appear in coding tests:

1. Basic Shortest Path Problems
   - Finding the shortest path from a single source to a single destination
   - Finding the shortest paths from a single source to all other nodes
   - Finding the K-th shortest path

2. Modified Graph Problems
   - Graphs with weighted edges (standard Dijkstra's scenario)
   - Graphs with additional constraints on edges
   - Multi-layered graphs

3. Real-world Applications
   - Network routing problems
   - GPS navigation problems
   - Resource allocation problems

4. Advanced Variations
   - Bidirectional Dijkstra's algorithm
   - Dijkstra's with dynamic programming
   - Combining Dijkstra's with other algorithms

Now, I'll explain each type in detail, focusing on solution methods rather than providing actual code, and I'll number them according to their frequency in coding tests and importance:

1. 기본 최단 경로 찾기 (Basic shortest path finding) - 가장 빈출
2. 특정 조건이 있는 최단 경로 (Shortest path with specific conditions)
3. 다중 시작점 다익스트라 (Multiple source Dijkstra)
4. K번째 최단 경로 찾기 (K-th shortest path)
5. 양방향 다익스트라 (Bidirectional Dijkstra)
6. 다익스트라와 동적 계획법 결합 (Dijkstra with DP)
7. 다중 가중치 그래프 (Multi-weight graphs)
8. 최단 경로 복원 (Path reconstruction)
9. 최대 용량 경로 찾기 (Maximum capacity path)
10. 특정 노드를 반드시 방문하는 최단 경로 (Shortest path visiting specific nodes)

Let me now explain each of these problem types in detail in Korean, without including code.

# 코딩테스트 다익스트라 알고리즘 문제 유형 및 풀이 방법

## 1. 기본 최단 경로 찾기 (가장 빈출)
한 시작점에서 목적지까지의 최단 경로를 찾는 기본 문제입니다. 우선순위 큐를 활용하여 현재까지 발견된 최단 거리가 가장 짧은 노드부터 탐색합니다. 각 노드까지의 최단 거리를 배열에 저장하고, 인접한 노드들을 방문하며 더 짧은 경로가 발견되면 거리를 갱신합니다.

## 2. 특정 조건이 있는 최단 경로
기본 다익스트라에 추가적인 제약 조건이 있는 문제입니다. 예를 들어:
- 특정 비용(연료, 돈 등) 제한 내에서의 최단 경로
- 특정 시간대에 통행 가능한 경로만 이용
- 통행료가 있는 경로 최소화

풀이: 추가 조건을 상태로 관리하며 다익스트라를 확장합니다. 거리 배열을 2차원 이상으로 확장하여 [노드][상태] 형태로 최단 거리를 관리합니다.

## 3. 최단 경로 복원
단순히 최단 거리뿐만 아니라 실제 경로를 출력해야 하는 문제입니다.

풀이: 각 노드의 이전 노드를 저장하는 배열을 추가로 관리합니다. 경로 갱신 시 이전 노드 정보도 함께 업데이트하고, 목적지에 도달한 후 역추적하여 경로를 복원합니다.

## 4. 다중 시작점 다익스트라
여러 시작점에서 동시에 출발하여 각 노드까지의 최단 거리를 찾는 문제입니다.

풀이: 모든 시작점을 우선순위 큐에 초기 거리 0으로 넣고 일반 다익스트라처럼 진행합니다. 여러 출발점에서 동시에 퍼져나가는 형태로 동작합니다.

## 5. K번째 최단 경로
출발점에서 목적지까지의 K번째로 짧은 경로를 찾는 문제입니다.

풀이: 각 노드마다 최단 경로들을 우선순위 큐나 배열로 관리합니다. 노드 방문 시 해당 노드까지의 거리를 K개까지 저장하고, 더 짧은 경로가 발견되면 갱신합니다.

## 6. 양방향 다익스트라
출발점과 도착점 양쪽에서 동시에 다익스트라를 실행하여 효율성을 높이는 문제입니다.

풀이: 출발점에서 정방향 다익스트라, 도착점에서 역방향 다익스트라를 동시에 실행합니다. 두 탐색이 만나는 지점을 찾아 최단 경로를 계산합니다.

## 7. 특정 노드를 반드시 방문하는 최단 경로
출발점에서 도착점까지 가는 동안 특정 노드나 여러 노드를 반드시 방문해야 하는 문제입니다.

풀이: 필수 방문 노드들 사이의 최단 거리를 모두 계산한 후, 가능한 모든 방문 순서를 고려하여 전체 경로 중 최단 경로를 선택합니다. 방문 순서가 많지 않다면 순열을 사용할 수 있습니다.

## 8. 다익스트라와 동적 계획법 결합
추가적인 상태나 조건이 있어 DP와 결합된 문제입니다.

풀이: 상태를 [노드][추가상태]로 정의하고, 각 상태에 대한 최단 거리를 계산합니다. 예를 들어 [현재노드][남은자원] 형태로 DP 테이블을 구성할 수 있습니다.

## 9. 최대 용량 경로 찾기
각 간선이 용량(대역폭 등)을 갖고 있을 때, 출발점에서 도착점까지 최대 용량을 갖는 경로를 찾는 문제입니다.

풀이: 다익스트라의 최소화 대신 최대화 문제로 변형합니다. 우선순위 큐를 최대 힙으로 사용하고, 간선을 통과할 때는 현재까지의 경로 중 최소 용량을 계산합니다.

## 10. 다중 가중치 그래프
간선이 여러 종류의 가중치를 갖는 문제입니다(거리와 비용 등).

풀이: 우선순위를 정해 하나의 가중치로 최적화하고 나머지는 제약조건으로 사용하거나, 파레토 최적해를 구하기 위해 다차원 배열로 최단 거리를 관리합니다.

각 문제 유형에 접근할 때는 기본 다익스트라 알고리즘을 이해하고, 문제의 특성에 맞게 자료구조와 상태 관리 방식을 변형하는 것이 핵심입니다.
