#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int getNextData(FILE* file) {
		int value;
		fscanf(file,"%i",&value);

		return value;
}
