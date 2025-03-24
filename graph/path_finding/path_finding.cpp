#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

const int MAX_N = 101;

struct Edge {
    int to, cost;
};
vector<Edge> graph[MAX_N];
bool visited[MAX_N];
vector<int> path;
int parent[MAX_N];  // 각 노드의 부모 노드 저장

// 유틸리티 함수
void addEdge(int start, int end, int cost) {
    graph[start].push_back({end, cost});
}

void initPath() {
    for (int i = 0; i < MAX_N; i++) {
        visited[i] = false;
        parent[i] = -1;
    }
    path.clear();
}

void visitNode(int curr) {
    visited[curr] = true;
    path.push_back(curr);
}

void printPath() {
    printf("경로: ");
    for (int node : path) printf("%d -> ", node);
    printf("Finished!\n");
}

// parent 배열을 사용하여 시작 노드부터 타겟 노드까지의 최단 경로 재구성
void reconstructPath(int parent[], int start, int target) {
    // 기존 path를 지우고 새로운 경로로 대체
    path.clear();

    // 타겟에서 시작 노드로 거슬러 올라가며 경로 기록
    vector<int> reversePath;
    for (int at = target; at != -1; at = parent[at]) {
        reversePath.push_back(at);
        if (at == start) break; // 시작 노드에 도달하면 중단
    }

    // 경로를 시작 노드에서 타겟 노드 순서로 뒤집기
    for (int i = reversePath.size() - 1; i >= 0; i--) {
        path.push_back(reversePath[i]);
    }
}

//===================================================================
// 경로 찾기(Pathfinding) 알고리즘 - 목표 노드까지의 경로 탐색
//===================================================================

// DFS 경로 찾기 - 전통적 방식 (부모 노드 추적 기능 추가)
bool dfsPathfinding_PreOrder(int curr, int target) {
    if (visited[curr]) return false;
    visitNode(curr);

    // 목표 노드 도달 시 true 반환
    if (curr == target) return true;

    for (const auto& next : graph[curr]) {
        if (!visited[next.to]) {
            parent[next.to] = curr;  // 부모 노드 기록 (불필요)
            if (dfsPathfinding_PreOrder(next.to, target))
                return true;
        }
    }

    // 목표 노드를 찾지 못하면 현재 노드를 경로에서 제거 (백트래킹)
    path.pop_back();
    return false;
}

// DFS 경로 찾기 - 자식 중심 방식 (부모 노드 추적 기능 추가)
bool dfsPathfinding_ChildrenFirst(int curr, int target) {
    // 현재 노드가 목표면 true 반환
    if (curr == target) return true;

    for (const auto& next : graph[curr]) {
        if (!visited[next.to]) {
            parent[next.to] = curr;  // 부모 노드 기록 (불필요)
            visitNode(next.to);

            // 다음 노드가 목표 노드로 가는 경로면 true 반환
            if (next.to == target || dfsPathfinding_ChildrenFirst(next.to, target))
                return true;

            // 이 경로로는 목표에 도달할 수 없으면 경로에서 제거
            path.pop_back();
        }
    }

    return false;
}

// BFS 경로 찾기 - 전통적 방식
bool bfsPathfinding_LevelOrder(int start, int target) {
    queue<int> q;

    visitNode(start);
    q.push(start);

    while (!q.empty()) {
        int curr = q.front(); q.pop();

        // 목표 노드 발견
        if (curr == target) return true;

        for (const auto& next : graph[curr]) {
            if (!visited[next.to]) {
                parent[next.to] = curr; // 부모 노드 기록
                visitNode(next.to);
                q.push(next.to);
            }
        }
    }

    return false;
}

// BFS 경로 찾기 - 후처리 방식
bool bfsPathfinding_QueueFirst(int start, int target) {
    queue<int> q;

    q.push(start);

    while (!q.empty()) {
        int curr = q.front(); q.pop();

        if (visited[curr]) continue;
        visitNode(curr);

        // 목표 노드 발견
        if (curr == target) return true;

        for (const auto& next : graph[curr]) {
            if (!visited[next.to]) {
                parent[next.to] = curr; // 부모 노드 기록
                q.push(next.to);
            }
        }
    }

    return false;
}

int main()
{
    int start = 0;
    int target = 8;

    printf("\n=== 경로 찾기(Pathfinding) 테스트 ===\n");

    // 테스트용 그래프 초기화
    for (int i = 0; i < MAX_N; i++)
        graph[i].clear();

    // 테스트용 그래프 생성
    addEdge(0, 1, 1); addEdge(0, 2, 1);
    addEdge(1, 3, 1); addEdge(1, 4, 1);
    addEdge(2, 5, 1); addEdge(2, 6, 1);
    addEdge(5, 7, 1); addEdge(7, 8, 1);

    printf("\n*** DFS 경로 찾기 (Pre-Order)\n");
    initPath();
    bool found1 = dfsPathfinding_PreOrder(start, target);
    if (found1) {
        printf("목표 노드 %d에 도달!\n", target);
        printf("탐색 순서 경로:\n");
        printPath();
        printf("parent 배열을 통한 실제 경로:\n");
        reconstructPath(parent, start, target);
        printPath();
    } else {
        printf("목표 노드 %d에 도달할 수 없음\n", target);
    }

    printf("\n*** DFS 경로 찾기 (Children First)\n");
    initPath();
    visitNode(start); // 시작 노드 방문 처리
    parent[start] = -1; // 시작 노드의 부모는 없음
    bool found2 = dfsPathfinding_ChildrenFirst(start, target);
    if (found2) {
        printf("목표 노드 %d에 도달!\n", target);
        printf("탐색 순서 경로:\n");
        printPath();
        printf("parent 배열을 통한 실제 경로:\n");
        reconstructPath(parent, start, target);
        printPath();
    } else {
        printf("목표 노드 %d에 도달할 수 없음\n", target);
    }

    printf("\n*** BFS 경로 찾기 (Level Order) - 최단 경로\n");
    initPath();
    bool found3 = bfsPathfinding_LevelOrder(start, target);
    if (found3) {
        printf("목표 노드 %d에 도달!\n", target);
        printf("탐색 순서 경로:\n");
        printPath();
        printf("parent 배열을 통한 최단 경로:\n");
        reconstructPath(parent, start, target);
        printPath();
    } else {
        printf("목표 노드 %d에 도달할 수 없음\n", target);
    }

    printf("\n*** BFS 경로 찾기 (Queue First) - 최단 경로\n");
    initPath();
    bool found4 = bfsPathfinding_QueueFirst(start, target);
    if (found4) {
        printf("목표 노드 %d에 도달!\n", target);
        printf("탐색 순서 경로:\n");
        printPath();
        printf("parent 배열을 통한 최단 경로:\n");
        reconstructPath(parent, start, target);
        printPath();
    } else {
        printf("목표 노드 %d에 도달할 수 없음\n", target);
    }

    return 0;
}