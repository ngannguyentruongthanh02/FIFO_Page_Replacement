
#include "../include/Statistics.h"
#include <iomanip>

// Tính toán thống kê kết quả FIFO
Statistics calculateStatistics(const FIFOResult& result) {

    Statistics stats;

    // Lấy dữ liệu từ kết quả FIFO
    stats.pageFaults = result.pageFaults;
    stats.pageHits = result.pageHits;

    // Tính tổng số lần truy cập trang
    stats.totalReferences = stats.pageFaults + stats.pageHits;

    // Khởi tạo tỷ lệ
    stats.pageFaultRate = 0.0;
    stats.pageHitRate = 0.0;

    // Tính tỷ lệ Page Fault và Page Hit
    if (stats.totalReferences > 0) {

        stats.pageFaultRate =
            (double)stats.pageFaults
            / stats.totalReferences * 100;

        stats.pageHitRate =
            (double)stats.pageHits
            / stats.totalReferences * 100;
    }

    return stats;
}


// Hiển thị kết quả thống kê
void displayStatistics(const Statistics& stats) {

    cout << "\n========== STATISTICS ==========\n";

    cout << "Total Page References: "
        << stats.totalReferences << "\n";

    cout << "Page Faults: "
        << stats.pageFaults << "\n";

    cout << "Page Hits: "
        << stats.pageHits << "\n";

    cout << fixed << setprecision(2);

    cout << "Page Fault Rate: "
        << stats.pageFaultRate << "%\n";

    cout << "Page Hit Rate: "
        << stats.pageHitRate << "%\n";

    cout << "================================\n";
}
