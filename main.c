#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "filters.h"




int main() {
	static const char filename[] = "ECG.txt";
	FILE *file = fopen(filename,"r");

	int input[12] = {0};
	int afterLowpass[32] = {0};
	//for (int i = 0; i < 12; i++) {
	//	printf("%d\n", input[i]);
	//}
	int counter = 0;
	int x;

	while (!feof(file)){

		x = getNextData(file);
		insertArray(input,12,x);
		lowPass(input,afterLowpass);
	}



}


