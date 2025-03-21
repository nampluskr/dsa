#include <cstdio>
#include "stack.h"

int main() {
    // 정수형 스택 테스트
    Stack<int> s;
    
    // 데이터 추가 테스트
    printf("데이터 추가 테스트:\n");
    for (int i = 1; i <= 10; i++) {
        s.push(i * 10);
        printf("스택에 %d 추가, 현재 크기: %d, 맨 위 요소: %d\n", 
               i * 10, s.size(), s.top());
    }
    printf("\n");
    
    // pop 테스트
    printf("pop 테스트:\n");
    printf("pop 전 스택 크기: %d\n", s.size());
    
    for (int i = 0; i < 5; i++) {
        int topValue = s.top();
        s.pop();
        printf("pop된 값: %d, 현재 스택 크기: %d\n", topValue, s.size());
        if (!s.empty()) {
            printf("새로운 맨 위 요소: %d\n", s.top());
        }
    }
    printf("\n");
    
    // 추가 push 테스트 (동적 크기 조정 확인)
    printf("추가 push 테스트:\n");
    for (int i = 11; i <= 20; i++) {
        s.push(i * 10);
        printf("스택에 %d 추가, 현재 크기: %d\n", i * 10, s.size());
    }
    printf("\n");
    
    // 스택 내용물 전체 출력 (pop하면서)
    printf("스택의 모든 내용물 출력 (LIFO 순서):\n");
    while (!s.empty()) {
        printf("%d ", s.top());
        s.pop();
    }
    printf("\n\n");
    
    // 스택이 비었는지 확인
    printf("스택이 비었나요? %s\n", s.empty() ? "예" : "아니오");
    
    // clear 테스트
    s.push(100);
    s.push(200);
    printf("push 후 스택 크기: %d\n", s.size());
    s.clear();
    printf("clear 후 스택 크기: %d\n", s.size());
    
    return 0;
}