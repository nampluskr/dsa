#pragma once

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a < b ? b : a; }

struct RangeMin {
    static const int identity = 0x7FFFFFFF;     // 최대 정수
    int merge(int a, int b) const { return min(a, b); }
};

struct RangeMax {
    static const int identity = 0x80000000;     // 최소 정수
    int merge(int a, int b) const { return max(a, b); }
};

struct RangeSum {
    static const int identity = 0;
    int merge(int a, int b) const { return a + b; }
};

template<typename Operation>
struct SqrtDecomp {
    int* arr, n;                        // 원본 배열, 원본 배열 크기
    int* blocks, blockSize, numBlocks;  // 블록 배열, 한 블록의 크기, 블록 개수
    static const int identity = Operation::identity;
    Operation op;                       // Operation 인스턴스

    SqrtDecomp(int size) {
        n = size;
        arr = new int[n];
        for (int i = 0; i < n; i++) arr[i] = identity;

        blockSize = 1;
        while (blockSize * blockSize < n) blockSize++;  // 블록 크기 계산 (sqrt)

        numBlocks = (n + blockSize - 1) / blockSize;    // 블록 개수 (올림)

        blocks = new int[numBlocks];                    // 블록 초기화 (identity)
        for (int i = 0; i < numBlocks; i++) blocks[i] = identity;
    }
    ~SqrtDecomp() { delete[] arr; delete[] blocks; }

    void build(int* data) {
        for (int i = 0; i < n; i++) arr[i] = data[i];

        for (int i = 0; i < numBlocks; i++) {
            int blockStart = i * blockSize;
            int blockEnd = min(n, (i + 1) * blockSize);

            blocks[i] = identity;
            for (int j = blockStart; j < blockEnd; j++)
                blocks[i] = op.merge(blocks[i], arr[j]);
        }
    }
    void update(int idx, int value) {
        arr[idx] = value;

        int blockIdx = idx / blockSize;
        int left = blockIdx * blockSize;
        int right = min((blockIdx + 1) * blockSize - 1, n - 1);

        blocks[blockIdx] = identity;
        for (int i = left; i <= right; i++)
            blocks[blockIdx] = op.merge(blocks[blockIdx], arr[i]);
    }
    int query(int left, int right) {
        int result = identity;
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++) result = op.merge(result, arr[i]);
            return result;
        }
        for (int i = left; i < (leftBlock + 1) * blockSize; i++)
            result = op.merge(result, arr[i]);

        for (int b = leftBlock + 1; b < rightBlock; b++)
            result = op.merge(result, blocks[b]);

        for (int i = rightBlock * blockSize; i <= right; i++)
            result = op.merge(result, arr[i]);

        return result;
    }
};