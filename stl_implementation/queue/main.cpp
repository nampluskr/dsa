#include <cstdio>
#include "queue.h"

int main() {
    // 정수형 큐 테스트
    Queue<int> q;
    
    // 데이터 추가 테스트
    printf("데이터 추가 테스트:\n");
    for (int i = 1; i <= 10; i++) {
        q.push(i * 10);
        printf("큐에 %d 추가, 현재 크기: %d\n", i * 10, q.size());
    }
    printf("\n");
    
    // 큐의 front와 back 확인
    printf("큐의 맨 앞 요소: %d\n", q.front());
    printf("큐의 맨 뒤 요소: %d\n", q.back());
    printf("\n");
    
    // pop 테스트
    printf("pop 테스트:\n");
    printf("pop 전 큐 크기: %d\n", q.size());
    
    for (int i = 0; i < 5; i++) {
        int frontValue = q.front();
        q.pop();
        printf("pop된 값: %d, 현재 큐 크기: %d\n", frontValue, q.size());
    }
    printf("\n");
    
    // 추가 push 테스트
    printf("추가 push 테스트:\n");
    for (int i = 11; i <= 15; i++) {
        q.push(i * 10);
        printf("큐에 %d 추가, 현재 크기: %d\n", i * 10, q.size());
    }
    printf("\n");
    
    // 큐 내용물 전체 출력 (pop하면서)
    printf("큐의 모든 내용물 출력 (FIFO 순서):\n");
    while (!q.empty()) {
        printf("%d ", q.front());
        q.pop();
    }
    printf("\n\n");
    
    // 큐가 비었는지 확인
    printf("큐가 비었나요? %s\n", q.empty() ? "예" : "아니오");
    
    // clear 테스트
    q.push(100);
    q.push(200);
    printf("push 후 큐 크기: %d\n", q.size());
    q.clear();
    printf("clear 후 큐 크기: %d\n", q.size());
    
    // 큐 용량 테스트 (자동 resize 기능)
    printf("\n큐 용량 확장 테스트:\n");
    Queue<int> resizeQ;
    printf("초기 용량의 큐 생성\n");
    
    for (int i = 1; i <= 20; i++) {
        resizeQ.push(i);
        
        // 용량이 2의 거듭제곱인 경우 확인 (용량 확장 확인)
        if ((i & (i - 1)) == 0) {  // i가 2의 거듭제곱인지 확인
            printf("%d개 요소 추가 후 큐 상태, 크기: %d\n", i, resizeQ.size());
        }
    }
    
    // 큐에서 요소 확인
    printf("\n큐의 첫 번째 요소: %d\n", resizeQ.front());
    printf("큐의 마지막 요소: %d\n", resizeQ.back());
    
    return 0;
}