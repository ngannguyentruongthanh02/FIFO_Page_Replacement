#include "../include/Display.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Hien thi tieu de
void displayHeader() {
    cout << "\n";
    cout << "============================================================\n";
    cout << "                 FIFO PAGE REPLACEMENT\n";
    cout << "                  SIMULATION SYSTEM\n";
    cout << "============================================================\n";
}

// Hien thi du lieu dau vao
void displayInputData(const InputData& data) {
    cout << "\n";
    cout << "---------------------- INPUT DATA -------------------------\n";

    cout << "Number of Frames : " << data.frameCount << "\n";

    cout << "Reference String : ";
    for (int page : data.referenceString) {
        cout << page << " ";
    }

    cout << "\n";
    cout << "------------------------------------------------------------\n";
}

// Hien thi bang mo phong FIFO
void displayFIFO(const InputData& data, const FIFOResult& result) {
    int n = static_cast<int>(data.referenceString.size());

    cout << "\n";
    cout << "==================== FIFO SIMULATION ======================\n\n";

    // Dong Reference
    cout << left << setw(12) << "Reference";

    for (int page : data.referenceString) {
        cout << setw(6) << page;
    }

    cout << "\n";

    cout << string(12 + n * 6, '-') << "\n";

    // Cac dong Frame
    for (int i = 0; i < data.frameCount; i++) {
        string frameName = "Frame " + to_string(i + 1);

        cout << left << setw(12) << frameName;

        for (const auto& state : result.frameHistory) {
            if (state[i] == -1) {
                cout << setw(6) << "-";
            }
            else {
                cout << setw(6) << state[i];
            }
        }

        cout << "\n";
    }

    cout << string(12 + n * 6, '-') << "\n";

    // Dong trang thai HIT / FAULT
    cout << left << setw(12) << "Status";

    for (int i = 0; i < n; i++) {
        bool isHit = false;

        // Kiem tra trang co ton tai trong Frame truoc do khong
        if (i > 0) {
            for (int j = 0; j < data.frameCount; j++) {
                if (result.frameHistory[i - 1][j] ==
                    data.referenceString[i]) {
                    isHit = true;
                    break;
                }
            }
        }

        cout << setw(6) << (isHit ? "HIT" : "FAULT");
    }

    cout << "\n";
    cout << "============================================================\n";

    cout << "\nLegend:\n";
    cout << "HIT   : Page already exists in memory.\n";
    cout << "FAULT : Page is not found in memory.\n";
    cout << "-     : Empty Frame.\n";
}

// Hien thi thong ke
void displayStatisticsResult(const Statistics& stats) {
    cout << "\n";
    cout << "====================== STATISTICS =========================\n";

    cout << left << setw(28) << "Total Page References:"
        << stats.totalReferences << "\n";

    cout << left << setw(28) << "Page Faults:"
        << stats.pageFaults << "\n";

    cout << left << setw(28) << "Page Hits:"
        << stats.pageHits << "\n";

    cout << fixed << setprecision(2);

    cout << left << setw(28) << "Page Fault Rate:"
        << stats.pageFaultRate << "%\n";

    cout << left << setw(28) << "Page Hit Rate:"
        << stats.pageHitRate << "%\n";

    cout << "============================================================\n";
}

// Hien thi ket thuc chuong trinh
void displayFooter() {
    cout << "\n";
    cout << "============================================================\n";
    cout << "              FIFO SIMULATION COMPLETED\n";
    cout << "============================================================\n";
}