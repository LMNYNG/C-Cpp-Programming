#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct s_table {//심볼 테이블
	char symbol[20] = { 0 };
	int sindex;
}ST[20];

struct r_table {//레지스터 테이블
	char reg[3] = { 0 };
	int num;
}RT[14];

struct i_table {//명령어 테이블
	char component[5] = { 0 };
	int add_index;
}IT[30];

char* temp;
int index = 0;
int i = 0;
int start=1;
int end=1;
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ시작점과 끝점 설정ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
void set_SE(char* temp) {
	if (strcmp(temp, "MOV") == 0) {
		start = 0;
		end = 6;
	}
	if (strcmp(temp, "ADD") == 0) {
		start = 7;
		end = 8;
	}
	if (strcmp(temp, "SUB") == 0) {
		start = 9;
		end = 10;
	}
	if (strcmp(temp, "AND") == 0) {
		start = 11;
		end = 14;
	}
	if (strcmp(temp, "OR") == 0) {
		start = 15;
		end = 18;
	}
	if (strcmp(temp, "INC") == 0) {
		start = end = 19;
	}
	if (strcmp(temp, "DEC") == 0) {
		start = end = 20;
	}
	if (strcmp(temp, "CMP") == 0) {
		start = 21;
		end = 24;
	}
	if (strcmp(temp, "JMP") == 0) {
		start = end = 25;
	}
	if (strcmp(temp, "JA") == 0) {
		start = end = 26;
	}
	if (strcmp(temp, "JB") == 0) {
		start = end = 27;
	}
	if (strcmp(temp, "JE") == 0) {
		start = end = 28;
	}
	if (strcmp(temp, "INT") == 0) {
		start = end = 29;
	}
}
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ확인함수ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
bool isReg(char* str) {//레지스터인지 확인
	if (strcmp(str, "AX") == 0 || strcmp(str, "BX") == 0 || strcmp(str, "CX") == 0 ||
		strcmp(str, "DX") == 0 || strcmp(str, "SI") == 0 || strcmp(str, "DI") == 0 ||
		strcmp(str, "AL") == 0 || strcmp(str, "BL") == 0 || strcmp(str, "CL") == 0 ||
		strcmp(str, "DL") == 0 || strcmp(str, "AH") == 0 || strcmp(str, "BH") == 0 ||
		strcmp(str, "CH") == 0 || strcmp(str, "DH") == 0) {
		return true;
	}
	else return false;
}
bool isNum(char* str) {//숫자인지 확인
	if (!(str[0] <= 57 && str[0] >= 48)) { 
		return false;
	}
	else return true;
}
bool isSym(char* str) {//심볼테이블 확인
	for (int j = 0; j < i; j++) {
		if (strcmp(ST[j].symbol, str) == 0) {
			return true;
		}
	}
	return false;
}
bool isMem(char* str) {//메모리인지 확인
	if (strchr(str, '[') != NULL) { 
		return true; 
	}
	else return false;
}
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡloop1 startedㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
void loop1(char* str) {
	char operand[10] = { 0 };
	temp = strtok(str, "\t");
	if (strcmp(temp, " ") != 0) {
		if (strchr(temp, ':') != NULL) {
			printf("Labl");
			temp[strlen(temp) - 1] = '\0';
			strcpy(ST[i].symbol, temp);
			ST[i++].sindex = index;
		}
		else {
			ST[i].sindex = index;
			strcpy(ST[i].symbol, temp);//테이블에 이름이랑 인덱스 저장
			i++;
			temp = strtok(NULL, "\t");//몇 바이트로 저장했는지 확인
			printf("Direc");
			if (strcmp(temp, "DB") == 0) {//define byte인 경우는 +1씩
				while (temp != NULL) {
					temp = strtok(NULL, ",");
					if (temp == NULL) return;
					index++;
				}
			}
			if (strcmp(temp, "DW") == 0) {//define word인 경우는 +2씩

				while (temp != NULL) {
					temp = strtok(NULL, ",");
					if (temp == NULL) return;
					index += 2;
				}
			}
		}
	}
	temp = strtok(NULL, "\t");
	printf("\tOpcd");
	set_SE(temp);
	temp = strtok(NULL, ",");
	if (start >= 19 && start <= 20 || start >= 25 && start <= 29) {
		if (isReg(temp)) { 
			printf("\tReg"); 
			strcat(operand, "R"); 
		}
		else if (isNum(temp)) { 
			printf("\tNumb"); 
			strcat(operand, "I"); 
		}
		else if (isMem(temp)) {
			printf("\t[Reg]");  
			strcat(operand, "[R]");
		}
		else {
			printf("\tSymbol");
			strcat(operand, "S");
		}
	}
	else {
		if (isReg(temp)) {
			printf("\tReg");
			strcat(operand, "R");
		}
		else if (isNum(temp)) {
			printf("\tNumb");
			strcat(operand, "I");
		}
		else if (isMem(temp)) {
			printf("\t[Reg]");
			strcat(operand, "[R]");
		}
		else {
			printf("\tSymbol");
			strcat(operand, "S");
		}
		temp = strtok(NULL, " ");
		if (isReg(temp)) {
			printf("\tReg");
			strcat(operand, "R");
		}
		else if (isNum(temp)) {
			printf("\tNumb");
			strcat(operand, "I");
		}
		else if (isMem(temp)) {
			printf("\t[Reg]");
			strcat(operand, "[R]");
		}
		else {
			printf("\tSymbol");
			strcat(operand, "S");
		}
	}
	for (int s = start; s <= end; s++)  
		if (strcmp(operand, IT[s].component) == 0) 	index += IT[s].add_index;
}
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡloop1 endedㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡloop2 startedㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
void loop2(char* str) {
	printf("%04d\t", index);
	int s;
	char operand[10] = { 0 };
	char op1[10];
	char op2[20];
	temp = strtok(str, "\t");
	if (strcmp(temp, " ") != 0) {
		if (strchr(temp, ':') != NULL);
		else{
			temp = strtok(NULL, "\t");//몇 바이트로 저장했는지 확인
			if (strcmp(temp, "DW") == 0) {//define byte인 경우는 +1씩
				while (temp != NULL) {
					temp = strtok(NULL, ",");
					if (temp == NULL) { 
						printf("\n"); 
						return; 
					}
					printf(" %04X", atoi(temp));
					index+=2;
				}
			}
			if (strcmp(temp, "DB") == 0) {//define word인 경우는 +2씩

				while (temp != NULL) {
					temp = strtok(NULL, ",");
					if (temp == NULL) {
						printf("\n");
						return;
					}
					printf(" %02X", atoi(temp));
					index ++;
				}
			}
			
			}
		}
	temp = strtok(NULL, "\t");
	set_SE(temp);
	temp = strtok(NULL, ",");
	if (start >= 19 && start <= 20 || start >= 25 && start <= 29) {
		strcpy(op1, temp);
		if (isReg(temp))strcat(operand, "R");
		else if (isNum(temp)) strcat(operand, "I");
		else if (isMem(temp)) strcat(operand, "[R]");
		else strcat(operand, "S");
	}
	else {
		strcpy(op1, temp);
		if (isReg(temp))strcat(operand, "R");
		else if (isNum(temp)) strcat(operand, "I");
		else if (isMem(temp)) strcat(operand, "[R]");
		else strcat(operand, "S");
		temp = strtok(NULL, " ");
		strcpy(op2, temp);
		if (isReg(temp))strcat(operand, "R");
		else if (isNum(temp)) strcat(operand, "I");
		else if (isMem(temp)) strcat(operand, "[R]");
		else strcat(operand, "S");
	}
	for (s = start; s <= end; s++)
		if (strcmp(operand, IT[s].component) == 0) {
			index += IT[s].add_index;
			break;
		}
	if (s == 0) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op2) == 0) printf(" %02X %02X", 139, 226 + 4 * RT[j].num);
	}
	if (s == 1) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op1) == 0) printf(" %02X %02X", 139, 6 + 8 * RT[j].num);
		for (int j = 0; j < i; j++)
			if (strcmp(ST[j].symbol, op2) == 0) printf(" %04X", ST[j].sindex * 256);
	}
	if (s == 2) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op2) == 0) printf(" %02X %02X", 137, 6 + 8 * RT[j].num);
		for (int j = 0; j < i; j++)
			if (strcmp(ST[j].symbol, op1) == 0) printf(" %04X", ST[j].sindex*256);
	}
	if (s == 3) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op1) == 0) printf(" %02X %02X", 180 + RT[j].num, atoi(op2)*256);
	}
	if (s == 4) {
		for (int j = 0; j < i; j++)
			if (strcmp(ST[j].symbol, op2) == 0) printf(" %02X %02X %02X %04X", 199, 6, ST[j].sindex, atoi(op2)*256);
	}
	if (s == 5) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op1) == 0) printf(" %02X %02X", 139, 7 + 8 * RT[j].num);
	}
	if (s == 6) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op2) == 0) printf(" %02X %02X", 137, 4 + 8 * RT[j].num);
	}
	if (s == 7) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op2) == 0) printf(" %02X %02X", 3, 216 + RT[j].num);
	}
	if (s == 8) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op1) == 0) printf(" %02X %02X %02X", 83, 192 + RT[j].num, atoi(op2));
	}
	if (s == 9) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op2) == 0) printf(" %02X %02X", 43, 216 + RT[j].num);
	}
	if (s == 10) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op1) == 0) printf(" %02X %02X %02X", 83, 235 - RT[j].num, atoi(op2));
	}
	if (s == 11) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op2) == 0) printf(" %02X %02X", 35, 193 + RT[j].num);
	}
	if (s == 12) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op1) == 0) printf(" %02X %02X %02X", 131, 224 + RT[j].num, atoi(op2)*256);
	}
	if (s == 13) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op1) == 0) printf(" %02X %02X", 35, 6 + 8 * RT[j].num);
		for (int j = 0; j < i; j++)
			if (strcmp(ST[j].symbol, op2) == 0) printf(" %04X", ST[j].sindex * 256);
	}
	if (s == 14) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op2) == 0) printf(" %02X %02X", 33, 6 + 8 * RT[j].num);
		for (int j = 0; j < i; j++)
			if (strcmp(ST[j].symbol, op1) == 0) printf(" %04X", ST[j].sindex * 256);
	}
	if (s == 15) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op2) == 0) printf(" %02X %02X", 11, 200 + RT[j].num);
	}
	if (s == 16) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op1) == 0) printf(" %02X %02X %02X", 131, 200 + RT[j].num, atoi(op2));
	}
	if (s == 17) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op1) == 0) printf(" %02X %02X", 11, 6 + 8 * RT[j].num);
		for (int j = 0; j < i; j++)
			if (strcmp(ST[j].symbol, op2) == 0) printf(" %04X", ST[j].sindex * 256);
	}
	if (s == 18) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op2) == 0) printf(" %02X %02X", 11, 9 + 8 * RT[j].num);
		for (int j = 0; j < i; j++)
			if (strcmp(ST[j].symbol, op1) == 0) printf(" %04X", ST[j].sindex * 256);
	}
	if (s == 19) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op1) == 0) printf(" %02X", 64 + RT[j].num);
	}
	if (s == 20) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op1) == 0) printf(" %02X", 72 + RT[j].num);
	}
	if (s == 21) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op2) == 0) printf(" %02X %02X", 59, 216 + RT[j].num);
	}
	if (s == 22) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op1) == 0) printf(" %02X %02X %02X", 131, 248 + RT[j].num, atoi(op2));
	}
	if (s == 23) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op2) == 0) printf(" %02X %02X", 57, 6 + 8 * RT[j].num);
		for (int j = 0; j < i; j++)
			if (strcmp(ST[j].symbol, op1) == 0) printf(" %04X", ST[j].sindex*256);
	}
	if (s == 24) {
		for (int j = 0; j < 14; j++)
			if (strcmp(RT[j].reg, op1) == 0) printf(" %02X %02X", 59, 6 + 8 * RT[j].num);
		for (int j = 0; j < i; j++)
			if (strcmp(ST[j].symbol, op2) == 0) printf(" %04X", ST[j].sindex * 256);
	}
	if (s == 25) {
		for (int j = 0; j < i; j++)
			if (strcmp(ST[j].symbol, op1) == 0) {
				if (ST[j].sindex < index) printf(" %02X %02X", 235, 252 - (index - ST[j].sindex));
				else printf(" %02X %02X", 235, ST[j].sindex - index - 2);
		}
	}
	if (s == 26) {
		for (int j = 0; j < i; j++)
			if (strcmp(ST[j].symbol, op1) == 0) { 
				if (ST[j].sindex < index) printf(" %02X %02X<<", 119, 252- (index- ST[j].sindex));
				else printf(" %02X %02X<<", 119,   ST[j].sindex-index-2); 
			}
	}
	if (s == 27) {
		for (int j = 0; j < i; j++)
			if (strcmp(ST[j].symbol, op1) == 0) {
				if (ST[j].sindex < index) printf(" %02X %02X", 114, 252 - (index - ST[j].sindex));
				else printf(" %02X %02X", 114, ST[j].sindex - index - 2); 
		}
	}
	if (s == 28) {
		for (int j = 0; j < i; j++)
			if (strcmp(ST[j].symbol, op1) == 0) {
				if (ST[j].sindex < index) printf(" %02X %02X", 116, 252 - (index - ST[j].sindex));
				else printf(" %02X %02X", 116, ST[j].sindex - index - 2);
		}
	}
	if (s == 29) {
		printf(" %02X %02X", 205, 33);
	}
