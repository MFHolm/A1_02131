#include <stdio.h>
#include <stdlib.h>

void insertArray(int* list,int size, int new);
int averageOf(int* list, int size);

//This functions hifts all elements in the array to the right and inserts a new element
void insertArray(int* list,int size, int new){
	for(int i = size-1; i > 0; i--){
		list[i]=list[i-1];
	}
	list[0]=new;

}
//This function takes the average of all non zero values in the array
int averageOf(int* list, int size) {
	int sum = 0;
	int realSize = 0;
	for (int i = 0; i < size; i++) {
		if (list[i] != 0) {
			realSize++;
			sum += list[i];
		}
	}
	return sum / realSize;
}
