
#include "../include/FIFO.h"
#include <iomanip>

// Thực hiện thuật toán FIFO
FIFOResult runFIFO(const InputData& data) {

    FIFOResult result;
    result.pageFaults = 0;
    result.pageHits = 0;

    int frameCount = data.frameCount;

    // Khởi tạo Frame rỗng
    vector<int> frames(frameCount, -1);

    // Vị trí Frame cần thay thế tiếp theo
    int replaceIndex = 0;

    // Duyệt chuỗi tham chiếu trang
    for (int page : data.referenceString) {

        bool found = false;

        // Kiểm tra trang đã tồn tại trong Frame chưa
        for (int i = 0; i < frameCount; i++) {
            if (frames[i] == page) {
                found = true;
                break;
            }
        }

        if (found) {
            // Page Hit
            result.pageHits++;
        }
        else {
            // Page Fault
            result.pageFaults++;

            // Tìm Frame trống
            bool emptyFrameFound = false;

            for (int i = 0; i < frameCount; i++) {
                if (frames[i] == -1) {
                    frames[i] = page;
                    emptyFrameFound = true;
                    break;
                }
            }

            // Nếu không còn Frame trống thì thay thế
            if (!emptyFrameFound) {
                frames[replaceIndex] = page;
                replaceIndex = (replaceIndex + 1) % frameCount;
            }
        }

        // Lưu trạng thái Frame sau mỗi lần truy cập
        result.frameHistory.push_back(frames);
    }

    return result;
}


// Hiển thị kết quả thuật toán FIFO
void displayFIFOResult(
    const InputData& data,
    const FIFOResult& result
) {

    cout << "\n========== FIFO PAGE REPLACEMENT RESULT ==========\n";

    // Hiển thị chuỗi tham chiếu
    cout << "\nReference String:\n";

    for (int page : data.referenceString) {
        cout << setw(5) << page;
    }

    // Hiển thị lịch sử Frame
    cout << "\n\nFrame History:\n";

    for (int i = 0; i < data.frameCount; i++) {

        cout << "Frame " << i + 1 << ":";

        for (const auto& state : result.frameHistory) {

            if (state[i] == -1) {
                cout << setw(5) << "-";
            }
            else {
                cout << setw(5) << state[i];
            }
        }

        cout << "\n";
    }

    // Hiển thị trạng thái Hit / Fault
    cout << "\nStatus:\n";

    for (size_t i = 0; i < data.referenceString.size(); i++) {

        bool isHit = false;

        if (i > 0) {
            for (int j = 0; j < data.frameCount; j++) {
                if (result.frameHistory[i - 1][j]
                    == data.referenceString[i]) {
                    isHit = true;
                    break;
                }
            }
        }

        cout << setw(5) << (isHit ? "H" : "F");
    }

    // Hiển thị thống kê
    cout << "\n\n========== SUMMARY ==========\n";

    cout << "Number of Frames: "
        << data.frameCount << "\n";

    cout << "Total Page References: "
        << data.referenceString.size() << "\n";

    cout << "Page Faults: "
        << result.pageFaults << "\n";

    cout << "Page Hits: "
        << result.pageHits << "\n";

    double faultRate = 0;
    double hitRate = 0;

    if (!data.referenceString.empty()) {
        faultRate = (double)result.pageFaults
            / data.referenceString.size() * 100;

        hitRate = (double)result.pageHits
            / data.referenceString.size() * 100;
    }

    cout << fixed << setprecision(2);

    cout << "Page Fault Rate: "
        << faultRate << "%\n";

    cout << "Page Hit Rate: "
        << hitRate << "%\n";
}
