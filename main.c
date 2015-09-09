#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "filters.h"




int main() {
	static const char filename[] = "ECG.txt";
	FILE *file = fopen(filename,"r");

	int input[12] = {0};
	int afterLowpass[32] = {0};
	int x;
	int ret;
	for(int i;i<12;i++)
		printf("%d\n",x,afterLowpass[i]);
	while (!feof(file)){
			x = getNextData(file);
			insertArray(input,12,x);
			ret = lowPass(input,afterLowpass);
			insertArray(afterLowpass,32, ret);
			//printf("%d %d\n",x,afterLowpass[0]);

		}


	}



