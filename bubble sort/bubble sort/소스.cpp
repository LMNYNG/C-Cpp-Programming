#include <stdio.h>

void bubble(int array[], int n) {
	int hold, j, pass;
	int switched = true;

	for (pass = 0; pass < n - 1 && switched == true; pass++) {
		switched = false;
		for (j = 0; j < n - pass; j++) {
			if (array[j] > array[j + 1]) {
				switched = true;
				hold = array[j];
				array[j] = array[j + 1];
				array[j + 1] = hold;
			}
		}
	}
}