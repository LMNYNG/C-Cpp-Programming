#include <iostream>
#include <string>
using namespace std;

class Playfair {
	string mTable[25];// Ű���̺�
	string mPair;// �Բ� ����� Ű ��
	string mKey;// Ű ���̺� ������ ���� Ű ��
	string Encrypted;// ��ȣȭ�� ����
	string Plain;//��ȣȭ �� ��
	string Decrypted;//��ȣȭ�� ������ ��ȣȭ�� ����
public:
	Playfair(string mKey, string mPair);//������
	void makeTable();//Ű ���̺��� ���� �Լ�
	void showTable();//Ű ���̺��� �ҷ��� �Լ�
	string makeEncryption();//������ ��ȣȭ�� ������ ������ �Լ�
	string makeDecryption();//��ȣȭ�� �������� ��ȣȭ�� ������ ������ �Լ�
	string makePlain(string Plain);//���� �о�ͼ� �����ϴ� �Լ�
	void callEncrypted();//Ŭ������ ����� ��ȣȭ�� ������ �о���� �Լ�
	void callDecrypted();//Ŭ������ ����� ��ȣȭ�� ������ �о���� �Լ�
	void callPlain();//Ŭ������ ����� ���� �о���� �Լ�
};

Playfair::Playfair(string mKey, string mPair) {//������

	if (mPair[0] > mPair[2]) {//Ű ���� �� ���ڰ� ���ĺ� ������ ���� ������
		this->mPair.append(mPair.substr(2, 1));
		this->mPair.append(mPair.substr(1, 1));
		this->mPair.append(mPair.substr(0, 1));
	}//mPair�� ������ ������ ������ �����ؼ� this->mPair�� ����
	else this->mPair = mPair;//������� ���� �״�� mPair�� this->mPair�� ����
	this->mKey.append(mKey.substr(0, 1));
	for (int i = 1; i < mKey.length(); i++) {
		if (this->mKey.find(mKey[i]) == -1) {
			this->mKey.append(mKey.substr(i, 1));
		}//mKey������ ������� �ߺ��� �����Ͽ� this->mKey�� ����
	}
	cout << "****[mKey & mPair]*******************************\n";
	cout << "\tEntered Key is [" << mKey << "]\n\tCreated mKey is[" << this->mKey
		<< "]\n\tEntered Pair is[" << mPair << "]\n\tCreated mPair is [" << this->mPair << "]\n";
	cout << "*************************************************\n";//������ �Ϸ�Ǿ����� ǥ��
}

void Playfair::makeTable() {//Ű ���̺��� ���� �Լ�
	int i = 0, j;
	for (int j = 0; j < mKey.length(); j++) {//�ӽ� �迭�� �ִ� ���ڸ� ������� Ű ���̺� ����
		if (this->mKey[j] == this->mPair[2]) continue; // mPair�� �� ��° ���ĺ� ����
		if (this->mPair.find(mKey[j]) != -1) {//�ش� ���ڰ� mPair�� ���� �����̸�
			this->mTable[i++] = this->mPair;//mTable�� mPair �ֱ�
		}
		else this->mTable[i++] = mKey.substr(j, 1);//mPair�� �ƴϸ� �׳� �ֱ�
	}
	for (int alp = 65; alp <= 90; alp++) {//���ĺ� �빮�� A���� Z����
		for (j = 0; j < i; j++) //Ű ���̺� ���θ� ��ȸ�ϸ鼭
			if (mTable[j].find(char(alp)) != -1) break; //Ű���̺� ���ο� alp�� ������ �ݺ��� Ż��
		if (i == j) {//������ Ű ���̺� ����
			if (char(alp) == this->mPair[0]) mTable[i++] = this->mPair;//���� ��� ����
			else mTable[i++] = char(alp);//�ƴϸ� �׳� ����
		}
	}
}

void Playfair::showTable() {//Ű ���̺��� �ҷ��� �Լ�
	cout << "****[mTable]*************************************" << endl << "*\t\t\t\t\t\t*" << endl;
	for (int i = 0; i < 25; i++) {
		if (i % 5 == 0) cout << "*";
		cout << "\t" << this->mTable[i];
		if (i % 5 == 4) cout << "\t*" << endl;
	}
	cout << "*\t\t\t\t\t\t*" << endl << "*************************************************" << endl;
}

string Playfair::makeEncryption() {//������ ��ȣȭ�� ������ ������ �Լ�
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
string Playfair::makeDecryption() {//��ȣȭ�� �������� ��ȣȭ�� ������ ������ �Լ�
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
string Playfair::makePlain(string Plain) {//���� �о�ͼ� �����ϴ� �Լ�
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
void Playfair::callEncrypted() {//Ŭ���� ������ ��ȣȭ�� ���� ���
	cout << "Encrypted text in class[Playfair] is\n[ " << Encrypted << " ]\n";
}
void Playfair::callDecrypted() {//Ŭ���� ������ ��ȣȭ�� ���� ���
	cout << "Decrypted text in class[Playfair] is\n[ " << Decrypted << " ]\n";
}
void Playfair::callPlain() {//Ŭ���� ������ �� ���
	cout << "Plain text in class[Playfair] is\n[ " << Plain << " ]\n";
}

int main() {


	Playfair pfair("ASSASSINATOR", "A/S");//Ű ���� �Բ� �� Ű �� �Է�(�빮�ڷ�)


	pfair.makeTable();//Ű ���̺� ����
	pfair.showTable();//Ű ���̺� ���


	string pl = pfair.makePlain("BECAREFULFORASSASSINATOR");//�� �Է�
	cout << pl << endl;//���� �� �Ǵ��� Ȯ��1


	string en = pfair.makeEncryption();//�� ������� ��ȣȭ�� ���� ����
	cout << en << endl; // ���� �� �Ǵ��� Ȯ��2


	string de = pfair.makeDecryption();//��ȣȭ�� ���� ������� ��ȣȭ�� ���� ����
	cout << de << endl << endl;//���� �� �Ǵ��� Ȯ��3


	pfair.callPlain(); //�� �� ����Ǿ����� Ȯ��
	pfair.callEncrypted();//��ȣȭ ���� �� ����Ǿ����� Ȯ��
	pfair.callDecrypted();//��ȣȯ ���� �� ����Ǿ����� Ȯ��


}