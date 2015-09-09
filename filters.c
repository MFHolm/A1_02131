#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

void lowPass(int* input, int* output){
	int result = 2*output[0]-output[1]+(((input[0]-2*input[6]+input[12]))/32);
	insertArray(output,32,result);
	printf("%d\n",result);
}

void highPass(){

}


void insertArray(int* x,int size, int new){
	for(int i = 1; i < size; i++){
		x[i]=x[i-1];
	}
	x[0]=new;

}
