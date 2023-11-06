#include <stdio.h>
long func2(long rdx, long esi, long edi) {
	return (1 + esi - 1) * (esi - 1) / 2 * edi + (1 + esi - 1) * (esi - 1) / 2 * esi * rdx;
}
long func3(long edi, long esi, long edx, long rcx, long r8, long r9, long s1, long s2) {
	long rax;
	edi *= r8;
	esi *= r9;
	edi -= esi;
	edx *= (s1 + s2 + 8);
	rax = edx + edi;
	rcx *= (s1 + s2 + 16);
	return rax + rcx;
}
long main() {
	long a = 4;
	long b = 5;
	long c = 3;
	long d = -4;
	long e = 9;
	long f = 6;
	long g = 2;
	long h = 8;


	long f2, f3;

	f2 = func2(a, b, d);
	f3 = func3(a, b, c, d, e, f, g, h);

	printf("func2(4,5,-4) = %ld\n", f2);
	printf("func3(4,5,3,-4,9,6,2,8) = %ld\n", f3);

	return 0;
}