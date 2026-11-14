#include <iostream>
#include <cassert>

#include "../include/FIFO.h"
#include "../include/Statistics.h"

using namespace std;

// Test 1: Tat ca cac trang deu bi loi trang
void testAllPageFaults() {
    InputData data;
    data.frameCount = 3;
    data.referenceString = { 1, 2, 3, 4, 1, 2, 5 };

    FIFOResult result = runFIFO(data);

    assert(result.pageFaults == 7);
    assert(result.pageHits == 0);
    assert(result.frameHistory.size() == 7);

    cout << "[PASS] Test 1: All Page Faults\n";
}

// Test 2: Kiem tra trang lap lai
void testPageHits() {
    InputData data;
    data.frameCount = 3;
    data.referenceString = { 1, 1, 1, 1 };

    FIFOResult result = runFIFO(data);

    assert(result.pageFaults == 1);
    assert(result.pageHits == 3);

    cout << "[PASS] Test 2: Page Hits\n";
}

// Test 3: Kiem tra Frame chi co 1 o
void testSingleFrame() {
    InputData data;
    data.frameCount = 1;
    data.referenceString = { 1, 2, 1 };

    FIFOResult result = runFIFO(data);

    assert(result.pageFaults == 3);
    assert(result.pageHits == 0);

    cout << "[PASS] Test 3: Single Frame\n";
}

// Test 4: Kiem tra thu tu thay the FIFO
void testFIFOReplacement() {
    InputData data;
    data.frameCount = 3;
    data.referenceString = { 1, 2, 3, 4 };

    FIFOResult result = runFIFO(data);

    assert(result.pageFaults == 4);
    assert(result.pageHits == 0);

    assert(result.frameHistory[3][0] == 4);
    assert(result.frameHistory[3][1] == 2);
    assert(result.frameHistory[3][2] == 3);

    cout << "[PASS] Test 4: FIFO Replacement Order\n";
}

// Test 5: Kiem tra tinh toan thong ke
void testStatistics() {
    InputData data;
    data.frameCount = 3;
    data.referenceString = { 1, 1, 2, 2, 3 };

    FIFOResult result = runFIFO(data);
    Statistics stats = calculateStatistics(result);

    assert(stats.totalReferences == 5);
    assert(stats.pageFaults == 3);
    assert(stats.pageHits == 2);

    assert(stats.pageFaultRate == 60.0);
    assert(stats.pageHitRate == 40.0);

    cout << "[PASS] Test 5: Statistics Calculation\n";
}

int main() {
    cout << "\n";
    cout << "========================================\n";
    cout << "       FIFO UNIT TESTING SYSTEM\n";
    cout << "========================================\n\n";

    testAllPageFaults();
    testPageHits();
    testSingleFrame();
    testFIFOReplacement();
    testStatistics();

    cout << "\n========================================\n";
    cout << "       ALL TESTS PASSED!\n";
    cout << "========================================\n";

    system("pause");

    return 0;
}