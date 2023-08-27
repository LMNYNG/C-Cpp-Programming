#include <iostream>
#include <string>
using namespace std;

class Playfair {
	string mTable[25];// 키테이블
	string mPair;// 함께 저장될 키 쌍
	string mKey;// 키 테이블 생성에 사용될 키 값
	string Encrypted;// 암호화된 문장
	string Plain;//암호화 할 평문
	string Decrypted;//암호화된 문장을 복호화한 문장
public:
	Playfair(string mKey, string mPair);//생성자
	void makeTable();//키 테이블을 만들 함수
	void showTable();//키 테이블을 불러올 함수
	string makeEncryption();//평문으로 암호화된 문장을 생성할 함수
	string makeDecryption();//암호화된 문장으로 복호화된 문장을 생성할 함수
	string makePlain(string Plain);//평문을 읽어와서 저장하는 함수
	void callEncrypted();//클래스에 저장된 암호화된 문장을 읽어오는 함수
	void callDecrypted();//클래스에 저장된 복호화된 문장을 읽어오는 함수
	void callPlain();//클래스에 저장된 평문을 읽어오는 함수
};

Playfair::Playfair(string mKey, string mPair) {//생성자

	if (mPair[0] > mPair[2]) {//키 쌍의 뒷 문자가 알파벳 상으로 먼저 나오면
		this->mPair.append(mPair.substr(2, 1));
		this->mPair.append(mPair.substr(1, 1));
		this->mPair.append(mPair.substr(0, 1));
	}//mPair를 작은게 앞으로 오도록 변경해서 this->mPair에 저장
	else this->mPair = mPair;//순서대로 오면 그대로 mPair를 this->mPair에 저장
	this->mKey.append(mKey.substr(0, 1));
	for (int i = 1; i < mKey.length(); i++) {
		if (this->mKey.find(mKey[i]) == -1) {
			this->mKey.append(mKey.substr(i, 1));
		}//mKey값에서 순서대로 중복을 제거하여 this->mKey에 저장
	}
	cout << "****[mKey & mPair]*******************************\n";
	cout << "\tEntered Key is [" << mKey << "]\n\tCreated mKey is[" << this->mKey
		<< "]\n\tEntered Pair is[" << mPair << "]\n\tCreated mPair is [" << this->mPair << "]\n";
	cout << "*************************************************\n";//저장이 완료되었음을 표시
}

void Playfair::makeTable() {//키 테이블을 만들 함수
	int i = 0, j;
	for (int j = 0; j < mKey.length(); j++) {//임시 배열에 있는 문자를 순서대로 키 테이블에 저장
		if (this->mKey[j] == this->mPair[2]) continue; // mPair의 두 번째 알파벳 무시
		if (this->mPair.find(mKey[j]) != -1) {//해당 문자가 mPair에 속한 문자이면
			this->mTable[i++] = this->mPair;//mTable에 mPair 넣기
		}
		else this->mTable[i++] = mKey.substr(j, 1);//mPair가 아니면 그냥 넣기
	}
	for (int alp = 65; alp <= 90; alp++) {//알파벳 대문자 A부터 Z까지
		for (j = 0; j < i; j++) //키 테이블 내부를 순회하면서
			if (mTable[j].find(char(alp)) != -1) break; //키테이블 내부에 alp가 있으면 반복물 탈출
		if (i == j) {//없으면 키 테이블에 저장
			if (char(alp) == this->mPair[0]) mTable[i++] = this->mPair;//페어면 페어 저장
			else mTable[i++] = char(alp);//아니면 그냥 저장
		}
	}
}

void Playfair::showTable() {//키 테이블을 불러올 함수
	cout << "****[mTable]*************************************" << endl << "*\t\t\t\t\t\t*" << endl;
	for (int i = 0; i < 25; i++) {
		if (i % 5 == 0) cout << "*";
		cout << "\t" << this->mTable[i];
		if (i % 5 == 4) cout << "\t*" << endl;
	}
	cout << "*\t\t\t\t\t\t*" << endl << "*************************************************" << endl;
}

