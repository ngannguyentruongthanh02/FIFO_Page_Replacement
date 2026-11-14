
#include "../include/Input.h"
#include <limits>
#include <sstream>

// ==========================================
// 1. Nhap so luong Frame
// ==========================================
int inputFrameCount() {
    int frameCount;

    while (true) {
        cout << "Enter number of Frames: ";

        if (cin >> frameCount && frameCount > 0) {
            break;
        }

        cout << "Invalid input! Frame count must be a positive integer.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return frameCount;
}

// ==========================================
// 2. Nhap chuoi tham chieu trang
// ==========================================
vector<int> inputReferenceString() {
    vector<int> referenceString;
    string line;

    // Bo qua ky tu xuong dong sau khi nhap Frame
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "Enter Reference String (separated by spaces): ";

        getline(cin, line);

        stringstream ss(line);
        int page;
        bool valid = true;

        referenceString.clear();

        while (ss >> page) {
            if (page < 0) {
                valid = false;
                break;
            }

            referenceString.push_back(page);
        }

        // Kiem tra ky tu khong hop le
        if (!ss.eof()) {
            valid = false;
        }

        if (valid && !referenceString.empty()) {
            break;
        }

        cout << "Invalid Reference String! Please enter non-negative integers.\n";
    }

    return referenceString;
}

// ==========================================
// 3. Kiem tra du lieu dau vao
// ==========================================
bool validateInput(const InputData& data) {

    if (data.frameCount <= 0) {
        return false;
    }

    if (data.referenceString.empty()) {
        return false;
    }

    for (int page : data.referenceString) {
        if (page < 0) {
            return false;
        }
    }

    return true;
}

// ==========================================
// 4. Nhap toan bo du lieu
// ==========================================
InputData inputData() {
    InputData data;

    cout << "\n========== FIFO PAGE REPLACEMENT ==========\n";

    data.frameCount = inputFrameCount();

    data.referenceString = inputReferenceString();

    if (validateInput(data)) {
        cout << "\nInput data successfully!\n";
    }

    return data;
}
