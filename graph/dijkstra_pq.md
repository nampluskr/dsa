```cpp
#include <stdio.h>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

const int MAX_N = 101;
const int INF = numeric_limits<int>::max();

struct Edge {
    int to, cost;
    
    // 우선순위 큐에서 사용할 비교 연산자 (최소 비용 우선)
    bool operator<(const Edge& other) const {
        return cost > other.cost; // 최소 비용 우선을 위해 '>' 사용
    }
};

vector<Edge> graph[MAX_N];
bool visited[MAX_N];
int dist[MAX_N];          // 시작 노드로부터의 최단 거리
int parent[MAX_N];        // 최단 경로 트리에서의 부모 노드
vector<int> path;         // 경로 저장

// 유틸리티 함수
void addEdge(int start, int end, int cost) {
    graph[start].push_back({end, cost});
}

void initGraph() {
    for (int i = 0; i < MAX_N; i++) {
        graph[i].clear();
        visited[i] = false;
        dist[i] = INF;
        parent[i] = -1;
    }
    path.clear();
}

// 경로 재구성 함수
void reconstructPath(int start, int target) {
    path.clear();
    for (int at = target; at != -1; at = parent[at]) {
        path.push_back(at);
        if (at == start) break;
    }
    // 경로 뒤집기 (시작 -> 끝 순서로)
    reverse(path.begin(), path.end());
}

// 경로 출력 함수
void printPath(int target) {
    printf("최단 경로: ");
    for (size_t i = 0; i < path.size(); i++) {
        printf("%d", path[i]);
        if (i < path.size() - 1)
            printf(" -> ");
    }
    printf("\n");
    printf("총 비용: %d\n", dist[target]);
}

//===================================================================
// 1. 큐에 넣기 전 방문 표시 + 방문 배열 사용 (BFS1 + visited)
//===================================================================
void dijkstra_MarkBeforeQueue_WithVisited(int start, int target) {
    priority_queue<Edge> pq;
    
    // 시작 노드 초기화
    dist[start] = 0;
    visited[start] = true;
    pq.push({start, 0});
    
    while (!pq.empty()) {
        auto curr = pq.top(); pq.pop();
        
        // 목표 노드에 도달한 경우
        if (curr.to == target) {
            reconstructPath(start, target);
            return;
        }
        
        // 인접 노드 탐색
        for (const auto& next : graph[curr.to]) {
            int nextNode = next.to;
            int nextDist = curr.cost + next.cost;
            
            // 새 경로가 더 짧은 경우 업데이트
            if (nextDist < dist[nextNode]) {
                dist[nextNode] = nextDist;
                parent[nextNode] = curr.to;
                
                // 방문하지 않은 노드만 큐에 추가
                if (!visited[nextNode]) {
                    visited[nextNode] = true;
                    pq.push({nextNode, nextDist});
                } else {
                    // 이미 방문했지만 더 짧은 경로를 찾은 경우
                    pq.push({nextNode, nextDist});
                }
            }
        }
    }
}

//===================================================================
// 2. 거리 비교만으로 중복 방지 + 방문 배열 미사용 (BFS1 스타일)
//===================================================================
void dijkstra_DistanceCheck_NoVisited(int start, int target) {
    priority_queue<Edge> pq;
    
    // 시작 노드 초기화
    dist[start] = 0;
    pq.push({start, 0});
    
    while (!pq.empty()) {
        auto curr = pq.top(); pq.pop();
        
        // 현재 알려진 최단 거리보다 큰 경우 스킵
        if (curr.cost > dist[curr.to]) continue;
        
        // 목표 노드에 도달한 경우
        if (curr.to == target) {
            reconstructPath(start, target);
            return;
        }
        
        // 인접 노드 탐색
        for (const auto& next : graph[curr.to]) {
            int nextNode = next.to;
            int nextDist = curr.cost + next.cost;
            
            // 새 경로가 더 짧은 경우 업데이트 및 큐에 추가
            if (nextDist < dist[nextNode]) {
                dist[nextNode] = nextDist;
                parent[nextNode] = curr.to;
                pq.push({nextNode, nextDist});
            }
        }
    }
}

//===================================================================
// 3. 큐에서 꺼낸 후 방문 표시 + 방문 배열 사용 (전통적 다익스트라)
//===================================================================
void dijkstra_MarkAfterDequeue_WithVisited(int start, int target) {
    priority_queue<Edge> pq;
    
    // 시작 노드 초기화
    dist[start] = 0;
    pq.push({start, 0});
    
    while (!pq.empty()) {
        auto curr = pq.top(); pq.pop();
        
        // 이미 방문한 노드면 스킵
        if (visited[curr.to]) continue;
        
        // 방문 처리
        visited[curr.to] = true;
        
        // 목표 노드에 도달한 경우
        if (curr.to == target) {
            reconstructPath(start, target);
            return;
        }
        
        // 인접 노드 탐색
        for (const auto& next : graph[curr.to]) {
            int nextNode = next.to;
            int nextDist = curr.cost + next.cost;
            
            // 방문하지 않은 노드 중 더 짧은 경로를 발견한 경우 업데이트
            if (!visited[nextNode] && nextDist < dist[nextNode]) {
                dist[nextNode] = nextDist;
                parent[nextNode] = curr.to;
                pq.push({nextNode, nextDist});
            }
        }
    }
}

//===================================================================
// 4. 거리 갱신 위주 + 방문 배열 미사용 (동적 그래프용)
//===================================================================
void dijkstra_PureDistanceUpdate_NoVisited(int start, int target) {
    priority_queue<Edge> pq;
    
    // 시작 노드 초기화
    dist[start] = 0;
    pq.push({start, 0});
    
    while (!pq.empty()) {
        auto curr = pq.top(); pq.pop();
        
        // 현재 알려진 최단 거리보다 큰 경우 스킵
        if (curr.cost > dist[curr.to]) continue;
        
        // 목표 노드에 도달한 경우
        if (curr.to == target) {
            reconstructPath(start, target);
            return;
        }
        
        // 인접 노드 탐색
        for (const auto& next : graph[curr.to]) {
            int nextNode = next.to;
            int nextDist = curr.cost + next.cost;
            
            // 더 짧은 경로를 발견한 경우 업데이트
            if (nextDist < dist[nextNode]) {
                dist[nextNode] = nextDist;
                parent[nextNode] = curr.to;
                pq.push({nextNode, nextDist});
            }
        }
    }
}

int main() {
    printf("\n=== 4가지 다익스트라 알고리즘 구현 비교 ===\n");

    // 테스트용 가중치 그래프 생성
    addEdge(0, 1, 4);  addEdge(0, 2, 2);  addEdge(0, 3, 5);
    addEdge(1, 4, 10); addEdge(1, 5, 8);
    addEdge(2, 4, 7);  addEdge(2, 6, 3);
    addEdge(3, 5, 6);  addEdge(3, 6, 12);
    addEdge(4, 7, 5);  addEdge(4, 8, 8);
    addEdge(5, 7, 9);  addEdge(5, 8, 7);
    addEdge(6, 7, 4);  addEdge(6, 8, 6);
    addEdge(7, 8, 2);
    
    int start = 0;
    int target = 8;
    
    // 그래프 구조 출력
    printf("그래프 구조 (노드 -> [인접노드, 비용]):\n");
    for (int i = 0; i <= 8; i++) {
        printf("노드 %d: ", i);
        for (const auto& edge : graph[i]) {
            printf("[%d, %d] ", edge.to, edge.cost);
        }
        printf("\n");
    }
    
    // 1. 큐에 넣기 전 방문 표시 + 방문 배열 사용
    printf("\n*** 방법 1: 큐에 넣기 전 방문 표시 (MarkBeforeQueue) ***\n");
    initGraph();
    dijkstra_MarkBeforeQueue_WithVisited(start, target);
    printPath(target);
    
    // 2. 거리 비교만으로 중복 방지 + 방문 배열 미사용
    printf("\n*** 방법 2: 거리 비교만으로 중복 방지 (DistanceCheck) ***\n");
    initGraph();
    dijkstra_DistanceCheck_NoVisited(start, target);
    printPath(target);
    
    // 3. 큐에서 꺼낸 후 방문 표시 + 방문 배열 사용
    printf("\n*** 방법 3: 큐에서 꺼낸 후 방문 표시 (전통적 다익스트라) ***\n");
    initGraph();
    dijkstra_MarkAfterDequeue_WithVisited(start, target);
    printPath(target);
    
    // 4. 거리 갱신 위주 + 방문 배열 미사용
    printf("\n*** 방법 4: 거리 갱신 위주 (동적 그래프용) ***\n");
    initGraph();
    dijkstra_PureDistanceUpdate_NoVisited(start, target);
    printPath(target);
    
    // 특성 비교
    printf("\n=== 4가지 방식의 특성 비교 ===\n");
    
    printf("\n1. 큐에 넣기 전 방문 표시 (MarkBeforeQueue):\n");
    printf("   - 큐에 노드를 넣기 전에 방문 처리\n");
    printf("   - 이미 방문한 노드도 더 짧은 경로 발견 시 다시 큐에 추가\n");
    printf("   - 방문 표시와 큐 추가 로직이 분리되어 있음\n");
    printf("   - 적용: 방문 후 추가 처리가 필요한 복잡한 그래프 문제\n");
    
    printf("\n2. 거리 비교만으로 중복 방지 (DistanceCheck):\n");
    printf("   - 큐에서 꺼낸 노드의 거리가 현재 알려진 거리보다 크면 스킵\n");
    printf("   - 방문 여부 대신 거리 비교로 중복 처리 방지\n");
    printf("   - 구현이 간결하고 직관적\n");
    printf("   - 적용: 일반적인 최단 경로 문제\n");
    
    printf("\n3. 큐에서 꺼낸 후 방문 표시 (전통적 다익스트라):\n");
    printf("   - 큐에서 꺼낸 후 방문 처리\n");
    printf("   - 전통적인 다익스트라 구현에 가까움\n");
    printf("   - 각 노드는 최대 한 번만 처리됨\n");
    printf("   - 적용: 효율성이 중요한 대규모 그래프 문제\n");
    
    printf("\n4. 거리 갱신 위주 (PureDistanceUpdate):\n");
    printf("   - 방문 여부 대신 순수하게 거리 갱신에 집중\n");
    printf("   - 가장 간결한 구현\n");
    printf("   - 동적 그래프에 적합\n");
    printf("   - 적용: 간선 가중치가 변할 수 있는 문제\n");
    
    printf("\n코딩테스트에서는 일반적으로 방법 3(전통적 다익스트라) 또는\n");
    printf("방법 2(거리 비교만으로 중복 방지)가 가장 널리 사용되고 효율적입니다.\n");
    
    return 0;
}
```
