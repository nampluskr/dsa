#pragma once
#include "../vector/vector.h"
#include "hash.h"
#include <cstring>

const int MAX_TABLE = 17;

template<typename K, typename V>
struct UnorderedMap {
    struct Node {
        K key;
        V value;
    };
    Vector<Node> table[MAX_TABLE];
    Hash<K> hashfunc;
    Compare<K> compare;

    ~UnorderedMap() { clear(); }
    void clear() {
        for (int i = 0; i < MAX_TABLE; i++)
            table[i].clear();
    }
    Node* find(const K& key) {
        int hash = hashfunc(key) % MAX_TABLE;
        auto& bucket = table[hash];
        for (int i = 0; i < bucket.size(); i++)
            if (compare(bucket[i].key, key)) return &bucket[i];
        return nullptr;
    }
    void emplace(const K& key, const V& value) {
        int hash = hashfunc(key) % MAX_TABLE;
        auto& bucket = table[hash];

        // 이미 존재하는 키인지 확인
        for (int i = 0; i < bucket.size(); i++) {
            if (compare(bucket[i].key, key)) {
                bucket[i].value = value;   // 기존 값 업데이트
                return;
            }
        }
        // 새 노드 생성 후 버킷에 추가
        bucket.push_back({key, value});
    }
    V& operator[](const K& key) {
        Node* node = find(key);
        if (node != nullptr) return node->value;
        emplace(key, V());      // 키가 없으면 기본값으로 삽입
        return find(key)->value;
    }
    Node* end() { return nullptr; }
};