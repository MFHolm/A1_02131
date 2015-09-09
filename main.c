#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int lowpass();

int main() {
int [32];

}

int lowpass() {
	static const char filename[] = "ECG.txt";
	FILE *file = fopen(filename, "r");
	int value;
	fscanf(file, "%i", &value);

	return value;
}
