#include <iostream>
#include <string>
using namespace std;

class Playpair {
	string KeyTable[25] = { "A","B","C","D","E",
									  "F","G","H","I/J","K",
									  "L","M","N","O","P",
									  "Q","R","S","T","U",
									  "V","W","X","Y","Z" };
	string plain, cipher, decrypted;
public:
	void call_key() {//key table을 5x5로 출력
		cout << "Key_Table is :";
		for (int i = 0; i < 25; i++) {
			if (i % 5 == 0) cout << endl;
			cout << '\t' << KeyTable[i];
		}
		cout << endl;
	}

	void call_plain() {//평문 출력
		cout << "Plain text is :" << endl;
		cout << plain << endl;
	}

	void call_cipher() {//암호화된 문장 출력
		cout << "Cipher text is :" << endl;
		cout << cipher << endl;
	}

	void call_decrypted() {//복호화된 문장 출력
		cout << "Decrypted text is :" << endl;
		cout << decrypted << endl;
	}

	void set_plain(string plain) {//평문 입력
		this->plain = plain;
		int i = 0;
		for (i = 0; i < this->plain.length(); i += 2) {
			if (this->plain[i] == this->plain[i + 1]) this->plain.insert(i + 1, "X");
		}
		if (this->plain.length() % 2 == 1) {
			this->plain.append("X");
		}
	}

	void encrypt() {//평문 암호화
		cipher.clear();
		int i, r, r1, r2;
		for (i = 0; i < plain.length(); i += 2) {
			for (r = 0; r < 25; r++) {
				if (KeyTable[r].find(plain[i]) != -1) {
					r1 = r;
				}
				if (KeyTable[r].find(plain[i + 1]) != -1) {
					r2 = r;
				}
			}
			int rem = abs((r1 % 5) - (r2 % 5));
			if (r1 % 5 != r2 % 5 && r1 / 5 != r2 / 5) {
				if (r1 % 5 > r2 % 5) {
					cipher.append(KeyTable[r1 - rem], 0, 1);
					cipher.append(KeyTable[r2 + rem], 0, 1);
				}
				if (r1 % 5 < r2 % 5) {
					cipher.append(KeyTable[r1 + rem], 0, 1);
					cipher.append(KeyTable[r2 - rem], 0, 1);
				}
			}
			if (r1 / 5 == r2 / 5 && r1 % 5 != r2 % 5) {
				r1++, r2++;
				if (r1 % 5 == 0) r1 -= 5;
				if (r2 % 5 == 0) r2 -= 5;
				cipher.append(KeyTable[r1], 0, 1);
				cipher.append(KeyTable[r2], 0, 1);
			}
			if (r1 % 5 == r2 % 5 && r1 / 5 != r2 / 5) {
				r1 += 5;
				r2 += 5;
				if (r1 / 5 == 5) r1 = r1 % 5;
				if (r2 / 5 == 5) r2 = r2 % 5;
				cipher.append(KeyTable[r1], 0, 1);
				cipher.append(KeyTable[r2], 0, 1);
			}
			if (r1 % 5 == r2 % 5 && r1 / 5 == r2 / 5) {
				r1++; r2++;
				if (r1 % 5 == 0) r1 -= 20;
				if (r2 % 5 == 0) r2 -= 20;
				cipher.append(KeyTable[r1], 0, 1);
				cipher.append(KeyTable[r2], 0, 1);
			}
		}
	}
	void decrypt() {//암호화된 문장 복호화
		decrypted.clear();
		int i, r, r1, r2;
		for (i = 0; i < cipher.length(); i += 2) {
			for (r = 0; r < 25; r++) {
				if (KeyTable[r].find(cipher[i]) != -1) {
					r1 = r;
				}
				if (KeyTable[r].find(cipher[i + 1]) != -1) {
					r2 = r;
				}
			}
			int rem = abs((r1 % 5) - (r2 % 5));
			if (r1 % 5 != r2 % 5 && r1 / 5 != r2 / 5) {
				if (r1 % 5 > r2 % 5) {
					decrypted.append(KeyTable[r1 - rem], 0, 1);
					decrypted.append(KeyTable[r2 + rem], 0, 1);
				}
				if (r1 % 5 < r2 % 5) {
					decrypted.append(KeyTable[r1 + rem], 0, 1);
					decrypted.append(KeyTable[r2 - rem], 0, 1);
				}
			}
			if (r1 / 5 == r2 / 5 && r1 % 5 != r2 % 5) {
				r1--, r2--;
				if (r1 % 5 == 4 || r1 < 0) r1 += 5;
				if (r2 % 5 == 4 || r2 < 0) r2 += 5;
				decrypted.append(KeyTable[r1], 0, 1);
				decrypted.append(KeyTable[r2], 0, 1);
			}
			if (r1 % 5 == r2 % 5 && r1 / 5 != r2 / 5) {
				if (r1 - 5 < 0)  r1 += 20;
				else r1 -= 5;
				if (r2 - 5 < 0) r2 += 20;
				else r2 -= 5;
				decrypted.append(KeyTable[r1], 0, 1);
				decrypted.append(KeyTable[r2], 0, 1);
			}
			if (r1 % 5 == r2 % 5 && r1 / 5 == r2 / 5) {
				r1--; r2--;
				if (r1 % 5 == 4) r1 += 5;
				if (r2 % 5 == 4) r2 += 5;
				decrypted.append(KeyTable[r1], 0, 1);
				decrypted.append(KeyTable[r2], 0, 1);
			}
		}
	}
};

int main() {
	Playpair test;
	test.call_key();
	test.set_plain("FOX");
	test.call_plain();
	test.encrypt();
	test.call_cipher();
	test.decrypt();
	test.call_decrypted();
}
