#include <stdio.h>
#include <stdlib.h>
#include "filters.h"

static int SPKF = 0, NPKF = 0, THRESHOLD1 = 0, THRESHOLD2 = 0;
static int RR_Average1 = 0, RR_Average2 = 0, RR_LOW = 0, RR_HIGH = 0, RR_MISS =0;
static int counter = -1;
static int times[30]= {0};
static int RR_intervals[9] = {0};
static int Rpeaks[30] = {0};
static int RecentRR_OK[30] = {0};
static int RecentRR[30] = {0};
static int peaks[30] = {0};

void identifyPeaks(int* input) {
	counter = counter +1;
	int input1 = input[1];
	int input0 = input[0];
	int input2 = input[2];
	if (input[1] > input[0] && input[1] > input[2]) {
		insertArray(peaks, 30, input[1]);
		if (peaks[0] > THRESHOLD1) {
			int interval = counter - times[0];
			insertArray(RR_intervals, 9, interval);
		}
		else {
			NPKF = peaks[0]/8 + (7 * NPKF)/8;
			THRESHOLD1 = NPKF + (SPKF - NPKF)/4;
			THRESHOLD2 = THRESHOLD1 / 2;
			exit(0);
		}
		if (RR_intervals[0] > RR_LOW && RR_intervals[0] < RR_HIGH) {
			insertArray(Rpeaks, 30, peaks[0]);
			insertArray(times, 30, counter);
			SPKF = peaks[0]/8 + (7 * SPKF)/8;
			insertArray(RecentRR_OK, 30, RR_intervals[0]);
			insertArray(RecentRR, 30, RR_intervals[0]);
			RR_Average2 = averageOf(RecentRR_OK, 30);
			RR_Average1 = averageOf(RecentRR, 30);
			RR_LOW = 0.92 * RR_Average2;
			RR_HIGH = 1.16 * RR_Average2;
			THRESHOLD1 = NPKF + (SPKF - NPKF)/4;
			THRESHOLD2 = THRESHOLD2 / 2;
		}
		else {
			if (RR_intervals[0] > RR_MISS) {

				for (int i = 0; i < 30; i++) {
					if (peaks[i] > THRESHOLD2) {
						insertArray(Rpeaks, 30, peaks[i]);
						SPKF = peaks[i]/4 + (3* SPKF)/4;
						int interval = times[0] - (counter - i);
						insertArray(RR_intervals, 30, interval);
						RR_Average1 = averageOf(RecentRR, 30);
						RR_LOW = 0.92 * RR_Average1;
						RR_HIGH = 1.16 * RR_Average1;
						RR_MISS = 1.66 * RR_Average1;
						THRESHOLD1 = NPKF + (SPKF - NPKF) / 4;
						THRESHOLD2 = THRESHOLD1 / 2;
						i=30;
					}
				}

			}
		}

	}
	printf("%d     %d\n", Rpeaks[0], times[0]);
}

int averageOf(int* list, int size) {
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += list[i];
	}
	return sum/size;
}
