#include <cstdio>
#include "unordered_map.h"

void test_int_map() {
    printf("===== 정수 키 테스트 =====\n");
    UnorderedMap<int, int> map;

    // 삽입 테스트
    map.emplace(10, 100);
    map.emplace(20, 200);
    map.emplace(30, 300);

    // 조회 테스트
    auto node1 = map.find(10);
    auto node2 = map.find(20);
    auto node3 = map.find(30);
    auto node4 = map.find(40); // 존재하지 않는 키

    printf("key 10 값: %d\n", node1 ? node1->value : -1);
    printf("key 20 값: %d\n", node2 ? node2->value : -1);
    printf("key 30 값: %d\n", node3 ? node3->value : -1);
    printf("key 40 존재 여부: %s\n", map.find(40) == map.end() ? "없음" : "있음");

    // [] 연산자 테스트
    map[40] = 400;  // 새 요소 추가
    map[10] = 1000; // 기존 요소 업데이트

    printf("map[10] = %d\n", map[10]);
    printf("map[40] = %d\n", map[40]);

    // end() 테스트
    printf("find(99) == end()? %s\n", map.find(99) == map.end() ? "예" : "아니오");

    // clear 테스트
    map.clear();
    printf("clear 후 key 10 존재 여부: %s\n", map.find(10) == map.end() ? "없음" : "있음");
}

void test_string_map() {
    printf("\n===== 문자열 키 테스트 =====\n");
    UnorderedMap<const char*, int> map;

    // 삽입 테스트
    map.emplace("apple", 5);
    map.emplace("banana", 6);
    map.emplace("cherry", 6);

    // 조회 테스트
    auto node1 = map.find("apple");
    auto node2 = map.find("banana");
    auto node3 = map.find("cherry");

    printf("key 'apple' 값: %d\n", node1 ? node1->value : -1);
    printf("key 'banana' 값: %d\n", node2 ? node2->value : -1);
    printf("key 'cherry' 값: %d\n", node3 ? node3->value : -1);
    printf("key 'date' 존재 여부: %s\n", map.find("date") == map.end() ? "없음" : "있음");

    // [] 연산자 테스트
    map["date"] = 4;    // 새 요소 추가
    map["apple"] = 10;  // 기존 요소 업데이트

    printf("map['apple'] = %d\n", map["apple"]);
    printf("map['date'] = %d\n", map["date"]);
    printf("key 'date' 존재 여부: %s\n", map.find("date") == map.end() ? "없음" : "있음");
}

void test_int_vector_map() {
    printf("\n===== 정수 -> 벡터 맵핑 테스트 =====\n");
    UnorderedMap<int, Vector<int>> vecMap;

    // key 1 에 대한 Vector<int>에 값 추가
    vecMap[1].push_back(10);
    vecMap[1].push_back(20);

    // key 2 에 대한 Vector<int>에 값 추가
    vecMap[2].push_back(30);
    vecMap[2].push_back(40);

    // vecMap의 값 출력
    printf("vecMap[1] size = %d\n", vecMap[1].size());
    printf("vecMap[1][0] = %d\n", vecMap[1][0]);
    printf("vecMap[1][1] = %d\n", vecMap[1][1]);

    printf("vecMap[2] size = %d\n", vecMap[2].size());
    printf("vecMap[2][0] = %d\n", vecMap[2][0]);
    printf("vecMap[2][1] = %d\n", vecMap[2][1]);
}

void test_str_vector_map() {
    printf("\n===== 문자열 -> 벡터 맵핑 테스트 =====\n");
    UnorderedMap<const char*, Vector<const char*>> charVecMap;

    // "fruits" 키에 여러 문자열 추가
    charVecMap["fruits"].push_back("apple");
    charVecMap["fruits"].push_back("banana");
    charVecMap["fruits"].push_back("cherry");

    // "colors" 키에 여러 문자열 추가
    charVecMap["colors"].push_back("red");
    charVecMap["colors"].push_back("green");
    charVecMap["colors"].push_back("blue");

    // "fruits" 키에 대한 Vector 출력
    printf("Fruits:\n");
    auto& fruits = charVecMap["fruits"];
    for (int i = 0; i < fruits.size(); i++)
        printf("  %s\n", fruits[i]);

    // "colors" 키에 대한 Vector 출력
    printf("Colors:\n");
    auto& colors = charVecMap["colors"];
    for (int i = 0; i < colors.size(); i++)
        printf("  %s\n", colors[i]);
}

int main() {
    test_int_map();
    test_string_map();
    test_int_vector_map();
    test_str_vector_map();

    printf("\n");
    return 0;
}