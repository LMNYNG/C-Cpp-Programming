#include <stdio.h>
void partition(int x[], int lb, int ub, int* pj) {
	int a, down, temp, up;
	a = x[lb];
	up = ub;
	down = lb;
	while (down < up) {
		while (x[down] <= a && down < ub)
			down++;
		while (x[up] > a)
			up--;
		if (down < up) {
			temp = x[down];
			x[down] = x[up];
			x[up] = temp;
		}
	}
	x[lb] = x[up];
	x[up] = a;
	*pj = up;
}
void quick(int x[], int lb, int ub) {
	int j;
	if (lb >= ub) return;
	partition(x, lb, ub, &j);
	quick(x, lb, j - 1);
	quick(x, j + 1, ub);
}