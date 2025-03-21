#include "vector.h"
#include <cstdio>

void testVector() {
    Vector<int> intVec;             // integer
    Vector<const char*> strVec;     // string (char [])

    // 정수 벡터 테스트
    printf("=== Integer Vector ===\n");
    intVec.push_back(10);
    intVec.push_back(20);
    intVec.push_back(30);

    printf(">> Before: ");
    for (const auto& num : intVec) printf("%d ", num);
    printf("\n");
    
    for (auto& num : intVec) num += 5; 

    printf(">> After: ");
    for (const auto& num : intVec) printf("%d ", num);
    printf("\n");
    
    // 문자열 벡터 테스트
    printf("\n=== String Vector ===\n");
    strVec.push_back("apple");
    strVec.push_back("banana");
    strVec.push_back("orange");
    
    printf(">> Before: ");
    for (const auto& str : strVec) printf("%s ", str);
    printf("\n");

    strVec[0] = "grape";
    strVec[1] = "mango";
    strVec[2] = "strawberry";

    printf(">> After: ");
    for (const auto& str : strVec) printf("%s ", str);
    printf("\n");
}

int main()
{
    testVector();

    return 0;
}