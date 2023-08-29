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
			string kTemp = mKey.substr(kindex,1);//스트링의 1번째부터 끝까지 문자로 하나씩 뜯어와서 저장
			for ( j = 0; j<25; j++) {
				if (temp[j].find(kTemp) != -1) {//그 문자가 이미 임시 배열에 있으면
					break;//반복문 탈출
				}
			}
			if (j == 25) {//그 문자가 임시 배열에 없으면
				if (mPair.find(kTemp) != -1) {//그 문자가 페어로 묶인 문자이면
					temp[tindex++] = mPair;//그 페어를 임시 배열에 저장
				}
				else temp[tindex++] = kTemp;//페어가 아니면 그 문자를 임시 배열에 저장 
			}
		}//임시 배열 구성 완료
	
		for (j = 0; j < tindex; j++) {//임시 배열에 있는 문자룰 순서대로 키 테이블에 저장
			key_table[i++] = temp[j];
		}
		for (j = 0; j < i; j++) {
			cout << key_table [j] << endl;
		}
		for (int alp=65; alp <= 90; alp++) {//알파벳 대문자 A부터 Z까지
			for (j = 0; j < i; j++) {//키 테이블 내부를 순회하면서
				if (key_table[j].find(char(alp)) != -1) {
					cout << char(alp) << "is already here\n";
					break;
				}//키테이블 내부에 alp가 있으면 반복물 탈출
			}
			if (i == j) key_table[i++] = char(alp);//없으면 키 테이블에 저장
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