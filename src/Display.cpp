
#include "../include/Display.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

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
			if (i < state.size() && state[i] == -1) {
				cout << setw(6) << "-";
			}
			else if (i < state.size()) {
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

		if (i < result.frameHistory.size() && i > 0) {
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

// Hien thi chi tiet qua trinh xu ly FIFO
void displayDetailedProcessing(const InputData& data, const FIFOResult& result) {

	cout << "\n";
	cout << "================================================================\n";
	cout << "DETAILED PROCESSING\n";

	cout << "Frames: " << data.frameCount << " | String: [";

	for (int i = 0; i < data.referenceString.size(); i++) {
		cout << data.referenceString[i];

		if (i < data.referenceString.size() - 1) {
			cout << ", ";
		}
	}

	cout << "]\n";
	cout << "================================================================\n";

	int n = static_cast<int>(data.referenceString.size());

	// Kiem tra so luong trang thai
	if (result.frameHistory.size() < n) {
		cout << "Error: Frame history is incomplete.\n";
		return;
	}

	// Duyet tung lan truy cap trang
	for (int i = 0; i < n; i++) {

		int page = data.referenceString[i];

		bool isHit = false;
		bool hasFreeFrame = false;
		int replacedPage = -1;

		const auto& currentState = result.frameHistory[i];

		// Lay trang thai bo nho truoc do
		if (i > 0) {

			const auto& previousState = result.frameHistory[i - 1];

			// Kiem tra trang da ton tai trong bo nho chua
			for (int frame : previousState) {
				if (frame == page) {
					isHit = true;
					break;
				}
			}

			// Kiem tra frame trong
			if (!isHit) {
				for (int frame : previousState) {
					if (frame == -1) {
						hasFreeFrame = true;
						break;
					}
				}
			}

			// Tim trang bi thay the
			if (!isHit && !hasFreeFrame) {

				for (int oldPage : previousState) {

					bool stillExists = false;

					for (int newPage : currentState) {
						if (oldPage == newPage) {
							stillExists = true;
							break;
						}
					}

					if (!stillExists) {
						replacedPage = oldPage;
						break;
					}
				}
			}
		}
		else {
			hasFreeFrame = true;
		}

		// Hien thi ket qua truy cap
		cout << "Reference " << page << " -> Page Fault: ";

		if (isHit) {
			cout << "NO (HIT)\n";
		}
		else {

			cout << "YES (MISS - ";

			if (hasFreeFrame) {
				cout << "Added to free frame";
			}
			else {
				cout << "Replaced page " << replacedPage;
			}

			cout << ")\n";
		}

		// Hien thi trang thai bo nho
		cout << "    Memory State: [";

		bool first = true;

		for (int frame : currentState) {

			if (frame != -1) {

				if (!first) {
					cout << ", ";
				}

				cout << frame;
				first = false;
			}
		}

		cout << "]\n";
	}

	cout << "================================================================\n";
}

// Hien thi thong ke
void displayStatisticsResult(const Statistics& stats) {
	cout << "\n";
	cout << "================================================================\n";
	cout << "SUMMARY RESULT\n";

	cout << "Total Page References: "
		<< stats.totalReferences << "\n";

	cout << "Total Page Faults: "
		<< stats.pageFaults << "\n";

	cout << "Total Page Hits: "
		<< stats.pageHits << "\n";

	cout << fixed << setprecision(2);

	cout << "Page Fault Rate: "
		<< stats.pageFaultRate << "%\n";

	cout << "Page Hit Rate: "
		<< stats.pageHitRate << "%\n";

	cout << "================================================================\n";
}

// Hien thi ket thuc chuong trinh
void displayFooter() {
	cout << "\n";
	cout << "============================================================\n";
	cout << "              FIFO SIMULATION COMPLETED\n";
	cout << "============================================================\n";
}
