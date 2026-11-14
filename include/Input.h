
#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Cấu trúc lưu dữ liệu đầu vào
struct InputData {
    int frameCount;
    vector<int> referenceString;
};

// Nhập số lượng Frame
int inputFrameCount();

// Nhập chuỗi tham chiếu trang
vector<int> inputReferenceString();

// Kiểm tra dữ liệu đầu vào
bool validateInput(const InputData& data);

// Nhập toàn bộ dữ liệu
InputData inputData();

#endif // INPUT_H
