void selectsort(int x[], int n) {
	int i, index, j, large;
	for (i = n - 1; i > 0; i--) {
		large = x[0];
		index = 0;
		for (j = 1; j <= i; j++)
			if (x[j] > large) {
				large = x[j];
				index = j;
			}
		x[index] = x[i];
		x[i] = large;
	}
	
}