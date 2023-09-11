void insertionsort(int x[], int n) {
	int i, k, y;
	for (k = 1; k < n; k++) {
		y = x[k];
		for (i = k - 1; i >= 0 && y < x[i]; i--) x[i + 1] = x[i];
		x[i + 1] = y;
	}
}