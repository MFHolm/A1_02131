#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "filters.h"




int main() {
	static const char filename[] = "ECG.txt";
	FILE *file = fopen(filename,"r");

	int input[13] = {0};
	int afterLowpass[33] = {0};
	//for (int i = 0; i < 12; i++) {
	//	printf("%d\n", input[i]);
	//}
	int counter = 0;
	int x;

	while (!feof(file)){

		x = getNextData(file);
		insertArray(input,13,x);
		lowPass(input,afterLowpass);
	}



}


