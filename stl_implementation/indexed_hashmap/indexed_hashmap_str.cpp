#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_DATA = 1000;
const int MAX_TABLE = 5;
const int MAX_LEN = 11;

struct Data {
    char key[MAX_LEN];
    int value;
    int next;
    bool isValid;
} data[MAX_DATA];
int cnt;
int hashTable[MAX_TABLE];

void init() {
    cnt = 0;
    for (int i = 0; i < MAX_TABLE; i++) hashTable[i] = -1;
}

int hashFunc(const char *key) {
    int c, hash = 5381;
    while (c = *key++) { hash = (((hash << 5) + hash) + c) % MAX_TABLE; }
    return hash % MAX_TABLE;
}

int find(const char* key) {
    int hash = hashFunc(key);
    int idx = hashTable[hash];
    while (idx != -1) {
        if (strcmp(data[idx].key, key) == 0 && data[idx].isValid) return idx;
        idx = data[idx].next;
    }
    return -1;
}

void insert(const char* key, int value) {
    int idx = find(key);
    if (idx != -1) { data[idx].value = value; return; }

    int hash = hashFunc(key);
    strcpy(data[cnt].key, key);
    data[cnt].value = value;
    data[cnt].next = hashTable[hash];
    data[cnt].isValid = true;
    hashTable[hash] = cnt++;
}

void erase(const char* key) {
    int idx = find(key);
    if (idx == -1) return;
    data[idx].isValid = false;
}

int main()
{
    init();

    insert("aaa", 1000);
    insert("bbb", 2000);
    insert("ccc", 3000);
    insert("ddd", 4000);
    insert("eee", 5000);
    insert("fff", 6000);
    insert("ggg", 7000);
    insert("hhh", 8000);
    insert("iii", 9000);

    erase("ccc");
    erase("ggg");
    erase("hhh");

    for (int i = 0; i < cnt; i++) {
        int idx = find(data[i].key);
        printf("%s, %d, %2d [%d]\n", data[i].key, data[i].value, data[i].next, idx);
    }

    return 0;
}
