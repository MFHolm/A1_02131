#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "filters.h"




int main() {
	static const char filename[] = "ECG.txt";
	FILE *file = fopen(filename,"r");

	int input[12];
	int afterLowpass[32];

	int counter = 0;
	int x;

	while (!feof(file)){

		x = getNextData(file);
		if(counter <= 12){
			input[12-counter] = x;
			counter++;
		}else if(counter == 13){
			afterLowpass[0]=input[0];
			afterLowpass[1]=input[1];
			counter++;
		} else {
			insertArray(input,12,x);
			lowPass(input,afterLowpass);
		}


	}



}


