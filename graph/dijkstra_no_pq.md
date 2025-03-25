```cpp
#include <stdio.h>
#include <vector>
#include <limits>
using namespace std;

const int MAX_N = 101;
const int INF = numeric_limits<int>::max();

struct Edge {
    int to, cost;
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

// 방문하지 않은 노드 중 최소 거리를 가진 노드 찾기 (visited 배열 사용)
int getMinDistNodeWithVisited(int n) {
    int minDist = INF;
    int minNode = -1;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] < minDist) {
            minDist = dist[i];
            minNode = i;
        }
    }
    
    return minNode;
}

// 처리되지 않은 노드 중 최소 거리를 가진 노드 찾기 (visited 배열 미사용)
int getMinDistNodeWithoutVisited(int n) {
    int minDist = INF;
    int minNode = -1;
    
    for (int i = 0; i < n; i++) {
        // 거리가 INF가 아닌 노드는 아직 완전히 처리되지 않은 것으로 간주
        if (dist[i] < minDist && dist[i] != -1) {  // -1은 이미 처리된 노드 표시
            minDist = dist[i];
            minNode = i;
        }
    }
    
    return minNode;
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
    if (dist[target] == INF) {
        printf("경로가 존재하지 않습니다.\n");
        return;
    }

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
// 방법 1: visited 배열을 사용하는 다익스트라 (우선순위 큐 없음)
//===================================================================
void dijkstraWithVisited(int start, int target, int n) {
    // 시작 노드 초기화
    dist[start] = 0;
    
    for (int i = 0; i < n; i++) {
        // 방문하지 않은 노드 중 최소 거리를 가진 노드 선택
        int current = getMinDistNodeWithVisited(n);
        
        // 모든 노드가 방문되었거나 도달할 수 없는 경우
        if (current == -1) break;
        
        // 목표 노드에 도달한 경우
        if (current == target) {
            reconstructPath(start, target);
            return;
        }
        
        // 현재 노드를 방문 처리
        visited[current] = true;
        
        // 인접 노드 탐색
        for (const auto& next : graph[current]) {
            int nextNode = next.to;
            int nextDist = dist[current] + next.cost;
            
            // 새 경로가 더 짧은 경우 업데이트
            if (!visited[nextNode] && nextDist < dist[nextNode]) {
                dist[nextNode] = nextDist;
                parent[nextNode] = current;
            }
        }
    }
}

//===================================================================
// 방법 2: visited 배열을 사용하지 않는 다익스트라 (우선순위 큐 없음)
//===================================================================
void dijkstraWithoutVisited(int start, int target, int n) {
    // 시작 노드 초기화
    dist[start] = 0;
    
    for (int i = 0; i < n; i++) {
        // 처리되지 않은 노드 중 최소 거리를 가진 노드 선택
        int current = getMinDistNodeWithoutVisited(n);
        
        // 모든 노드가 처리되었거나 도달할 수 없는 경우
        if (current == -1) break;
        
        // 목표 노드에 도달한 경우
        if (current == target) {
            reconstructPath(start, target);
            return;
        }
        
        // 현재 노드의 거리값을 -1로 설정하여 처리 완료 표시
        int currentDist = dist[current];
        dist[current] = -1;  // 특수 값으로 처리된 노드 표시
        
        // 인접 노드 탐색
        for (const auto& next : graph[current]) {
            int nextNode = next.to;
            int nextDist = currentDist + next.cost;
            
            // dist[nextNode]가 -1이 아니고(아직 처리되지 않음) 더 짧은 경로를 발견한 경우
            if (dist[nextNode] != -1 && nextDist < dist[nextNode]) {
                dist[nextNode] = nextDist;
                parent[nextNode] = current;
            }
        }
    }
    
    // 목표 노드가 처리되었으면 경로 재구성
    if (dist[target] == -1) {
        // 목표 노드가 처리되었으므로, 실제 거리는 별도로 저장 필요
        reconstructPath(start, target);
    }
}

int main() {
    printf("\n=== 우선순위 큐 없는 다익스트라 알고리즘 비교 ===\n");

    // 테스트용 가중치 그래프 생성
    addEdge(0, 1, 4);  addEdge(0, 2, 2);  addEdge(0, 3, 5);
    addEdge(1, 4, 10); addEdge(1, 5, 8);
    addEdge(2, 4, 7);  addEdge(2, 6, 3);
    addEdge(3, 5, 6);  addEdge(3, 6, 12);
    addEdge(4, 7, 5);
    addEdge(5, 7, 9);
    addEdge(6, 7, 4);
    
    int start = 0;
    int target = 7;
    int n = 8;  // 그래프의 노드 수
    
    // 그래프 구조 출력
    printf("그래프 구조 (노드 -> [인접노드, 비용]):\n");
    for (int i = 0; i < n; i++) {
        printf("노드 %d: ", i);
        for (const auto& edge : graph[i]) {
            printf("[%d, %d] ", edge.to, edge.cost);
        }
        printf("\n");
    }
    
    // 1. visited 배열을 사용하는 다익스트라
    printf("\n*** 방법 1: visited 배열 사용 다익스트라 ***\n");
    initGraph();
    dijkstraWithVisited(start, target, n);
    printPath(target);
    
    // 실제 구현에서는 dijkstraWithoutVisited 사용 시 dist 배열을 -1로 마킹하면
    // 실제 거리를 잃어버리므로, 실제 거리를 별도 배열에 저장해야 합니다.
    // 이 예제에서는 단순화를 위해 초기화 후 다시 실행합니다.
    
    // 2. visited 배열을 사용하지 않는 다익스트라
    printf("\n*** 방법 2: visited 배열 미사용 다익스트라 ***\n");
    initGraph();
    dijkstraWithoutVisited(start, target, n);
    int finalDist = 0;
    for (int i = 1; i < path.size(); i++) {
        for (const auto& edge : graph[path[i-1]]) {
            if (edge.to == path[i]) {
                finalDist += edge.cost;
                break;
            }
        }
    }
    printf("최단 경로: ");
    for (size_t i = 0; i < path.size(); i++) {
        printf("%d", path[i]);
        if (i < path.size() - 1)
            printf(" -> ");
    }
    printf("\n");
    printf("총 비용: %d\n", finalDist);
    
    // 차이점 설명
    printf("\n=== 두 방식의 차이점 ===\n");
    printf("1. visited 배열 사용 방식:\n");
    printf("   - 별도의 visited 배열로 방문 여부 관리\n");
    printf("   - 방문한 노드는 더 이상 고려하지 않음\n");
    printf("   - 직관적인 구현으로 이해하기 쉬움\n");
    printf("   - dist 배열이 최종 거리 값을 유지\n");
    
    printf("\n2. visited 배열 미사용 방식:\n");
    printf("   - dist 배열에 특수 값(-1)을 사용하여 처리된 노드 표시\n");
    printf("   - 추가 배열 없이 구현 가능하지만, 실제 거리 값을 잃어버림\n");
    printf("   - 실용적인 구현에서는 별도의 배열이나 처리가 필요\n");
    printf("   - 메모리 사용 측면에서 약간 효율적일 수 있음\n");
    
    printf("\n코딩테스트에서는 일반적으로 방법 1(visited 배열 사용)이 더 직관적이며\n");
    printf("추가 처리 없이 최종 거리 정보를 유지할 수 있어 권장됩니다.\n");
    
    return 0;
}
```
