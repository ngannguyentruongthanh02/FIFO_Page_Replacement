
#ifndef FIFO_H
#define FIFO_H

#include <iostream>
#include <vector>
#include "Input.h"

using namespace std;

// Cấu trúc lưu kết quả thuật toán FIFO
struct FIFOResult {
    int pageFaults;
    int pageHits;
    vector<vector<int>> frameHistory;
};

// Thực hiện thuật toán FIFO
FIFOResult runFIFO(const InputData& data);

// Hiển thị kết quả thuật toán FIFO
void displayFIFOResult(const InputData& data, const FIFOResult& result);

#endif // FIFO_H
