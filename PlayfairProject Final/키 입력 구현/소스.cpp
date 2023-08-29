#include <iostream>
#include <string>
using namespace std;

class Key {
	string key_table[25];
public:
	void make_key(string mKey, string mPair) {
		string temp[25];
		int tindex=0;
		int i=0,j;
		if (mPair.find(mKey[i]) != -1)
			temp[tindex++] = mPair;
		else temp[tindex++] = mKey[i];
		for (int kindex = 1; kindex<mKey.length(); kindex++) {
			string kTemp = mKey.substr(kindex,1);//��Ʈ���� 1��°���� ������ ���ڷ� �ϳ��� ���ͼ� ����
			for ( j = 0; j<25; j++) {
				if (temp[j].find(kTemp) != -1) {//�� ���ڰ� �̹� �ӽ� �迭�� ������
					break;//�ݺ��� Ż��
				}
			}
			if (j == 25) {//�� ���ڰ� �ӽ� �迭�� ������
				if (mPair.find(kTemp) != -1) {//�� ���ڰ� ���� ���� �����̸�
					temp[tindex++] = mPair;//�� �� �ӽ� �迭�� ����
				}
				else temp[tindex++] = kTemp;//�� �ƴϸ� �� ���ڸ� �ӽ� �迭�� ���� 
			}
		}//�ӽ� �迭 ���� �Ϸ�
	
		for (j = 0; j < tindex; j++) {//�ӽ� �迭�� �ִ� ���ڷ� ������� Ű ���̺� ����
			key_table[i++] = temp[j];
		}
		for (j = 0; j < i; j++) {
			cout << key_table [j] << endl;
		}
		for (int alp=65; alp <= 90; alp++) {//���ĺ� �빮�� A���� Z����
			for (j = 0; j < i; j++) {//Ű ���̺� ���θ� ��ȸ�ϸ鼭
				if (key_table[j].find(char(alp)) != -1) {
					cout << char(alp) << "is already here\n";
					break;
				}//Ű���̺� ���ο� alp�� ������ �ݺ��� Ż��
			}
			if (i == j) key_table[i++] = char(alp);//������ Ű ���̺� ����
		}
	}
	void call_key() {
		for (int i = 0; i < 25; i++) {
			cout << '\t' << key_table[i];
			if (i % 5 == 4) cout << endl;
		}
		cout << endl;
	}

};
int main() {
	Key prac;
	prac.make_key("ASSASSINATOR", "H/Z");
	prac.call_key();
}