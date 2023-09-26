void heapsort(int x[], int n) {
	int i, elt, s, f, ivalue;

	for (i = 0; i < n; i++) {//sift up
		elt = x[i];
		s = i;
		f = (s - 1) / 2;
		while (s > 0 && x[f] < elt) {
			x[s] = x[f];
			s = f;
			f = (s - 1) / 2;
		}
		x[s] = elt;
	}
	for (i = n - 1; i > 0; i--) {//sift down
		ivalue = x[i];
		x[i] = x[0];
		f = 0;
		if (i == 0)
			s = -1;
		else
			s = 1;
		if (i > 2 && x[2] > x[1])
			s = 2;
		while (s >= 0 && ivalue < x[s]) {
			x[f] = x[s];
			f = s;
			s = 2 * f + 1;
			if (s + 1 <= i - 1 && x[s] < x[s + 1])
				s = s = +1;
			if (s > i - 1)
				s = -1;
		}
		x[f] = ivalue;
	}
}