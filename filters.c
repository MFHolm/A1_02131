#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

void lowPass(int* input, int* output){
	int result = 2*output[0]-output[1]+(((input[0]-2*input[6]+input[12]))/32);


	insertArray(output,33,result);


}

void highPass(int* input, int* output){
	int result = output[0] - input[0]/32 + input[16] - input[17] + input[32]/32;
	//printf("%d\n", result);
	insertArray(output,5,result);
}

int derivative(int* input) {
	int result = (2*input[0]+input[1]-input[3]-2*input[4])/8;
	//printf("%d\n", result);
	return result;


}

void square(int input, int* output) {
	int result = input * input;
	//printf("%d\n", result);
	insertArray(output, 30, result);
}

void mWindowIntegration(int* input){
	int result = 0;
	for(int i = 29; i >= 1; i--){
		result+=input[i];
	}
	result = result/30;
	printf("%d\n",result);
}

void insertArray(int* x,int size, int new){
	for(int i = size-1; i > 0; i--){
		x[i]=x[i-1];
	}
	x[0]=new;

}
