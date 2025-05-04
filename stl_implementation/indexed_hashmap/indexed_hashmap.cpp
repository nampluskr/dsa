#include <cstdio>
using namespace std;

const int MAX_SIZE = 1000;
const int HASH_SIZE = 1007;

struct Data {
    int key;
    int value;
    int next;
    bool isValid;
};
Data data[MAX_SIZE];
int dataCnt;
int removeCnt;
int hashTable[HASH_SIZE];

void init() {
    dataCnt = 0;
    removeCnt = 0;
    for (int i = 0; i < HASH_SIZE; i++) hashTable[i] = -1;
}

int hashFunc(int key) { return key % HASH_SIZE; }

int find(int key) {
    int hashValue = hashFunc(key);
    int idx = hashTable[hashValue];
    
    while (idx != -1) {
        if (data[idx].key == key && data[idx].isValid)
            return idx;
        idx = data[idx].next;
    }
    return -1;  // 키를 찾을 수 없음
}

void insert(int key, int value) {
    int idx = find(key);
    
    // 이미 존재하는 키라면 값 업데이트
    if (idx != -1) {
        data[idx].value = value;
        return;
    }
    
    // 새 데이터 추가
    int hashValue = hashFunc(key);
    data[dataCnt].key = key;
    data[dataCnt].value = value;
    data[dataCnt].next = hashTable[hashValue];
    data[dataCnt].isValid = true;
    hashTable[hashValue] = dataCnt;
    dataCnt++;
}

void remove(int key) {
    int idx = find(key);
    if (idx != -1) {
        data[idx].isValid = false;
        removeCnt++;
    }
}

int size() {
    return dataCnt - removeCnt;
}

void printAll() {
    printf("---- 해시맵 내용 (%d 항목) ----\n", size());
    for (int i = 0; i < dataCnt; i++) {
        if (data[i].isValid)
            printf("키: %d, 값: %d\n", data[i].key, data[i].value);
    }
    printf("-------------------\n");
}

int main()
{
    init();
    
    // 데이터 삽입 테스트
    printf("1. 데이터 삽입 테스트\n");
    insert(5, 500);
    insert(15, 1500);
    insert(25, 2500);
    insert(1005, 10050);  // 5와 해시 충돌 (1005 % 1007 = 5)
    
    // 현재 상태 출력
    printAll();
    
    // 데이터 검색 테스트
    printf("\n2. 데이터 검색 테스트\n");
    int idx1 = find(15);
    if (idx1 != -1)
        printf("키 15를 찾음: 인덱스 = %d, 값 = %d\n", idx1, data[idx1].value);
    else
        printf("키 15를 찾을 수 없음\n");
    
    int idx2 = find(100);
    if (idx2 != -1)
        printf("키 100을 찾음: 인덱스 = %d, 값 = %d\n", idx2, data[idx2].value);
    else
        printf("키 100을 찾을 수 없음\n");
    
    // 해시 충돌이 있는 키 검색
    int idx3 = find(1005);
    if (idx3 != -1)
        printf("키 1005를 찾음: 인덱스 = %d, 값 = %d\n", idx3, data[idx3].value);
    else
        printf("키 1005를 찾을 수 없음\n");
    
    // 데이터 업데이트 테스트
    printf("\n3. 데이터 업데이트 테스트\n");
    insert(15, 1550);  // 키 15의 값 업데이트
    idx1 = find(15);
    if (idx1 != -1)
        printf("키 15 업데이트 후: 값 = %d\n", data[idx1].value);
    
    // 데이터 삭제 테스트
    printf("\n4. 데이터 삭제 테스트\n");
    printf("삭제 전 데이터 수: %d\n", size());
    remove(15);  // 키 15 삭제
    printf("키 15 삭제 후 데이터 수: %d\n", size());
    
    idx1 = find(15);
    if (idx1 != -1)
        printf("키 15를 찾음: 인덱스 = %d, 값 = %d\n", idx1, data[idx1].value);
    else
        printf("키 15를 찾을 수 없음\n");
    
    // 존재하지 않는 키 삭제 시도
    remove(100);
    printf("존재하지 않는 키 100 삭제 시도 후 데이터 수: %d\n", size());
    
    // 최종 상태 출력
    printf("\n5. 최종 상태\n");
    printAll();
    
    return 0;
}