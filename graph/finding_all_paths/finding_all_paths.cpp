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
vector<int> currentPath;        // 현재 탐색 중인 경로
vector<vector<int>> allPaths;   // 발견된 모든 경로 저장

// 유틸리티 함수
void addEdge(int start, int end, int cost) {
    graph[start].push_back({end, cost});
}

void initGraph() {
    for (int i = 0; i < MAX_N; i++) {
        graph[i].clear();
        visited[i] = false;
    }
    currentPath.clear();
    allPaths.clear();
}

// 경로 출력 함수
void printPath(const vector<int>& path) {
    printf("경로: ");
    for (size_t i = 0; i < path.size(); i++) {
        printf("%d", path[i]);
        if (i < path.size() - 1)
            printf(" -> ");
    }
    printf("\n");
}

// 모든 경로 출력 함수
void printAllPaths() {
    printf("총 %zu개의 경로를 찾았습니다:\n", allPaths.size());
    for (size_t i = 0; i < allPaths.size(); i++) {
        printf("경로 #%zu: ", i + 1);
        for (size_t j = 0; j < allPaths[i].size(); j++) {
            printf("%d", allPaths[i][j]);
            if (j < allPaths[i].size() - 1)
                printf(" -> ");
        }
        printf("\n");
    }
}

//===================================================================
// 모든 경로 찾기 - 백트래킹 알고리즘들
//===================================================================

// 1. DFS 전통적 방식 (Pre-Order) - 백트래킹으로 모든 경로 찾기
void dfsAllPaths_PreOrder(int curr, int target) {
    // 현재 노드를 방문 처리하고 경로에 추가
    visited[curr] = true;
    currentPath.push_back(curr);

    // 목표 노드에 도달한 경우
    if (curr == target) {
        allPaths.push_back(currentPath);
    } else {
        // 인접 노드 탐색
        for (const auto& next : graph[curr]) {
            if (!visited[next.to]) {
                dfsAllPaths_PreOrder(next.to, target);
            }
        }
    }

    // 백트래킹: 현재 노드를 방문하지 않은 상태로 되돌리고 경로에서 제거
    visited[curr] = false;
    currentPath.pop_back();
}

// 2. DFS 자식 중심 방식 (Children First) - 백트래킹으로 모든 경로 찾기
void dfsAllPaths_ChildrenFirst(int curr, int target) {
    // 목표 노드에 도달한 경우
    if (curr == target) {
        allPaths.push_back(currentPath);
        return;
    }

    // 인접 노드 탐색
    for (const auto& next : graph[curr]) {
        if (!visited[next.to]) {
            // 인접 노드를 방문 처리하고 경로에 추가
            visited[next.to] = true;
            currentPath.push_back(next.to);

            // 재귀 호출
            dfsAllPaths_ChildrenFirst(next.to, target);

            // 백트래킹: 인접 노드를 방문하지 않은 상태로 되돌리고 경로에서 제거
            visited[next.to] = false;
            currentPath.pop_back();
        }
    }
}

// 3. BFS 레벨 순서 방식 (Level Order) - 백트래킹으로 모든 경로 찾기
void bfsAllPaths_LevelOrder(int start, int target) {
    struct QueueItem {
        int node;
        vector<int> path;
        vector<bool> vis;
    };
    queue<QueueItem> q;

    // 시작 노드 설정
    vector<bool> initialVisited(MAX_N, false);
    initialVisited[start] = true;
    vector<int> initialPath = { start };

    q.push({start, initialPath, initialVisited});

    while (!q.empty()) {
        QueueItem current = q.front(); q.pop();

        int curr = current.node;

        // 목표 노드에 도달한 경우
        if (curr == target) {
            allPaths.push_back(current.path);
            continue;
        }

        // 인접 노드 탐색
        for (const auto& next : graph[curr]) {
            if (!current.vis[next.to]) {
                // 새로운 방문 상태와 경로 복사
                vector<bool> newVisited = current.vis;
                vector<int> newPath = current.path;

                // 인접 노드 방문 처리 및 경로에 추가
                newVisited[next.to] = true;
                newPath.push_back(next.to);

                // 큐에 추가
                q.push({next.to, newPath, newVisited});
            }
        }
    }
}

// 4. BFS 큐 우선 방식 (Queue First) - 백트래킹으로 모든 경로 찾기
void bfsAllPaths_QueueFirst(int start, int target) {
    struct QueueItem {
        int node;
        vector<int> path;
        vector<bool> vis;
    };
    queue<QueueItem> q;

    // 시작 노드 설정
    vector<bool> initialVisited(MAX_N, false);
    vector<int> initialPath = { start };

    q.push({start, initialPath, initialVisited});

    while (!q.empty()) {
        QueueItem current = q.front(); q.pop();

        int curr = current.node;

        // 현재 노드가 이미 방문한 노드인지 확인
        if (current.vis[curr]) continue;

        // 방문 처리
        vector<bool> newVisited = current.vis;
        newVisited[curr] = true;

        // 목표 노드에 도달한 경우
        if (curr == target) {
            allPaths.push_back(current.path);
            continue;
        }

        // 인접 노드 탐색
        for (const auto& next : graph[curr]) {
            if (!newVisited[next.to]) {
                // 새로운 경로 복사
                vector<int> newPath = current.path;
                newPath.push_back(next.to);

                // 큐에 추가
                q.push({next.to, newPath, newVisited});
            }
        }
    }
}

int main()
{
    printf("\n=== 모든 경로 찾기 알고리즘 비교 ===\n");

    // 테스트용 그래프 생성 - 여러 경로가 존재하도록 간선 구성
    addEdge(0, 1, 1); addEdge(0, 2, 1);
    addEdge(1, 3, 1); addEdge(1, 5, 1);
    addEdge(2, 4, 1); addEdge(2, 5, 1);
    addEdge(3, 6, 1); addEdge(4, 6, 1);
    addEdge(5, 7, 1);
    addEdge(6, 7, 1);
    addEdge(7, 8, 1);

    int start = 0;
    int target = 8;

    // 1. DFS Pre-Order 방식으로 모든 경로 찾기
    printf("\n*** DFS Pre-Order 방식으로 모든 경로 찾기 ***\n");
    allPaths.clear();
    for (int i = 0; i < MAX_N; i++) visited[i] = false;
    currentPath.clear();
    dfsAllPaths_PreOrder(start, target);
    printAllPaths();

    // 2. DFS Children First 방식으로 모든 경로 찾기
    printf("\n*** DFS Children First 방식으로 모든 경로 찾기 ***\n");
    allPaths.clear();
    for (int i = 0; i < MAX_N; i++) visited[i] = false;
    currentPath.clear();

    // 시작 노드 설정
    visited[start] = true;
    currentPath.push_back(start);

    dfsAllPaths_ChildrenFirst(start, target);
    printAllPaths();

    // 3. BFS Level Order 방식으로 모든 경로 찾기
    printf("\n*** BFS Level Order 방식으로 모든 경로 찾기 ***\n");
    allPaths.clear();
    bfsAllPaths_LevelOrder(start, target);
    printAllPaths();

    // 4. BFS Queue First 방식으로 모든 경로 찾기
    printf("\n*** BFS Queue First 방식으로 모든 경로 찾기 ***\n");
    allPaths.clear();
    bfsAllPaths_QueueFirst(start, target);
    printAllPaths();

    return 0;
}