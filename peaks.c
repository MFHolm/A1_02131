#include <stdio.h>
#include <stdlib.h>
#include "filters.h"

static int SPKF = 0, NPKF = 0, THRESHOLD1 = 0, THRESHOLD2 = 0;
static int RR_Average1 = 0, RR_Average2 = 0, RR_LOW = 0, RR_HIGH = 0, RR_MISS =
		0;
static int counter = -1;
static int RPeakTime[30] = { 0 };
static int peakTime[10000] = { 0 };
static int Rpeaks[30] = { 0 };
static int RecentRR_OK[30] = { 0 };
static int RecentRR[30] = { 0 };
static int size = 10000;
static int peaks[10000] = { 0 };

int averageOf(int* list, int size);

void identifyPeaks(int* input) {
	counter++;
	//int input1 = input[1];
	//int input0 = input[0];
	//int input2 = input[2];
	//printf("%d\n", counter);
	int interval;
	if ((input[1] > input[0]) && (input[1] > input[2])) {
		insertArray(peaks, size, input[1]);
		insertArray(peakTime, size, counter);
		if (peaks[0] > THRESHOLD1) {
			interval = counter - RPeakTime[0];
			if ((interval > RR_LOW) && (interval < RR_HIGH)) {
				insertArray(Rpeaks, 30, peaks[0]);
				insertArray(RPeakTime, 30, counter);
				printf("nsb%d     %d\n", RPeakTime[0], Rpeaks[0]);
				SPKF = peaks[0] / 8 + (7 * SPKF) / 8;
				insertArray(RecentRR_OK, 30, interval);
				insertArray(RecentRR, 30, interval);
				RR_Average2 = averageOf(RecentRR_OK, 30);
				RR_Average1 = averageOf(RecentRR, 30);
				RR_LOW = 0.92 * RR_Average2;
				RR_HIGH = 1.16 * RR_Average2;
				THRESHOLD1 = NPKF + (SPKF - NPKF) / 4;
				THRESHOLD2 = THRESHOLD1 / 2;
			} else {
				if (interval > RR_MISS) {

					for (int i = 1; i < size; i++) {
						if (peaks[i] > THRESHOLD2) {
							insertArray(Rpeaks, 30, peaks[i]);
							insertArray(RPeakTime, 30, peakTime[i]);
							printf("sa %d     %d\n", RPeakTime[0],Rpeaks[0]);
							SPKF = peaks[i] / 4 + (3 * SPKF) / 4;
							interval = RPeakTime[0] - RPeakTime[1];
							insertArray(RecentRR, 30, interval);
							RR_Average1 = averageOf(RecentRR, 30);
							RR_LOW = 0.92 * RR_Average1;
							RR_HIGH = 1.16 * RR_Average1;
							RR_MISS = 1.66 * RR_Average1;
							THRESHOLD1 = NPKF + (SPKF - NPKF) / 4;
							THRESHOLD2 = THRESHOLD1 / 2;
							i = size;
						}
					}

				}
			}
		} else {
			NPKF = peaks[0] / 8 + (7 * NPKF) / 8;
			THRESHOLD1 = NPKF + (SPKF - NPKF) / 4;
			THRESHOLD2 = THRESHOLD1 / 2;
		}

	}
}

int averageOf(int* list, int size) {
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += list[i];
	}
	return sum / size;
}
