#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"


int lowPass(int input[], int output[]){
	int test= 2*output[0]-output[1]+(input[0]-2*input[6]+input[12])/32;
	//insertArray(output,32,res);
	printf("In Low = %d, 6:%d, 12:%d\n",input[0],input[6],input[12]);
	return test;
}

void highPass(){

}


void insertArray(int x[],int size, int new){
	for(int i = 1; i < size; i++){
		x[i]=x[i-1];
	}
	x[0]=new;

}