printf("\n");
}
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡloop2endedㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
int main() {
	FILE* fp;
	errno_t err=fopen_s(&fp, "R_Table.txt", "r");
	for(int j=0;j<14;j++){
		char read[100];
		fgets(read, 100, fp);
		temp = strtok(read, " ");
		strcpy(RT[j].reg, temp);
		temp = strtok(NULL, "\n");
		RT[j].num = atoi(temp);
	}
	fclose(fp);
	err = fopen_s(&fp, "I_Table.txt", "r");
	for (int j = 0; j < 30; j++) {
		char read[100];
		fgets(read, 100, fp);
		temp = strtok(read, " ");
		temp = strtok(NULL, " ");
		strcpy(IT[j].component, temp);
		temp = strtok(NULL, " ");
		IT[j].add_index = atoi(temp);
	}
	fclose(fp);
	err = fopen_s(&fp, "Assembly.txt", "r");
	printf("*******************************LOOP1*******************************\n");
	while (true) {
		char read[100];
		fgets(read, 100, fp);
		read[strlen(read) - 1] = '\0';
		if (strstr(read, "MAIN") != NULL || strstr(read, "ASSUME") != NULL || strstr(read, "ENDS") != NULL) { 
			printf("Direc\n");
			continue;
		}
		else if (strstr(read, "END") != NULL) {
			printf("Direc\n");
			break;
		}
		else  loop1(read);
		printf("\n");
	}
	printf("***************LOOP1 ENDED / Symbol Table is made****************\n");
	fclose(fp);
	index = 0;
	printf("\n\n*******************************Symbol Table*******************************\n");
	for (int j = 0; j < i; j++) {
		printf("\t%s\t%d\n", ST[j].symbol,ST[j].sindex);
	}
	printf("*******************************Symbol Table Ended*******************************\n");
	fopen_s(&fp, "Assembly.txt", "r");
	printf("\n\n*******************************LOOP2*******************************\n");
	while (true) {
		char read[100];
		fgets(read, 100, fp);
		read[strlen(read) - 1] = '\0';
		if (strstr(read, "MAIN") != NULL || strstr(read, "ASSUME") != NULL || strstr(read, "ENDS") != NULL) continue;
		else if (strstr(read, "END") != NULL) 	break;
		else  loop2(read);
	}
	fclose(fp);
	printf("*******************************LOOP2 ENDED*******************************\n");
}