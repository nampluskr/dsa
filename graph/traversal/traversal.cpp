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

// 유틸리티 함수
void addEdge(int start, int end, int cost) {
    graph[start].push_back({end, cost});
}

void initPath() {
    for (int i = 0; i < MAX_N; i++) visited[i] = false;
    path.clear();
}

void visitNode(int curr) {
    visited[curr] = true;
    path.push_back(curr);
}

void printPath() {
    printf(">> ");
    for (int node : path) printf("%d -> ", node);
    printf("Finished!\n");
}

//===================================================================
// 1. 그래프 순회(Traversal) 알고리즘 - 연결된 모든 노드 방문
//===================================================================

// DFS 순회 - 전통적 방식 (Pre-Order)
void dfsTraversal_PreOrder(int curr) {
    if (visited[curr]) return;
    visitNode(curr);

    for (const auto& next : graph[curr])
        if (!visited[next.to])
            dfsTraversal_PreOrder(next.to);
}

// DFS 순회 - 자식 중심 방식
void dfsTraversal_ChildrenFirst(int curr) {
    for (const auto& next : graph[curr])
        if (!visited[next.to]) {
            visitNode(next.to);
            dfsTraversal_ChildrenFirst(next.to);
        }
}

// BFS 순회 - 전통적 방식
void bfsTraversal_LevelOrder(int start) {
    queue<int> q;
    
    visitNode(start);
    q.push(start);
    
    while (!q.empty()) {
        int curr = q.front(); q.pop();
        
        for (const auto& next : graph[curr]) {
            if (!visited[next.to]) {
                visitNode(next.to);
                q.push(next.to);
            }
        }
    }
}

// BFS 순회 - 후처리 방식
void bfsTraversal_QueueFirst(int start) {
    queue<int> q;
    q.push(start);
    
    while (!q.empty()) {
        int curr = q.front(); q.pop();
        
        if (visited[curr]) continue;
        visitNode(curr);
        
        for (const auto& next : graph[curr])
            if (!visited[next.to])
                q.push(next.to);
    }
}

int main()
{
    int start = 0;

    printf("\n=== 그래프 순회(Traversal) 테스트 ===\n");
    
    // 테스트용 그래프 생성
    addEdge(0, 1, 1); addEdge(0, 2, 1);
    addEdge(1, 3, 1); addEdge(1, 4, 1);
    addEdge(2, 5, 1); addEdge(2, 6, 1);
    
    printf("\n*** DFS 순회 (Pre-Order)\n");
    initPath();
    dfsTraversal_PreOrder(start);
    printPath();
    
    printf("\n*** DFS 순회 (Children First)\n");
    initPath();
    visitNode(start); // 시작 노드 방문 처리
    dfsTraversal_ChildrenFirst(start);
    printPath();
    
    printf("\n*** BFS 순회 (Level Order)\n");
    initPath();
    bfsTraversal_LevelOrder(start);
    printPath();
    
    printf("\n*** BFS 순회 (Queue First)\n");
    initPath();
    bfsTraversal_QueueFirst(start);
    printPath();

    return 0;
}