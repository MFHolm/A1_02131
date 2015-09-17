#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "filters.h"
#include "peaks.h"


int main() {
	static const char filename[] = "ECG.txt";
	FILE *file = fopen(filename,"r");


	int input[13] = {0};
	int afterLowpass[33] = {0};
	int afterHighpass[5] = {0};
	int afterDerivative = 0;
	int afterSquare[30] = {0};
	int afterWindowIntegration[3] = {0};


	int x;
	
	char max[100];

	while(fgets(max,100,file)){
		x = getNextData(file);
		insertArray(input,13,x);
		lowPass(input,afterLowpass);
		highPass(afterLowpass,afterHighpass);
		afterDerivative = derivative(afterHighpass);
		square(afterDerivative,afterSquare);
		mWindowIntegration(afterSquare, afterWindowIntegration);
		identifyPeaks(afterWindowIntegration);

	 }

}


