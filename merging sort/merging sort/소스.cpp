void merge(int x[], int low, int mid, int high) {
	int i, j, k;
	int aux[1024];
	for (i = low, j = mid + 1; i <= mid && j <= high;)
		if (x[i] <= x[j])
			aux[k++] = x[i++];
		else
			aux[k++] = x[j++];
	for (; i <= mid; i++, k++)
		aux[k] = x[i];
	for (; j <= high; j++, k++)
		aux[k] = x[j];
	for (i = low; i < high; i++)
		x[i] = aux[i];
}
void mergesort(int x[], int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		mergesort(x, low, mid);
		mergesort(x, mid + 1, high);
		merge(x, low, mid, high);
	}
}