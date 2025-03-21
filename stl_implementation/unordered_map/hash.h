#pragma once
#include <cstring>

// 기본 해시 함수 템플릿
template<typename T>
struct Hash;

// 정수형 특수화
template<>
struct Hash<int> {
    unsigned int operator()(const int& key) const {
        return static_cast<unsigned int>(key);
    }
};

// 문자열 특수화 (djb2 알고리즘)
template<>
struct Hash<const char*> {
    unsigned int operator()(const char* key) const {
        unsigned int hash = 5381;
        int c;
        while ((c = *key++)) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash;
    }
};

// 기본 템플릿: operator== 사용
template<typename T>
struct Compare {
    bool operator()(const T &a, const T &b) const {
        return a == b;
    }
};

int my_strcmp(const char *a, const char *b) {
    while (*a && (*a == *b)) a++, b++;
    return (unsigned char)*a - (unsigned char)*b;
}

// const char* 에 대한 동등 비교: strcmp 사용
template<>
struct Compare<const char*> {
    bool operator()(const char *a, const char *b) const {
        return my_strcmp(a, b) == 0;
    }
};