#pragma once

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a < b ? b : a; }

struct RangeMin {
    static const int identity = 0x7FFFFFFF;     // 최대 정수
    int merge(int a, int b) const { return min(a, b); }
    int update(int value, int size) const { return value; }
};

struct RangeMax {
    static const int identity = 0x80000000;     // 최소 정수
    int merge(int a, int b) const { return max(a, b); }
    int update(int value, int size) const { return value; }
};

struct RangeSum {
    static const int identity = 0;
    int merge(int a, int b) const { return a + b; }
    int update(int value, int size) const { return value * size; }
};

template<typename Operation>
struct SqrtDecompLazy {
    int* arr, n;                        // 원본 배열, 원본 배열 크기
    int* blocks, blockSize, numBlocks;  // 블록 배열, 한 블록의 크기, 블록 개수

    int* lazyValue;                     // 지연된 업데이트 값
    bool* lazyExist;                    // 지연된 업데이트 존재 여부

    static const int identity = Operation::identity;
    Operation op;                       // Operation 인스턴스

    SqrtDecompLazy(int size) {
        n = size;
        arr = new int[n];
        for (int i = 0; i < n; i++) arr[i] = 0;  // 기본값 0으로 초기화

        blockSize = 1;
        while (blockSize * blockSize < n) blockSize++;  // 블록 크기 계산 (sqrt)

        numBlocks = (n + blockSize - 1) / blockSize;    // 블록 개수 (올림)

        blocks = new int[numBlocks];                    // 블록 초기화 (identity)
        for (int i = 0; i < numBlocks; i++) blocks[i] = identity;

        // Lazy 업데이트 관련 배열 초기화
        lazyValue = new int[numBlocks];
        lazyExist = new bool[numBlocks];
        for (int i = 0; i < numBlocks; i++) {
            lazyValue[i] = 0;
            lazyExist[i] = false;
        }
    }

    ~SqrtDecompLazy() {
        delete[] arr;
        delete[] blocks;
        delete[] lazyValue;
        delete[] lazyExist;
    }

    void build(int* data) {
        for (int i = 0; i < n; i++) arr[i] = data[i];

        // 모든 지연 업데이트 초기화
        for (int i = 0; i < numBlocks; i++) {
            lazyValue[i] = 0;
            lazyExist[i] = false;
        }
        for (int i = 0; i < numBlocks; i++) {
            int blockStart = i * blockSize;
            int blockEnd = min((i + 1) * blockSize - 1, n - 1);

            blocks[i] = identity;
            for (int j = blockStart; j <= blockEnd; j++)
                blocks[i] = op.merge(blocks[i], arr[j]);
        }
    }

    // 단일 위치 업데이트
    void update(int idx, int value) {
        int blockIdx = idx / blockSize;
        propagate(blockIdx);
        arr[idx] = value;
        
        // 블록 값 재계산
        int blockStart = blockIdx * blockSize;
        int blockEnd = min((blockIdx + 1) * blockSize - 1, n - 1);
        
        blocks[blockIdx] = identity;
        for (int i = blockStart; i <= blockEnd; i++)
            blocks[blockIdx] = op.merge(blocks[blockIdx], arr[i]);
    }

    // 구간 업데이트: [left, right] 범위의 모든 값에 value 추가
    void update(int left, int right, int value) {
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        // 왼쪽 블록 부분 업데이트
        if (left % blockSize != 0 || leftBlock == rightBlock) {
            propagate(leftBlock);
            int blockStart = leftBlock * blockSize;
            int blockEnd = min((leftBlock + 1) * blockSize - 1, n - 1);

            // 블록 내 범위 업데이트
            for (int i = blockStart; i <= blockEnd; i++)
                if (i >= left && i <= right) arr[i] += value;

            // 블록 값 재계산
            blocks[leftBlock] = identity;
            for (int i = blockStart; i <= blockEnd; i++)
                blocks[leftBlock] = op.merge(blocks[leftBlock], arr[i]);
        }

        // 오른쪽 블록 부분 업데이트 (leftBlock != rightBlock일 때만)
        if (leftBlock != rightBlock && (right + 1) % blockSize != 0) {
            propagate(rightBlock);
            int blockStart = rightBlock * blockSize;
            int blockEnd = min((rightBlock + 1) * blockSize - 1, n - 1);

            // 블록 내 범위 업데이트
            for (int i = blockStart; i <= blockEnd; i++)
                if (i >= left && i <= right) arr[i] += value;

            // 블록 값 재계산
            blocks[rightBlock] = identity;
            for (int i = blockStart; i <= blockEnd; i++)
                blocks[rightBlock] = op.merge(blocks[rightBlock], arr[i]);
        }
        // 완전히 포함되는 중간 블록들은 lazy 업데이트
        for (int b = leftBlock + 1; b < rightBlock; b++) {
            lazyValue[b] += value;
            lazyExist[b] = true;
        }
    }

    // 구간 쿼리: [left, right] 범위의 결과 반환
    int query(int left, int right) {
        int result = identity;
        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        // 동일한 블록에 있는 경우
        if (leftBlock == rightBlock) {
            propagate(leftBlock);  // 지연 업데이트 적용
            for (int i = left; i <= right; i++)
                result = op.merge(result, arr[i]);
            return result;
        }

        // 왼쪽 블록 부분 계산
        propagate(leftBlock);
        for (int i = left; i < (leftBlock + 1) * blockSize && i < n; i++)
            result = op.merge(result, arr[i]);

        // 중간 블록들 계산
        for (int b = leftBlock + 1; b < rightBlock; b++) {
            if (lazyExist[b]) {
                // 지연된 업데이트가 있는 경우 블록 전체 값 계산
                int blockStart = b * blockSize;
                int blockEnd = min((b + 1) * blockSize - 1, n - 1);
                int blockLength = blockEnd - blockStart + 1;
                result = op.merge(result, blocks[b] + op.update(lazyValue[b], blockLength));
            } else {
                // 지연된 업데이트가 없는 경우 블록 값 그대로 사용
                result = op.merge(result, blocks[b]);
            }
        }

        // 오른쪽 블록 부분 계산
        propagate(rightBlock);
        for (int i = rightBlock * blockSize; i <= right && i < n; i++)
            result = op.merge(result, arr[i]);

        return result;
    }

private:
    void propagate(int blockIdx) {
        if (lazyExist[blockIdx]) {
            int blockStart = blockIdx * blockSize;
            int blockEnd = min((blockIdx + 1) * blockSize - 1, n - 1);
            int blockLength = blockEnd - blockStart + 1;

            // 블록 값 업데이트
            blocks[blockIdx] += op.update(lazyValue[blockIdx], blockLength);

            // 원본 배열 업데이트
            for (int i = blockStart; i <= blockEnd; i++)
                arr[i] += lazyValue[blockIdx];

            // 지연 업데이트 초기화
            lazyValue[blockIdx] = 0;
            lazyExist[blockIdx] = false;
        }
    }
};