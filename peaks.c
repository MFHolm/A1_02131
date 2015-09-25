#include <stdio.h>
#include <stdlib.h>
#include "helperMethods.h"

//Global variables which are used and updated through the algorithm
static int SPKF = 0, NPKF = 0, THRESHOLD1 = 0, THRESHOLD2 = 0;
static int RR_Average1 = 0, RR_Average2 = 0, RR_LOW = 0, RR_HIGH = 0, RR_MISS =
		0;
static int counter = 0;
static int lastRpeakTime = 0;
static int peakTime[100] = { 0 };
static int latestRpeak = 0;
static int RecentRR_OK[8] = { 0 };
static int RecentRR[8] = { 0 };
static int size = 100;
static int peaks[100] = { 0 };
static int pulseCounter = 0;
static int missCounter = 0;
static int heartFailureCounter = 0;

void peakBelowThreshold1();
void rrCorrectInterval(int);
void newPeakAboveThreshold2(int, int);
void calculatePulse();

void identifyPeaks(int* input) {
	//If no peak has been detected for 2 seconds
	if (counter - lastRpeakTime > 500) { //500 samples is 2 seconds
		printHeartFailure();
	}
	int RR;
	//If the current value is higher than both its neighbors it is a peak
	if ((input[1] > input[0]) && (input[1] > input[2])) {
		insertArray(peaks, size, input[1]);
		insertArray(peakTime, size, counter);
		//If peak is above threshold1
		if (peaks[0] > THRESHOLD1) {
			RR = counter - lastRpeakTime;
			//If the RR interval is in the right interval
			if ((RR > RR_LOW) && (RR < RR_HIGH)) {
				missCounter = 0;
				rrCorrectInterval(RR);
			} else {
				missCounter++;
				checkMissWarning();
				if (RR > RR_MISS) {
					//The search back method
					for (int i = 1; i < size; i++) {
						//If a peak is detected that is above threshold2 it is saved
						if (peaks[i] > THRESHOLD2) {
							newPeakAboveThreshold2(i, RR);
							break;
						}
					}
				}
			}
			//If peak is not above threshold1 some variables are updated
		} else {
			peakBelowThreshold1();
		}

	}
	counter++;
}

void peakBelowThreshold1() {
	NPKF = 0.125 * peaks[0] + 0.875 * NPKF;
	THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);
	THRESHOLD2 = 0.5 * THRESHOLD1;
}

//This function saves peak as a Rpeak, updates some values and calculates the pulse
void rrCorrectInterval(int interval) {
	latestRpeak = peaks[0];
	lastRpeakTime = counter;
	if (latestRpeak < 2000) {
		printPeakWarning();
	}
	calculatePulse();
	SPKF = peaks[0] * 0.125 + SPKF * 0.875;
	insertArray(RecentRR_OK, 8, interval);
	insertArray(RecentRR, 8, interval);
	RR_Average2 = averageOf(RecentRR_OK, 8);
	RR_Average1 = averageOf(RecentRR, 8);
	RR_LOW = 0.92 * RR_Average2;
	RR_HIGH = 1.16 * RR_Average2;
	THRESHOLD1 = NPKF + (SPKF - NPKF) * 0.25;
	THRESHOLD2 = THRESHOLD1 * 0.5;
	printOutput();
}

//This function savese the peak as an RPeak, updates some values, and calculates the pulse
void newPeakAboveThreshold2(int i, int interval) {
	latestRpeak = peaks[i];
	lastRpeakTime = peakTime[i];
	calculatePulse();
	SPKF = peaks[i] * 0.25 + (SPKF) * 0.75;
	insertArray(RecentRR, 8, interval);
	RR_Average1 = averageOf(RecentRR, 8);
	RR_LOW = 0.92 * RR_Average1;
	RR_HIGH = 1.16 * RR_Average1;
	RR_MISS = 1.66 * RR_Average1;
	THRESHOLD1 = NPKF + (SPKF - NPKF) * 0.25;
	THRESHOLD2 = THRESHOLD1 * 0.5;
	printOutput();
}

void printOutput() {
	if (latestRpeak < 2000) {
		printPeakWarning();
	}
}

void calculatePulse() {
	if (RecentRR[0] > 0) {
		pulseCounter = 60 * 250 / (RecentRR[0]);
	}

}
void checkMissWarning() {
	if (missCounter > 4) {
		printRRWarning();
	}
}

void printPeakWarning() {
	printf("Oh no! The latest R-peak value was below 2000!\n");
}

void printRRWarning() {
	printf("Oh no! 5 succesive RR-intervals have missed interval.\n");
}
void printHeartFailure() {
		printf("Oh no! Heart failure....\n");
}
