
#include <iostream>
#include <string>
#include <cstdlib>

#include "../include/Input.h"
#include "../include/FIFO.h"
#include "../include/Statistics.h"
#include "../include/Display.h"

using namespace std;

int main() {

	// 1. Nhap du lieu
	InputData data = inputData();

	// 2. Kiem tra du lieu
	if (!validateInput(data)) {
		cout << "\nInvalid input data!\n";
		return 1;
	}

	// 3. Chay thuat toan FIFO
	FIFOResult result = runFIFO(data);

	// 4. Tinh toan thong ke
	Statistics stats = calculateStatistics(result);

	// 5. Hien thi INPUT DATA
	cout << "\n";
	cout << "+------------------------------------------+\n";
	cout << "|               INPUT DATA                 |\n";
	cout << "+------------------------------------------+\n";

	cout << "| Number of Frames    : "
		<< data.frameCount;

	cout << string(21 - to_string(data.frameCount).length(), ' ')
		<< "|\n";

	cout << "| Reference String    : ";

	for (int page : data.referenceString) {
		cout << page << " ";
	}

	cout << "\n";
	cout << "+------------------------------------------+\n";


	// 6. Hien thi FIFO SIMULATION
	cout << "\n";
	cout << "+------------------------------------------+\n";
	cout << "|              FIFO SIMULATION             |\n";
	cout << "+------------------------------------------+\n";

	// Dong Reference
	cout << "| Ref       ";

	for (int page : data.referenceString) {
		cout << page << "  ";
	}

	cout << "\n";

	// Cac dong Frame
	for (int i = 0; i < data.frameCount; i++) {

		cout << "| Frame " << i + 1 << "   ";

		for (const auto& state : result.frameHistory) {

			if (state[i] == -1) {
				cout << "-  ";
			}
			else {
				cout << state[i] << "  ";
			}
		}

		cout << "\n";
	}

	// Dong Status
	cout << "| Status    ";

	for (int i = 0; i < data.referenceString.size(); i++) {

		bool isHit = false;

		if (i > 0) {
			for (int j = 0; j < data.frameCount; j++) {

				if (result.frameHistory[i - 1][j] ==
					data.referenceString[i]) {

					isHit = true;
					break;
				}
			}
		}

		cout << (isHit ? "H" : "F") << "  ";
	}

	cout << "\n";
	cout << "+------------------------------------------+\n";


	// 7. Hien thi DETAILED PROCESSING
	displayDetailedProcessing(data, result);


	// 8. Hien thi STATISTICS
	cout << "\n";
	cout << "+------------------------------------------+\n";
	cout << "|                STATISTICS                |\n";
	cout << "+------------------------------------------+\n";

	cout << "| Total References : "
		<< stats.totalReferences << "\n";

	cout << "| Page Faults      : "
		<< stats.pageFaults << "\n";

	cout << "| Page Hits        : "
		<< stats.pageHits << "\n";

	cout << fixed;
	cout.precision(2);

	cout << "| Fault Rate       : "
		<< stats.pageFaultRate << "%\n";

	cout << "| Hit Rate         : "
		<< stats.pageHitRate << "%\n";

	cout << "+------------------------------------------+\n";


	// 9. Ket thuc chuong trinh
	cout << "\n";
	cout << "|          PROGRAM COMPLETED              |\n";
	cout << "+------------------------------------------+\n";

	system("pause");

	return 0;
}
