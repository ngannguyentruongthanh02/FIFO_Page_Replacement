
#ifndef DISPLAY_H
#define DISPLAY_H

#include "Input.h"
#include "FIFO.h"
#include "Statistics.h"

void displayHeader();

void displayInputData(const InputData& data);

void displayFIFO(const InputData& data, const FIFOResult& result);

void displayDetailedProcessing(
	const InputData& data,
	const FIFOResult& result
);

void displayStatisticsResult(const Statistics& stats);

void displayFooter();

#endif // DISPLAY_H
