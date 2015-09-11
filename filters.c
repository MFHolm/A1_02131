#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"


void lowPass(int* input, int* output){
	int result = 2*output[0]-output[1]+(((input[0]-2*input[6]+input[12]))/32);

	printf("%d\n" , result);
	insertArray(output,33,result);

}

void highPass(){

}


void insertArray(int x[],int size, int new){
	for(int i = size-1; i > 0; i--){
		x[i]=x[i-1];
	}
	x[0]=new;

}
