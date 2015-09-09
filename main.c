#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "filters.h"




int main() {
	static const char filename[] = "ECG.txt";
	FILE *file = fopen(filename,"r");

	int input[13] = {0};
	int afterLowpass[33] = {0};
	int afterHighpass[5] = {0};
	int afterDerivative = 0;
	int afterSquare[30] = {0};
	//for (int i = 0; i < 12; i++) {
	//	printf("%d\n", input[i]);
	//}
	int counter = 0;
	int x;

	do{
		x = getNextData(file);
		insertArray(input,13,x);
		lowPass(input,afterLowpass);
		highPass(afterLowpass,afterHighpass);
		afterDerivative = derivative(afterHighpass);
		printf("her");
		square(afterDerivative);
	 }while (!feof(file));



}


