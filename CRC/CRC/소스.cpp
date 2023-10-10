#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {
	printf("다항식 입력:");
	char exp[50];
	scanf_s(" %s", & exp, sizeof(exp));
	printf("송신 문자열 입력:");

	char string[30];
	scanf_s(" %s", & string, sizeof(string));
	int size;

	if (exp[0] == 'x') size = exp[1] - '0'+1;
	else size = 1;

	int *code = (int*)malloc(sizeof(int)* size);
	for (int i = 0; i < size; i++) code[i] = 0;

	int *result = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) result[i] = 0;

	for (int i = 0; i < strlen(exp); i++) {
		if (exp[i] == 'x') {
			code[size - (exp[i + 1] - '0')-1] = 1;
			i++;
		}
		else if (exp[i] == '1') code[size - 1] = 1;
	}

	for (int i = 0; i < size - 1; i++) strcat_s(string,sizeof(string), "0");

	for (int i = 0; i <= strlen(string) - strlen(exp) ; i++) {
		int count = 1;
		int count2 = 0;

		if (i == 0) {
			if (string[i] == '1') {
				for (int j = i + 1; j < i + size - 1; j++) {
					if (code[count++] == string[j] - '0') result[count2++] = 0;
					else result[count2++] = 1;
				}
				result[count2] = string[i + size] - '0';
			}
			else if (string[i] == '0') {
				for (int j = i + 1; j < i + size - 1; j++) {
					if (0 == string[j] - '0') result[count2++] = 0;
					else result[count2++] = 1;
				}
				result[count2] = string[i + size] - '0';
			}
		}
		else {
			if (result[0] == 1) {
				for (int j = 1; j < size; j++) {
					if (result[j] == code[j]) result[count2++] = 0;
					else result[count2++] = 1;
				}
				result[size - 1] = string[i + size] - '0';
			}
			else {
				for (int j = 1; j < size; j++) {
					if (result[j] == 0) result[count2++] = 0;
					else result[count2++] = 1;
				}
				result[size - 1] = string[i + size] - '0';
			}
		}

		printf("STEP%d) ", i+1);
		for (int k = 0 ; k < size; k++)  printf("%d  ", result[k]);
		printf("\n");
	}
	printf("Checksum is [  ");
	for (int i = 1; i < size; i++)  printf("%d  ", result[i]);
	printf("]");
	
	return 0;
}