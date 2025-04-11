#include <cstdio>
using namespace std;

const int MAX_DATA = 1000;
const int MAX_TABLE = 5;

struct Data {
    int key;
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

int hashFunc(int key) {
    return key % MAX_TABLE;
}

int find(int key) {
    int hash = hashFunc(key);
    int idx = hashTable[hash];
    while (idx != -1) {
        if (data[idx].key == key && data[idx].isValid) return idx;
        idx = data[idx].next;
    }
    return -1;
}

void insert(int key, int value) {
    int idx = find(key);
    if (idx != -1) { data[idx].value = value; return; }

    int hash = hashFunc(key);
    data[cnt].key = key;
    data[cnt].value = value;
    data[cnt].next = hashTable[hash];
    data[cnt].isValid = true;
    hashTable[hash] = cnt++;
}

void erase(int key) {
    int idx = find(key);
    if (idx == -1) return;
    data[idx].isValid = false;
}

int main()
{
    init();

    insert(111, 1000);
    insert(112, 2000);
    insert(113, 3000);
    insert(114, 4000);
    insert(115, 5000);
    insert(116, 6000);
    insert(117, 7000);
    insert(118, 8000);
    insert(119, 9000);

    erase(113);
    erase(117);
    erase(118);

    for (int i = 0; i < cnt; i++) {
        int idx = find(data[i].key);
        printf("%d, %d, %2d [%d]\n", data[i].key, data[i].value, data[i].next, idx);
    }

    return 0;
}