string Playfair::makeEncryption() {//평문으로 암호화된 문장을 생성할 함수
	Encrypted.clear();
	int i, r, r1, r2;
	for (i = 0; i < Plain.length(); i += 2) {
		for (r = 0; r < 25; r++) {
			if (mTable[r].find(Plain[i]) != -1) {
				r1 = r;
			}
			if (mTable[r].find(Plain[i + 1]) != -1) {
				r2 = r;
			}
		}
		int rem = abs((r1 % 5) - (r2 % 5));
		if (r1 % 5 != r2 % 5 && r1 / 5 != r2 / 5) {
			if (r1 % 5 > r2 % 5) {
				Encrypted.append(mTable[r1 - rem], 0, 1);
				Encrypted.append(mTable[r2 + rem], 0, 1);
			}
			if (r1 % 5 < r2 % 5) {
				Encrypted.append(mTable[r1 + rem], 0, 1);
				Encrypted.append(mTable[r2 - rem], 0, 1);
			}
		}
		if (r1 / 5 == r2 / 5 && r1 % 5 != r2 % 5) {
			r1++, r2++;
			if (r1 % 5 == 0) r1 -= 5;
			if (r2 % 5 == 0) r2 -= 5;
			Encrypted.append(mTable[r1], 0, 1);
			Encrypted.append(mTable[r2], 0, 1);
		}
		if (r1 % 5 == r2 % 5 && r1 / 5 != r2 / 5) {
			r1 += 5;
			r2 += 5;
			if (r1 / 5 == 5) r1 = r1 % 5;
			if (r2 / 5 == 5) r2 = r2 % 5;
			Encrypted.append(mTable[r1], 0, 1);
			Encrypted.append(mTable[r2], 0, 1);
		}
		if (r1 % 5 == r2 % 5 && r1 / 5 == r2 / 5) {
			r1++; r2++;
			if (r1 % 5 == 0) r1 -= 20;
			if (r2 % 5 == 0) r2 -= 20;
			Encrypted.append(mTable[r1], 0, 1);
			Encrypted.append(mTable[r2], 0, 1);
		}
	}
	string temp;
	temp.append(this->Encrypted);
	return temp;
}
string Playfair::makeDecryption() {//암호화된 문장으로 복호화된 문장을 생성할 함수
	Decrypted.clear();
	int i, r, r1, r2;
	for (i = 0; i < Encrypted.length(); i += 2) {
		for (r = 0; r < 25; r++) {
			if (mTable[r].find(Encrypted[i]) != -1) {
				r1 = r;
			}
			if (mTable[r].find(Encrypted[i + 1]) != -1) {
				r2 = r;
			}
		}
		int rem = abs((r1 % 5) - (r2 % 5));
		if (r1 % 5 != r2 % 5 && r1 / 5 != r2 / 5) {
			if (r1 % 5 > r2 % 5) {
				Decrypted.append(mTable[r1 - rem], 0, 1);
				Decrypted.append(mTable[r2 + rem], 0, 1);
			}
			if (r1 % 5 < r2 % 5) {
				Decrypted.append(mTable[r1 + rem], 0, 1);
				Decrypted.append(mTable[r2 - rem], 0, 1);
			}
		}
		if (r1 / 5 == r2 / 5 && r1 % 5 != r2 % 5) {
			r1--, r2--;
			if (r1 % 5 == 4 || r1 < 0) r1 += 5;
			if (r2 % 5 == 4 || r2 < 0) r2 += 5;
			Decrypted.append(mTable[r1], 0, 1);
			Decrypted.append(mTable[r2], 0, 1);
		}
		if (r1 % 5 == r2 % 5 && r1 / 5 != r2 / 5) {
			if (r1 - 5 < 0)  r1 += 20;
			else r1 -= 5;
			if (r2 - 5 < 0) r2 += 20;
			else r2 -= 5;
			Decrypted.append(mTable[r1], 0, 1);
			Decrypted.append(mTable[r2], 0, 1);
		}
		if (r1 % 5 == r2 % 5 && r1 / 5 == r2 / 5) {
			r1--; r2--;
			if (r1 % 5 == 4) r1 += 5;
			if (r2 % 5 == 4) r2 += 5;
			Decrypted.append(mTable[r1], 0, 1);
			Decrypted.append(mTable[r2], 0, 1);
		}
	}
	string temp;
	temp.append(this->Decrypted);
	return temp;
}
string Playfair::makePlain(string Plain) {//평문을 읽어와서 저장하는 함수
	this->Plain = Plain;
	int i = 0;
	for (i = 0; i < this->Plain.length(); i += 2) {
		if (this->Plain[i] == this->Plain[i + 1]) this->Plain.insert(i + 1, "X");
	}
	if (this->Plain.length() % 2 == 1) {
		this->Plain.append("X");
	}
	string temp;
	temp.append(this->Plain);
	return temp;
}
void Playfair::callEncrypted() {//클래스 내부의 암호화된 문장 출력
	cout << "Encrypted text in class[Playfair] is\n[ " << Encrypted << " ]\n";
}
void Playfair::callDecrypted() {//클래스 내부의 복호화된 문장 출력
	cout << "Decrypted text in class[Playfair] is\n[ " << Decrypted << " ]\n";
}
void Playfair::callPlain() {//클래스 내부의 평문 출력
	cout << "Plain text in class[Playfair] is\n[ " << Plain << " ]\n";
}

int main() {


	Playfair pfair("ASSASSINATOR", "A/S");//키 값과 함께 들어갈 키 쌍 입력(대문자로)


	pfair.makeTable();//키 테이블 생성
	pfair.showTable();//키 테이블 출력


	string pl = pfair.makePlain("BECAREFULFORASSASSINATOR");//평문 입력
	cout << pl << endl;//리턴 잘 되는지 확인1


	string en = pfair.makeEncryption();//평문 기반으로 암호화된 문장 생성
	cout << en << endl; // 리턴 잘 되는지 확인2


	string de = pfair.makeDecryption();//암호화된 문장 기반으로 복호화된 문장 생성
	cout << de << endl << endl;//리턴 잘 되는지 확인3


	pfair.callPlain(); //평문 잘 저장되었는지 확인
	pfair.callEncrypted();//암호화 문장 잘 저장되었는지 확인
	pfair.callDecrypted();//복호환 문장 잘 저장되었는지 확인


}