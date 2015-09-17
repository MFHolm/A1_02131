#include <stdio.h>
#include <stdlib.h>
#include "filters.h"

static int SPKF = 0, NPKF = 0, THRESHOLD1 = 0, THRESHOLD2 = 0;
static int RR_Average1 = 0, RR_Average2 = 0, RR_LOW = 0, RR_HIGH = 0, RR_MISS =
		0;
static int counter = 0;
static int RPeakTime[30] = { 0 };
static int peakTime[10000] = { 0 };
static int Rpeaks[30] = { 0 };
static int RecentRR_OK[8] = { 0 };
static int RecentRR[8] = { 0 };
static int size = 10000;
static int peaks[10000] = { 0 };

int averageOf(int* list, int size);
void peakBelowThreshold1();
void rrCorrectInterval(int);
void newPeakAboveThreshold2(int);

void identifyPeaks(int* input) {



	if ((input[1] > input[0]) && (input[1] > input[2])) {
		insertArray(peaks, size, input[1]);
		insertArray(peakTime, size, counter);
		if (peaks[0] > THRESHOLD1) {
			int interval = counter - RPeakTime[0];
			if ((interval > RR_LOW) && (interval < RR_HIGH)) {
				rrCorrectInterval(interval);
			} else {
				if (interval > RR_MISS) {
					for (int i = 0; i < size; i++) {
						if (peaks[i] > THRESHOLD2) {
							newPeakAboveThreshold2(i);
							break;
						}

					}

				}
			}
		} else {
			peakBelowThreshold1();

		}

	}
	//printf("%d \n",counter);
	counter++;
}

int averageOf(int* list, int size) {
	int c = 0;
	int sum = 0;
	for (int i = 0; i < size; i++) {
		if(list[i]>0){
		sum += list[i];
		c++;
		}
	}
	return sum / c;
}

void peakBelowThreshold1() {
	NPKF = 0.125 * peaks[0] + 0.875 * NPKF;
	THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);
	THRESHOLD2 = 0.5 * THRESHOLD1;
}

void rrCorrectInterval(int interval) {
	insertArray(Rpeaks, 30, peaks[0]);
	insertArray(RPeakTime, 30, counter);
    printf("%d     %d\n", RPeakTime[0], Rpeaks[0]);
	SPKF = peaks[0]*0.125 + SPKF*0.875;
	insertArray(RecentRR_OK, 8, interval);
	insertArray(RecentRR, 8, interval);
	RR_Average2 = averageOf(RecentRR_OK, 8);
	RR_Average1 = averageOf(RecentRR, 8);
	RR_LOW = 0.92 * RR_Average2;
	RR_HIGH = 1.16 * RR_Average2;
	//printf("\nAv2  %d \nAv1  %d \nLow  %d \nHigh  %d\n",RR_Average2,RR_Average1,RR_LOW,RR_HIGH);
	THRESHOLD1 = NPKF + (SPKF - NPKF)*0.25;
	THRESHOLD2 = THRESHOLD1*0.5;
}

void newPeakAboveThreshold2(int i) {
	insertArray(Rpeaks, 30, peaks[i]);
	insertArray(RPeakTime, 30, peakTime[i]);
	printf("%d     %d\n", RPeakTime[0], Rpeaks[0]);
	SPKF = peaks[i]*0.25 + (SPKF)*0.75;
	int interval = RPeakTime[0] - RPeakTime[1];
	insertArray(RecentRR, 8, interval);
	RR_Average1 = averageOf(RecentRR, 8);
	RR_LOW = 0.92 * RR_Average1;
	RR_HIGH = 1.16 * RR_Average1;
	RR_MISS = 1.66 * RR_Average1;
	//printf("\nAv2  %d \nAv1  %d \nLow  %d \nHigh  %d\n",RR_Average2,RR_Average1,RR_LOW,RR_HIGH);
	THRESHOLD1 = NPKF + (SPKF - NPKF)*0.25;
	THRESHOLD2 = THRESHOLD1*0.5;
}

