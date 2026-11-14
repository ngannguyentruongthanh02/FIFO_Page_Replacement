
#ifndef Statistics_H
#define Statistics_H

#include <iostream>
#include "FIFO.h"

using namespace std;

// Cấu trúc lưu thông tin thống kê
struct Statistics {
    int totalReferences;
    int pageFaults;
    int pageHits;

    double pageFaultRate;
    double pageHitRate;
};

// Tính toán thống kê kết quả FIFO
Statistics calculateStatistics(const FIFOResult& result);

// Hiển thị thống kê kết quả
void displayStatistics(const Statistics& stats);

#endif // STATISTICS_H
