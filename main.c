#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "filters.h"
#include "peaks.h"
#include "helperMethods.h"
#include <time.h>

int main() {
	//Two booleans are used when taking calculating the runtime
	int clockOn = 0;
	int totalClockOn = 1;
	//Variables used in calculating runtime
	clock_t start, clockBeforeRead, clockAfterRead, clockAfterLowPass,
			clockAfterHighPass, clockAfterDer, clockAfterSquare, clockAfterMWI,
			clockAfterIdentifyPeaks, end;
	double cpuTimeUsed;
	double timeReadData = 0;
	double timeLowPass = 0;
	double timeHighPass = 0;
	double timeDerivative = 0;
	double timeSquare = 0;
	double timeMWindowInt = 0;
	double timeIdentifyPeaks = 0;

	//The file to read from
	static const char filename[] = "ECG.txt";
	FILE *file = fopen(filename, "r");

	//Arrays and a variable to keep track of the values after each filter
	int input[13] = { 0 };
	int afterLowpass[33] = { 0 };
	int afterHighpass[5] = { 0 };
	int afterDerivative = 0;
	int afterSquare[30] = { 0 };
	int afterWindowIntegration[3] = { 0 };

	int value;
	int counter = 0;

	if (totalClockOn) {
		start = clock();
	}
	//The loops runs as long as it has not reached the end of the file
	while (!feof(file)) {
		if (clockOn) {
			clockBeforeRead = clock();
		}
		counter++;
		//The nex value is saved in the variable "value"
		value = getNextData(file);
		insertArray(input, 13, value);
		/*if (clockOn) {
		 clockAfterRead = clock();
		 timeReadData =+ ((double) ((clockAfterRead - clockBeforeRead)) / CLOCKS_PER_SEC ) * 1000;
		 }*/
		lowPass(input, afterLowpass);
		/*if (clockOn) {
		 clockAfterLowPass = clock();
		 timeLowPass =+ ((double) ((clockAfterLowPass - clockAfterRead)) / CLOCKS_PER_SEC ) * 1000;
		 }*/
		highPass(afterLowpass, afterHighpass);
		/*if (clockOn) {
		 clockAfterHighPass = clock();
		 timeHighPass =+ ((double) ((clockAfterHighPass - clockAfterLowPass)) / CLOCKS_PER_SEC ) * 1000;
		 }*/
		afterDerivative = derivative(afterHighpass);
		/*if (clockOn) {
		 clockAfterDer = clock();
		 timeDerivative =+ ((double) ((clockAfterDer - clockAfterHighPass)) / CLOCKS_PER_SEC ) * 1000;
		 }*/
		square(afterDerivative, afterSquare);
		/*if (clockOn) {
		 clockAfterSquare = clock();
		 timeSquare =+ ((double) ((clockAfterSquare - clockAfterDer)) / CLOCKS_PER_SEC ) * 1000;
		 }*/
		mWindowIntegration(afterSquare, afterWindowIntegration);
		if (clockOn) {
			clockAfterMWI = clock();
			timeMWindowInt = +((double) ((clockAfterMWI - clockBeforeRead))
					/ CLOCKS_PER_SEC) * 1000;
		}
		identifyPeaks(afterWindowIntegration);
		if (clockOn) {
			clockAfterIdentifyPeaks = clock();
			timeIdentifyPeaks = +((double) ((clockAfterIdentifyPeaks
					- clockAfterMWI)) / CLOCKS_PER_SEC) * 1000;
		}
	}
	if (totalClockOn) {
		end = clock();
		cpuTimeUsed = ((double) ((end - start)) / CLOCKS_PER_SEC) * 1000;
		printf("Total cpu time: %f milliseconds\n", cpuTimeUsed);
	}
	if (clockOn) {
		//printf("Average time read data: %f nanoseconds\nAverage time Low Pass filter: %f nanoseconds\nAverage time High Pass filter: %f nanoseconds\n", timeReadData, timeLowPass, timeHighPass);
		//printf("Average time derivative filter: %f nanoseconds\nAverage time square filter: %f nanoseconds\nAverage time moving window integration filter: %f nanoseconds\n",timeDerivative, timeSquare, timeMWindowInt);
		printf("Time to apply filters: %f milliseconds\n", timeMWindowInt);
		printf("Time to identify peaks: %f milliseconds\n", timeIdentifyPeaks);
	}
	return 0;

}
